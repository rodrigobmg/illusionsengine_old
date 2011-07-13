/**
 * @file PluginSubsystem.hpp
 * @date September 25, 2009
 *
 * Handles loading and unlading Dynamic libraries (DLL on Windows, Shared Objects on Linux).
 */

#ifndef ILL_CORE_PluginSUBSYSTEM_HPP
#define ILL_CORE_PluginSUBSYSTEM_HPP

#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/Plugin.hpp>

namespace Ill
{
    namespace Core
    {
        class PluginSubsystem : public Subsystem
        {
        public:
            CLASS(PluginSubsystem,Subsystem);
            CONSTRUCTOR(public,PluginSubsystem,());
            virtual ~PluginSubsystem();

			/**
			 * Get a reference to our singleton instance.
			 */
			STATIC_METHOD( public, PluginSubsystem&, GetSingleton, () );

            /**
            * Startup
            */
            VIRTUAL_METHOD(public,bool,Startup,( const PropertyMap& startupOptions ));

            /**
            * Shutdown
            */
            VIRTUAL_METHOD(public,bool,Shutdown,());

            /**
             * Loads a .DLL or an .SO by filename.
             * @returns a pointer to the loaded lib, or a NULL pointer if the plugin can't be loaded.
             */
            VIRTUAL_METHOD(public, Plugin*, Load,( const std::wstring& pluginName ) );

            /**
             * Unloads a dynamic loaded lib
             */
            VIRTUAL_METHOD(public,void,Unload, ( Plugin* plugin ) );

        private:
            typedef std::map<std::wstring, Plugin* > PluginList;
            PluginList m_PluginList;

			static PluginSubsystem* ms_Singleton;
        };
    }
}

#endif // ILL_CORE_PluginSUBSYSTEM_HPP