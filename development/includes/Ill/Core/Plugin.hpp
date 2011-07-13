#ifndef ILL_CORE_PLUGIN_HPP
#define ILL_CORE_PLUGIN_HPP

#include <Ill/Core/Object.hpp>

#if ILL_PLATFORM == ILL_PLATFORM_WIN32
#    define DYNLIB_HANDLE hInstance
#    define DYNLIB_LOAD( a ) LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#    define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#    define DYNLIB_UNLOAD( a ) !FreeLibrary( a )

struct HINSTANCE__;
typedef struct HINSTANCE__* hInstance;

#elif ILL_PLATFORM == ILL_PLATFORM_LINUX
#    define DYNLIB_HANDLE void*
#    define DYNLIB_LOAD( a ) dlopen( a, RTLD_LAZY | RTLD_GLOBAL)
#    define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#    define DYNLIB_UNLOAD( a ) dlclose( a )

#elif ILL_PLATFORM == ILL_PLATFORM_APPLE
#    define DYNLIB_HANDLE CFBundleRef
#    define DYNLIB_LOAD( a ) mac_loadExeBundle( a )
#    define DYNLIB_GETSYM( a, b ) mac_getBundleSym( a, b )
#    define DYNLIB_UNLOAD( a ) mac_unloadExeBundle( a )
#endif

namespace Ill
{
    namespace Core
    {
        class Plugin : public Object
        {
        public:
            CLASS(Plugin,Object);
            CONSTRUCTOR(public,Plugin,( const std::wstring& libName ) );
            /**
             * Default destructor
             */
            ~Plugin();

            /**
             * Load this Dynamic Library.
             */
            void Load();

            /**
             * Unload this Dynamic Library.
             */
            void Unload();

            /**
             * Gets the address of a particular symbol defined in the Dynamic Library.
             * The symbol must be exported for the symbol to be found in the library.
             */
            void* GetSymbol( const std::string& symbolName ) const;

        protected:

            /**
             * If an error occurred while loading a dynamic library,
             * use this method to discover the error.
             */
            std::string GetPluginError();

            // The name of the library to load.
            std::wstring    m_PluginName;
            // Handle to the loaded library.
            DYNLIB_HANDLE   m_hInst;

        private:
            // Private getters and setters for the properties.
            const std::wstring& get_PluginName() const
            {
                return m_PluginName;
            }
            void set_PluginName( const std::wstring& )
            {
                // Throw an exception that this variable should not be set.
                throw std::exception("ReadOnlyError: Plugin::PluginName can only be set in the constructor.");
            }

        public:
            PROPERTY( const std::wstring&, PluginName );
        };
    }
}

#endif // ILL_CORE_PLUGIN_HPP