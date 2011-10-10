/**
 * @file PluginSubsystem.hpp
 * @date September 25, 2009
 *
 * Handles loading and unloading of Dynamic libraries (DLL on Windows, Shared Objects on Linux).
 */

#ifndef ILL_CORE_PLUGINSUBSYSTEM_HPP
#define ILL_CORE_PLUGINSUBSYSTEM_HPP

#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/Plugin.fwd.hpp>
#include <Ill/Core/PluginSubsystem.fwd.hpp>

namespace Ill
{
    namespace Core
    {
        class _IllExport PluginSubsystem : public Subsystem
        {
        public:
            CLASS(PluginSubsystem,Subsystem);
            CONSTRUCTOR(public,PluginSubsystem,());
            virtual ~PluginSubsystem();

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
            VIRTUAL_METHOD(public, PluginPtr, Load,( const std::wstring& pluginName ) );

            /**
             * Unloads a dynamic loaded lib
             */
            VIRTUAL_METHOD(public,void,Unload, ( PluginPtr plugin ) );

        private:
            typedef std::map<std::wstring, PluginPtr > PluginList;
            PluginList m_PluginList;
        };
    }
}

#endif // ILL_CORE_PLUGINSUBSYSTEM_HPP