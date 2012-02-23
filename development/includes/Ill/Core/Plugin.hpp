#ifndef ILL_CORE_PLUGIN_HPP
#define ILL_CORE_PLUGIN_HPP

#include <Ill/Core/Object.hpp>
#include <Ill/Core/Plugin.fwd.hpp>

namespace Ill
{
    namespace Core
    {
        class CORE_DLL Plugin : public Object
        {
        public:
            CLASS( Plugin, Object );
            CONSTRUCTOR( CORE_DLL, public, Plugin, () );

            /**
             * Default destructor
             */
            ~Plugin();

            /**
             * Initialize the plug-in including registering types
             * with the class registry, registering subsystems, and 
             * performing any other initialization steps required by the plug-in.
             */
            VIRTUAL_METHOD( CORE_DLL, public, void, Initialize, () );

            /**
             * Terminate the plug-in including unregistering subsystems that 
             * were initialized in the Initialize() method.
             */
            VIRTUAL_METHOD( CORE_DLL, public, void, Terminate, () );

        protected:
            const std::wstring& get_PluginName() const;
            void set_PluginName( const std::wstring& pluginName );

            const std::wstring& get_FileName() const;
            void set_FileName( const std::wstring& fileName );

        private:
            // The plug-in name is the name of the library file name without 
            // paths or extensions where this plug-in was loaded from.
            std::wstring    m_PluginName;
            std::wstring    m_FileName;

        public:
            PROPERTY( CORE_DLL, const std::wstring&, PluginName );
            PROPERTY( CORE_DLL, const std::wstring&, FileName );
        };
    }
}

#endif // ILL_CORE_PLUGIN_HPP