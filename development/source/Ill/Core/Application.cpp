#include <Ill/Core/CorePCH.hpp>

#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/DynamicLibSubsystem.hpp>
#include <Ill/Core/DynamicLib.hpp>
#include <Ill/Core/Plugin.hpp>
#include <Ill/Core/Application.hpp>

// The loaded plug-ins should expose 2 methods:
// 1) Plugin* CreatePlugin(void) 
//     This method should create the plug-in instance and return a pointer to it.
// 2) void DestroyPlugin(void) 
//     This method should destroy the plug-in releasing any dynamically allocated memory.
typedef Ill::Core::Plugin* (*CreatePluginFP)(void);
typedef void (*DestroyPluginFP)(void);

namespace Ill
{
	namespace Core
	{
        template<> Application* Singleton<Application>::ms_Singleton = NULL;

		Application::Application()
            : m_IsInitialized(false)
		{
        }

		Application::~Application()
		{
			BOOST_ASSERT( m_Subsystems.empty() );
            BOOST_ASSERT( m_Plugins.empty() );
		}

        Application& Application::Get() 
        {
            BOOST_ASSERT( ms_Singleton != NULL );
            return *ms_Singleton;
        }

        Application* Application::GetPtr()
        {
            return ms_Singleton;
        }

        void Application::Initialize()
        {
            // Before we can load plug-ins, we need the Dynamic Library subsystem  
            // to be available.  So register that one by default.
            RegisterSubsystem( DynamicLibSubsystem::getClassStatic() );

            DynamicLibSubsystemWeakPtr dynamicLibSystem = GetSubsystem<DynamicLibSubsystem>();
            m_DynamicLibSubsystem = dynamicLibSystem.lock();

            m_IsInitialized = true;

            OnInitialized( EventArgs( *this ) );
        }

        void Application::Terminate()
        {
            // Make sure our application has been shutdown.
            Shutdown();

            OnTerminated( EventArgs( *this ) );
        }

		bool Application::ParseConfigurations( int argc, char* argv[], PropertyMap& options )
		{

			return true;
		}

		bool Application::RegisterSubsystem( const Class& subsystemClass )
		{
			static const Class& baseClass = Subsystem::getClassStatic();

			// Make sure the class is actually derived from Subsystem.
			if ( baseClass.isBase( subsystemClass ) )
			{
				// Default construct the subsystem.
                SubsystemPtr subsystem = SubsystemPtr( static_cast<Subsystem*>( subsystemClass.newInstance() ) );
                BOOST_ASSERT( subsystem != NULL );
				subsystem->Name = subsystemClass.getFullName();
                subsystem->App = shared_from_this();

				m_Subsystems.push_back( subsystem );
				return true;
			}
            else
            {
                std::cerr << "ERROR: Failed to register type: \"" << subsystemClass.getName() << "\" Application::RegisterSubsystem." << std::endl; 
            }

			return false;
		}

        Plugin* Application::LoadPlugin( const std::wstring& filename )
        {
            BOOST_ASSERT( m_IsInitialized && "The application is not yet initialized." );
            
            fs::wpath filePath( filename );
            fs::wpath pluginName = filePath.stem();
            Plugin* plugin = GetPluginByName( pluginName.wstring() );

            if ( plugin == NULL )
            {
                // Try to load the dynamic lib from the provided filename.
                DynamicLibWeakPtr pluginLibWP = m_DynamicLibSubsystem->Load( filename );
                if ( DynamicLibPtr pluginLib = pluginLibWP.lock() )
                {
                    CreatePluginFP createPluginFunc = (CreatePluginFP)pluginLib->GetSymbol( "CreatePlugin" );
                    if ( createPluginFunc != NULL )
                    {
                        plugin = createPluginFunc();
                        if ( plugin != NULL )
                        {
                            plugin->FileName = filePath.wstring();
                            plugin->PluginName = filePath.stem().wstring();
                            PluginPtr pluginPtr( plugin );
                            AddPlugin( pluginPtr );
                        }
                        else
                        {
                            std::cerr << "Application::LoadPlugin: Plug-in creation failed in library \"";
                            std::wcerr << filename;
                            std::wcerr << "\"" << std::endl;
                        }
                    }
                    else
                    {

                        std::cerr << "Application::LoadPlugin: Could not find symbol \"CreatePlugin\" in library \"";
                        std::wcerr << filename;
                        std::cerr << "\"" << std::endl;
                    }
                }
            }

            return plugin;
        }

