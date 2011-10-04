#include <Ill/Core/CorePCH.hpp>

#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/PluginSubsystem.hpp>
#include <Ill/Core/Application.hpp>

namespace Ill
{
	namespace Core
	{
		Application::Application()
		{
        }

		Application::~Application()
		{
			BOOST_ASSERT( m_Subsystems.empty() );
		}

        void Application::Initialize()
        {
            // Before we can load plugins, we need the plugin subsystem  
            // to be available.  So register that one by default.
            RegisterSubsystem( PluginSubsystem::getClassStatic() );
        }

        void Application::Terminiate()
        {
            // Make sure our application has been shutdown.
            Shutdown();
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

			return false;
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

		bool Application::Run()
		{
			return true;
		}

		bool Application::Shutdown()
		{
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
	}
}