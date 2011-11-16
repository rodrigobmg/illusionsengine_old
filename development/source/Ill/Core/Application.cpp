#include <Ill/Core/CorePCH.hpp>

#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/DynamicLibSubsystem.hpp>
#include <Ill/Core/Application.hpp>

namespace Ill
{
	namespace Core
	{
		Application::Application()
            : m_IsInitialized(false)
		{
        }

		Application::~Application()
		{
			BOOST_ASSERT( m_Subsystems.empty() );
		}

        void Application::Initialize()
        {
            // Before we can load plug-ins, we need the Dynamic Library subsystem  
            // to be available.  So register that one by default.
            RegisterSubsystem( DynamicLibSubsystem::getClassStatic() );

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