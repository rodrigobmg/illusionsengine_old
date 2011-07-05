#include <Ill/Core/CorePCH.hpp>

#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/Application.hpp>

namespace Ill
{
	namespace Core
	{
		Application::Application()
		{}

		Application::~Application()
		{
			BOOST_ASSERT( m_Subsystems.empty() );
		}

		bool Application::ParseConfigurations( int argc, char* argv[], PropertyMap& options )
		{

			return true;
		}

		bool Application::RegisterSubsystem( const Class* subsystemClass )
		{
			static const Class& baseClass = Subsystem::getClassStatic();

			// Make sure the class is actually derived from Subsystem.
			if ( subsystemClass != NULL && baseClass.isBase( *subsystemClass ) )
			{
				// Default construct the subsystem.
				Subsystem* subsystem = static_cast<Subsystem*>( subsystemClass->newInstance() );
				BOOST_ASSERT( subsystem != NULL );
				subsystem->Name = subsystemClass->getFullName();

				// Increment the ref-counter (this is to ensure the subsystem isn't accidentally deleted if 
				// somebody stores a pointer to the subsystem in an intrusive_ptr type.
				intrusive_ptr_add_ref(subsystem); // subsystem->AddRef();

				m_Subsystems.push_back( subsystem );
				return true;
			}

			return false;
		}

		bool Application::StartUp( const PropertyMap& options )
		{
			// Startup our registered subsystems.
			iterator iter = m_Subsystems.begin();

			while (iter != m_Subsystems.end() )
			{
				Subsystem* subsystem = (*iter);
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
				Subsystem* subsystem = (*iter);
				subsystem->Shutdown();

				// Decrement the ref counter.  This should trigger a delete if
				// nobody has an intrusive ptr reference to it.
				intrusive_ptr_release(subsystem);

				++iter;
			}
			m_Subsystems.clear();

			return true;
		}
	}
}