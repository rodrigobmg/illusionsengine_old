#include <Ill/Core/CorePCH.hpp>

#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/DynamicLibSubsystem.hpp>
#include <Ill/Core/DynamicLib.hpp>
#include <Ill/Core/Plugin.hpp>
#include <Ill/Core/Application.hpp>

// The loaded plug-ins should expose 2 methods:
// 1) void CreatePlugin(void) 
//     This method should initialize the plugin and return a pointer to it.
// 2) void DestroyPlugin(void) 
//     This method should destroy the plug-in releasing any dynamically allocated memory.
typedef Ill::Core::PluginPtr (*CreatePluginFP)(void);
typedef void (*DestroyPluginFP)(void);

namespace Ill
{
	namespace Core
	{
        template<> Application* Singleton<Application>::ms_Singleton = NULL;

		Application::Application()
            : m_IsInitialized(false)
            , m_IsRunning(false)
		{
            // Before we can load plug-ins, we need the Dynamic Library subsystem  
            // to be available.
            m_DynamicLibSubsystem = boost::make_shared<DynamicLibSubsystem>();
            m_DynamicLibSubsystem->Initialize();
        }

		Application::~Application()
		{
            m_DynamicLibSubsystem->Terminate();

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

        template<class Archive>
        void Application::serialize( Archive& ar, const unsigned int version )
        {
            ar & boost::serialization::base_object<Super>(*this);
        }

        void Application::Initialize()
        {
            BOOST_ASSERT( m_IsInitialized == false );
            
            Super::Initialize();

            // Initialize loaded plug-ins
            PluginList::iterator pluginIter = m_Plugins.begin();
            while ( pluginIter != m_Plugins.end() )
            {
                PluginPtr plugin = (*pluginIter);
                plugin->Initialize();

                ++pluginIter;
            }

            // Initialize registered subsystems
            SubsystemList::iterator subsystemIter = m_Subsystems.begin();
            while ( subsystemIter != m_Subsystems.end() )
            {
                SubsystemPtr subsystem = (*subsystemIter);
                subsystem->Initialize();

                ++subsystemIter;
            }

            m_IsInitialized = true;

            OnInitialized( EventArgs( *this ) );
        }

        void Application::Terminate()
        {
            BOOST_ASSERT( m_IsInitialized == true );

            // Terminate the subsystems in the opposite order as they were registered.
            SubsystemList::reverse_iterator iter = m_Subsystems.rbegin();
            while ( iter != m_Subsystems.rend() )
            {
                SubsystemPtr subsystem = (*iter);
                subsystem->Terminate();

                ++iter;
            }

            m_Subsystems.clear();

            // Unload any previously loaded plug-ins
            PluginList plugins = m_Plugins;
            PluginList::iterator pluginIter = plugins.begin();
            while ( pluginIter != plugins.end() )
            {
                PluginPtr plugin = (*pluginIter);
                plugin->Terminate();

                UnloadPlugin( plugin );
                ++pluginIter;
            }

            plugins.clear();
            m_PluginsByName.clear();
            m_PluginsByFileName.clear();
            m_Plugins.clear();

            // Flush all the libraries.  At this point
            // there should be no residual pointers to objects
            // created in the library.
            m_DynamicLibSubsystem->Flush();

            m_IsInitialized = false;

            OnTerminated( EventArgs( *this ) );
        }

		bool Application::RegisterSubsystem( SubsystemPtr subsystem )
		{
            BOOST_ASSERT_MSG( subsystem, "Subsystem type is invalid.");

            if ( m_IsInitialized )
            {
                subsystem->Initialize();
            }
            if ( std::find( m_Subsystems.begin(), m_Subsystems.end(), subsystem ) == m_Subsystems.end() )
            {
    			m_Subsystems.push_back( subsystem );
	    		return true;
            }
            else
            {
                BOOST_ASSERT_MSG( false, "Subsystem already registered." );
            }
            return false;
		}

        SubsystemPtr Application::GetSubsystem( const Class& classType )
        {
            SubsystemList::iterator iter = m_Subsystems.begin();
            while ( iter != m_Subsystems.end() )
            {
                SubsystemPtr subsystem = (*iter);
                const Class& subsystemClass = subsystem->getClass();
                if ( subsystemClass.isRelative(classType) )
                {
                    return subsystem;
                }
                ++iter;
            }

            // Return an invalid ptr object
            return SubsystemPtr();
        }

        SubsystemPtr Application::GetSubsystem( const std::string& className )
        {
            const Class* classType = Class::forName(className);
            if ( classType != NULL )
            {
                return GetSubsystem( *classType );
            }
            else
            {
                std::cerr << "Class name \"" << className << "\" not found in class registry." << std::endl;
            }

            return SubsystemPtr();
        }

        PluginPtr Application::LoadPlugin( const std::wstring& filename )
        {            
            fs::wpath filePath( filename );
            fs::wpath pluginName = filePath.stem();
            PluginPtr pluginPtr = GetPluginByName( pluginName.wstring() );

            if ( !pluginPtr )
            {
                // Try to load the dynamic lib from the provided filename.
                DynamicLibPtr pluginLib = m_DynamicLibSubsystem->Load( filename );
                if ( pluginLib )
                {
                    CreatePluginFP createPluginFunc = (CreatePluginFP)pluginLib->GetSymbol( "CreatePlugin" );
                    if ( createPluginFunc != NULL )
                    {
                        pluginPtr = createPluginFunc();
                        if ( pluginPtr != NULL )
                        {
                            pluginPtr->FileName = filePath.wstring();
                            pluginPtr->PluginName = filePath.stem().wstring();
                            if ( m_IsInitialized )
                            {
                                pluginPtr->Initialize();
                            }

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

            return pluginPtr;
        }

        void Application::UnloadPlugin( PluginPtr plugin )
        {
            if ( plugin )
            {
                RemovePlugin( plugin );

                plugin->Terminate();

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
                    // Don't forget to call DynamicLibSubsystem::Flush to actually 
                    // release the libraries from memory.
                    m_DynamicLibSubsystem->Unload( ptrLib );
                }
                else
                {
                    std::cerr << "Application::UnloadPlugin: Could not find library with filename: \"";
                    std::wcerr << plugin->FileName.get();
                    std::cerr << "\"" << std::endl;
                }
            }
        }

        PluginPtr Application::GetPluginByName( const std::wstring& pluginName )
        {
            PluginPtr ptrPlugin;
            PluginNameMap::iterator iter = m_PluginsByName.find( pluginName );
            if ( iter != m_PluginsByName.end() )
            {
                ptrPlugin = (iter->second);
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

		int Application::Run()
		{
            m_IsRunning = true;
			return 0;
		}

        void Application::Stop()
        {
            m_IsRunning = false;
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