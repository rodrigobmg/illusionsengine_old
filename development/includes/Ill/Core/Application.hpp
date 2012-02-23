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
#include <Ill/Core/Singleton.hpp>
#include <Ill/Core/Events.hpp>
#include <Ill/Core/DynamicLibSubsystem.fwd.hpp>
#include <Ill/Core/Plugin.fwd.hpp>
#include <Ill/Core/Subsystem.fwd.hpp>
#include <Ill/Core/Application.fwd.hpp>

namespace Ill
{
	namespace Core
	{
        class CORE_DLL Application : public Object, public Singleton<Application>, public boost::enable_shared_from_this<Application>
		{
		public:
            typedef std::vector< SubsystemPtr > SubsystemList;
            typedef std::vector< PluginPtr > PluginList;

			CLASS( Application, Object );
			CONSTRUCTOR( CORE_DLL, public, Application, () );

			virtual ~Application();

            /**
             * Get a reference to the singleton instance of this application.
             * The application is the core class and is used to perform basic 
             * operations of the engine like loading plug-ins, and getting 
             * references to the loaded subsystems.
             * 
             * @precondition The application must first be created somewhere 
             * using make_shared<Application>() or new Application().
             *
             * @returns A reference to the application instance.
             */
            STATIC_METHOD( CORE_DLL, public, Application&, Get, () );

            /**
             * In case you need a pointer to the application, you can use
             * this method, otherwise just use the @see(Get) method.
             *
             * @precondition The application must first be created somewhere 
             * using make_shared<Application>() or new Application().
             *
             * @returns A pointer to the application instance.
             */
            STATIC_METHOD( CORE_DLL, public, Application*, GetPtr, () );

            /**
            * Initialize any memory needed by this object.
            */
            VIRTUAL_METHOD( CORE_DLL, public, void, Initialize, () );

            /**
            * Deallocate the memory that was allocated in Initialize.
            * It should be possible to invoke this method many times
            * without an error or exception being thrown.  This way, 
            * objects can be recycled without deleting them.
            * 
            */
            VIRTUAL_METHOD( CORE_DLL, public, void, Terminate, () );

            /**
			* Register a subsystem class that is associated with this application.
			* After the application has been started, a subsystem can be retrieved from the 
			* application by calling the @see(GetSubsystem).
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
			*
			* @param subSystem an instance of the subsystem to be registered.
			* @returns true if the subsystem was successfully added to the list of known 
            * subsystems, or false if a subsystem with the same type has already been registered.
			*/
			VIRTUAL_METHOD( CORE_DLL, public, bool, RegisterSubsystem, (SubsystemPtr subsystem) );

            /**
             * Load a plug-in that is to be used by the application.
             *
             * @precondition The application has been initialized.
             *
             * @param filePath The relative or absolute file path to the plug-in to be loaded.
             * 
             * @returns A pointer to the plug-in if it was loaded or NULL if the plug-in could not be loaded.
             *
             * @exception This method may throw an exception if the plugin file could not be found or if there was
             * a problem reading from the file.
             *
             * @see GetPlugin
             */
            VIRTUAL_METHOD( CORE_DLL, public, PluginPtr, LoadPlugin, ( const std::wstring& filePath ) );

            /**
             * Unloads a previously loaded plugin.
             * 
             * @precondition The plugin was previously loaded with @see(LoadPlugin).
             *
             * @param plugin The plugin to be unloaded.
             *
             * @see LoadPlugin
             */
            VIRTUAL_METHOD( CORE_DLL, public, void, UnloadPlugin, ( PluginPtr plugin ) );

            /**
             * Gets the pointer to a plug-in that has previously been loaded using @see(LoadPlugin).
             *
             * @precondition The plug-in was previously loaded with @see(LoadPlugin)
             * 
             * @param pluginName The name of the plug-in to be retrieved.  The name of the plug-in is the same
             * as the name of the plug-in file without the directory path or extensions, therefor all plug-ins
             * should have a unique name if you strip off the file path and extension.
             *
             * @returns A pointer to the plug-in with the given name otherwise NULL if the plugin
             * wasn't loaded yet.
             */
            VIRTUAL_METHOD( CORE_DLL, public, PluginPtr, GetPluginByName, ( const std::wstring& pluginName ) );

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
             * Check to see if the application has been initialized.
             */
            bool IsInitialized() const;

			/**
			* Retrieve a pointer to the subsystem that matches the class type.
			* @return A valid pointer object of the subsystem, otherwise
			* an invalid pointer object if the subsystem does not exist (the type
			* was never registered).
            *
            * @param subsystemClass The class type of the subsystem to retrieve.
			*/
			SubsystemPtr GetSubsystem( const Class& classType );

			/**
			* Retrieve a pointer to the subsystem that matches the class name.
			* @return A valid pointer object of the subsystem, otherwise
			* an invalid pointer object if the subsystem does not exist (the type
			* was never registered).
            *
            * @param subsystemClass The class name of the subsystem to retrieve.
			*/
            SubsystemPtr GetSubsystem( const std::string& className );

            /** 
             * Events supported by the application class
             */
            Event           Initialized;
            Event           Terminated;

        protected:
            /** 
             * Derived classes should override these methods to handle 
             * specific events.  Don't forget to call the super class's implementation
             * otherwise the event will not be triggered.
             */
            virtual void OnInitialized( EventArgs& e );
            // The application instance has been terminated.
            virtual void OnTerminated( EventArgs& e );

            // Adds the given plug-in to the list of known plug-ins.
            virtual void AddPlugin( PluginPtr plugin );
            // Remove the given plug-in from the list of known plug-ins.
            virtual void RemovePlugin( PluginPtr plugin );


		private:
            friend class boost::serialization::access;
            /**
             * Serialize or de-serialize the properties of an object.
             * Note: This method must always be declared private.
             * To allow the archive class access to private members
             * and methods of base classes, your class must allow
             * the boost::serialization::access class friend access by declaring 
             * it as a friend class.  Base classes are serialized by calling 
             * ar & boost::serialization::base_object<Super>(*this)
             * inside the serialize method.
             *
             * @param ar The archive object to serialize from or to.
             * @param version The class version when the object was serialized.
             */
            template<class Archive>
            void serialize( Archive& ar, const unsigned int version );

            // A sorted list of plug-ins by plug-in name.
            typedef std::map< std::wstring, PluginPtr > PluginNameMap;
            // A sorted list of plug-ins by file name.
            typedef std::map< std::wstring, PluginPtr > PluginFileMap;

			SubsystemList   m_Subsystems;
            PluginList      m_Plugins;
            PluginNameMap   m_PluginsByName;
            PluginFileMap   m_PluginsByFileName;

            DynamicLibSubsystemPtr m_DynamicLibSubsystem;
            bool            m_IsInitialized;
            bool            m_IsRunning;

		};

	} // namespace Ill
} // namespace Core

#include <Ill/Core/Application.inl>

#endif // ILL_CORE_APPLICATION_HPP