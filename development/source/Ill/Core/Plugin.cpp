/**
 * @file Plugin.cpp
 * @date September 25, 2009
 */

#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/Plugin.hpp>

namespace Ill
{
    namespace Core
    {
        Plugin::Plugin( const std::wstring& libName )
            : m_PluginName( libName )
            , m_hInst ( NULL )
        {}

        Plugin::~Plugin()
        {
            // The Lib should be unloaded.
            BOOST_ASSERT( m_hInst == NULL );
        }

        void Plugin::Load()
        {
            std::wstring name = m_PluginName;
            fs::path filePath( m_PluginName );
            if ( !filePath.has_extension() )
            {
#if ILL_PLATFORM == ILL_PLATFORM_WIN32
                filePath.replace_extension( L".dll" );
#elif ILL_PLATFORM == ILL_PLATFORM_LINUX
                filePath.replace_extension( L".so" );
#elif ILL_PLATFORM == ILL_PLATFORM_APPLE
                filePath.replace_extension( L".bundle" );
#endif
            }

            m_hInst = (DYNLIB_HANDLE)DYNLIB_LOAD( filePath.string().c_str() );

            if( !m_hInst ) 
            {
                std::string msg;
                msg = std::string( "Could not load dynamic library " ) + ConvertString(m_PluginName) + std::string( ". System Error: " ) + GetPluginError();
                throw std::exception( msg.c_str() ); // TODO: Create a more elaborate exception classes to store more information.
            }
        }

        void Plugin::Unload()
        {
            if( m_hInst == NULL || DYNLIB_UNLOAD( m_hInst ) )
            {
                std::string msg = std::string( "Could not unload dynamic library " ) + ConvertString(m_PluginName) + std::string( ". System Error: " ) + GetPluginError();
                throw std::exception(msg.c_str()); // TODO: Create a more elaborate exception classes to store more information and can accept wide character strings in UNICODE mode!.
            }
            m_hInst = NULL;
        }

        void* Plugin::GetSymbol( const std::string& strName ) const
        {
            BOOST_ASSERT( m_hInst != NULL );
            return (void*)DYNLIB_GETSYM( m_hInst, strName.c_str() );
        }

        std::string Plugin::GetPluginError( void ) 
        {
#if ILL_PLATFORM == ILL_PLATFORM_WIN32
            LPVOID lpMsgBuf; 
            FormatMessage( 
                FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                FORMAT_MESSAGE_FROM_SYSTEM | 
                FORMAT_MESSAGE_IGNORE_INSERTS, 
                NULL, 
                GetLastError(), 
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                (LPTSTR) &lpMsgBuf, 
                0, 
                NULL 
                ); 
            std::string ret = (char*)lpMsgBuf;
            // Free the buffer.
            LocalFree( lpMsgBuf );
            return ret;
#elif ILL_PLATFORM == ILL_PLATFORM_LINUX
            return std::string(dlerror());
#elif ILL_PLATFORM == ILL_PLATFORM_APPLE
            return std::string(mac_errorBundle());
#else
            return std::string( "" );
#endif
        }

    }
}