        void Application::UnloadPlugin( Plugin* plugin )
        {
            if ( plugin != NULL )
            {
                plugin->Terminiate();

                // Unload the DLL the plugin was loaded from.
                DynamicLibPtr ptrLib = m_DynamicLibSubsystem->GetLibrary( plugin->FileName );
                if ( ptrLib )
                {
                    DestroyPluginFP destroyPluginFunc = (DestroyPluginFP)ptrLib->GetSymbol( "DestroyPlugin" );
                    if ( destroyPluginFunc != NULL )
                    {
                        // Unload the plugin and all of the types that are associated with the plugin.
                        destroyPluginFunc();
                    }
                    else
                    {
                        std::cerr << "Application::UnloadPlugin: Could not find \"DestroyPlugin\" method in library \"";
                        std::wcerr << ptrLib->FileName.get();
                        std::cerr << "\"" << std::endl;
                    }
                    m_DynamicLibSubsystem->Unload( ptrLib );
                }
                else
                {
                    std::cerr << "Application::UnloadPlugin: Could not find library with filename: \"";
                    std::wcerr << plugin->FileName.get();
                    std::cerr << "\"" << std::endl;
                }

                // Remove the plug-in from the list of known plug-ins.
                PluginPtr ptrPlugin( plugin );
                RemovePlugin( ptrPlugin );
            }
        }

        Plugin* Application::GetPluginByName( const std::wstring& pluginName )
        {
            Plugin* ptrPlugin = NULL;
            PluginNameMap::iterator iter = m_PluginsByName.find( pluginName );
            if ( iter != m_PluginsByName.end() )
            {
                ptrPlugin = (iter->second).get();
            }

            return ptrPlugin;
        }

        void Application::AddPlugin( PluginPtr plugin )
        {
            PluginList::iterator iter = std::find( m_Plugins.begin(), m_Plugins.end(), plugin );
            if ( iter == m_Plugins.end() )
            {
                // Add it to the list of known plug-ins.
                m_Plugins.push_back(plugin);

                // Add it to the name -> plugin map
                m_PluginsByName.insert( PluginNameMap::value_type(plugin->PluginName, plugin) );
                m_PluginsByFileName.insert( PluginFileMap::value_type(plugin->FileName, plugin) );
            }
        }

        // Remove the given plug-in from the list of known plug-ins.
        void Application::RemovePlugin( PluginPtr plugin )
        {
            PluginList::iterator iter = std::find( m_Plugins.begin(), m_Plugins.end(), plugin );
            if ( iter != m_Plugins.end() )
            {
                m_PluginsByName.erase( plugin->PluginName );
                m_PluginsByFileName.erase( plugin->FileName );
                // Remove it from the list of known plug-ins.
                m_Plugins.erase( iter );
            }
        }

		bool Application::StartUp( const PropertyMap& options )
		{
			// Startup our registered subsystems.
            SubsystemList::iterator iter = m_Subsystems.begin();

			while (iter != m_Subsystems.end() )
			{
                SubsystemPtr subsystem = (*iter);
				BOOST_ASSERT( subsystem != NULL );

				if ( !subsystem->Startup( options ) )
				{
					// Our subsystem failed to start...
					return false;
				}

				++iter;
			}
			return true;
		}

		int Application::Run()
		{
			return 0;
		}

        void Application::Stop()
        {

        }

		bool Application::Shutdown()
		{
            // Unload any previously loaded plug-ins
            PluginList::iterator pluginIter = m_Plugins.begin();
            while ( pluginIter != m_Plugins.end() )
            {
                PluginPtr ptrPlugin = (*pluginIter);
                UnloadPlugin( ptrPlugin.get() );
                ++pluginIter;
            }
            m_PluginsByName.clear();
            m_PluginsByFileName.clear();
            m_Plugins.clear();

			// Shutdown our subsystems in the opposite order as they were registered.
			SubsystemList::reverse_iterator iter = m_Subsystems.rbegin();
			while ( iter != m_Subsystems.rend() )
			{
                SubsystemPtr subsystem = (*iter);
				subsystem->Shutdown();

				++iter;
			}
			m_Subsystems.clear();

			return true;
		}

        void Application::OnInitialized( EventArgs& e )
        {
            Initialized( e );
        }

        void Application::OnTerminated( EventArgs& e )
        {
            Terminated( e );
        }

	}
}