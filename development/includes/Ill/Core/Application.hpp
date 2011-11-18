#ifndef ILL_CORE_APPLICATION_HPP
#define ILL_CORE_APPLICATION_HPP

/**
* @file Application.h
* @date April 15, 2008
* @author Jeremiah van Oosten
* 
* @brief The main application class.
* @description The application interface is used to define the entry point for the game.<br>
* The application should perform a number of tasks which include:<br>
* <ul>
*	<li>Load and parse the configuration files used by the game</li>
*	<li>Parse command line arguments needed to correctly initilise the game engine</li>
*	<li>Create and initilise the memory managment system</li>
*	<li>Initilise static variables</li>
*  <li>Initialize the subsystems used by the game engine</li>
*	<li>Kick-off the game loop</li>
*	<li>Uninitialize the game subsystems</li>
*	<li>Shutdown the game engine</li>
* </ul>
*/

#include <Ill/Core/Object.hpp>
#include <Ill/Core/Events.hpp>
#include <Ill/Core/PropertyMap.hpp>
#include <Ill/Core/Subsystem.fwd.hpp>
#include <Ill/Core/Application.fwd.hpp>

namespace Ill
{
	namespace Core
	{
        class CORE_DLL Application : public Object, public boost::enable_shared_from_this<Application>
		{
		public:
            typedef std::vector< SubsystemPtr > SubsystemList;

			CLASS( Application, Object );
			CONSTRUCTOR( CORE_DLL, public, Application, () );

			virtual ~Application();

            /**
            * Initialize any memory needed by this component.
            * 
            * @returns true if all memory allocations were successful.
            */
            VIRTUAL_METHOD( CORE_DLL, public, void, Initialize, () );

            /**
            * Deallocate the memory that was allocated in Initialize.
            * It should be possible to invoke this method many times
            * without an error or exception being thrown.  This way, 
            * components can be recycled without deleting them.
            * 
            * @returns true if all memory allocations were successful.
            */
            VIRTUAL_METHOD( CORE_DLL, public, void, Terminate, () );

            /**
			* Register a subsystem class that is associated with this application.
			* An instance of a subsystem will be created and initialized when the
			* application starts and shut-down when the application is about to close.
			* After the application has been started, a subsystem can be retrieved from the 
			* application by calling the @see(GetSubsystem) templated method with the template
			* argument being the type of the subsystem to retrieve.
			* All subsystems should be accessible throughout the lifetime of the application.
			* Types of subsystems that will be registered could be:
			* <ul>
			*  <li>Memory</li>
			*  <li>IO</li>
			*  <li>Graphics</li>
			*  <li>Physics</li>
			*  <li>UI</li>
			* </ul>
			* If one subsystem has a dependency on another, then it should be registered
			* after all the subsystems it depends on.  This will ensure the dependent subsystem
			* is initialized first.
			* Startup parameters for each subsystem should be passed to the application using the 
			* property bag parameter.  These properties can be parsed from the command line, or read from 
			* the applications config file.
			*
			* @param subsystemClass an instance of the class that represents the subsystem type.
			* @returns true if the subsystem was successfully created, or false if either
			* the passed-in class is NULL or it is not of the correct type, that is, 
			* not derrived from the Subsystem class.
			*/
			VIRTUAL_METHOD( CORE_DLL, public, bool, RegisterSubsystem, (const Class& subsystemClass) );

			/**
			* Parse the command line options and configuration options and store them
			* in the PropertyMap passed to the function.
			* 
			* @param argc The number of entries in the argc array.
			* @param argv The array of command line arguments passed to the application.
			* @param options Populate the property map with the parsed configuration options.
			*/ 
			VIRTUAL_METHOD( CORE_DLL, public, bool, ParseConfigurations, ( int argc, char* argv[], PropertyMap& options ) );

			/**
			* Start up the application subsystem.
			*
			* @param options Contains all the startup options that have
			* been either, parsed from the application config file, or parsed
			* on the command line.
			*/
			VIRTUAL_METHOD( CORE_DLL, public, bool, StartUp, (const PropertyMap& startupOptions) );

			/**
			* Run the application with the options specified application 
			* options specified in StartUp.
			*/
			VIRTUAL_METHOD( CORE_DLL, public, int, Run, () );

            /**
             * Stop the application.  This will cause the game application
             * to return from the Run loop.
             */
            VIRTUAL_METHOD( CORE_DLL, public, void, Stop, () );

			/**
			* Shutdown the subsystems used by this application.
			*/
			VIRTUAL_METHOD( CORE_DLL, public, bool, Shutdown, () );

            /**
             * Check to see if the application has been initialized.
             */
            bool IsInitialized() const;

			/**
			* Retrieve a pointer to the subsystem that matches
			* the template parameter type.
			* @return A valid weak pointer object of the subsystem, otherwise
			* an invalid pointer object if the subsystem does not exist (the type
			* was never registered).
			*/
			template<class T>
			boost::weak_ptr<T> GetSubsystem();

            /** 
             * Events supported by the application class
             */
            Event           Initialized;
            Event           Terminated;

        protected:
            /** 
             * Derived classes should override these methods to handle 
             * specific events.  Don't forget to call the super class's implementation
             * otherwise the event will not be called.
             */
            virtual void OnInitialized( EventArgs& e );
            // The application instance has been terminated.
            virtual void OnTerminated( EventArgs& e );

		private:
			SubsystemList m_Subsystems;
            bool          m_IsInitialized;
		};

	} // namespace Ill
} // namespace Core

#include <Ill/Core/Application.inl>

#endif // ILL_CORE_APPLICATION_HPP