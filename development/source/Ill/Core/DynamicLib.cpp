/**
 * @file DynamicLib.cpp
 * @date September 25, 2009
 */

#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/DynamicLib.hpp>

#if ILL_PLATFORM == ILL_PLATFORM_WIN32
#  define WIN32_LEAN_AND_MEAN
#  define NOMINMAX // required to stop windows.h messing up std::min
#  include <windows.h>
#endif

#if ILL_PLATFORM == ILL_PLATFORM_APPLE
#   include "macPlugins.h"
#endif

namespace Ill
{
    namespace Core
    {
        DynamicLib::DynamicLib( const String& libName )
            : m_LibName( libName )
            , m_hInst ( NULL )
        {}

        DynamicLib::~DynamicLib()
        {
            // The Lib should be unloaded.
            BOOST_ASSERT( m_hInst == NULL );
        }

        void DynamicLib::Load()
        {
            String name = m_LibName;

#if ILL_PLATFORM == ILL_PLATFORM_LINUX
            // dlopen() does not add .so to the filename, like windows does for .dll
            if (name.substr(name.length() - 3, 3) != ".so")
            {
                name += ".so";
            }
#endif
            m_hInst = (DYNLIB_HANDLE)DYNLIB_LOAD( name.c_str() );

            if( !m_hInst ) 
            {
                std::string msg;
                msg = std::string( "Could not load dynamic library " ) + ConvertString(m_LibName) + std::string( ". System Error: " ) + GetDynamicLibError();
                throw std::exception( msg.c_str() ); // TODO: Create a more elaborate exception classes to store more information.
            }
        }

        void DynamicLib::Unload()
        {
            if( DYNLIB_UNLOAD( m_hInst ) )
            {
                std::string msg;
                msg = std::string( "Could not unload dynamic library " ) + ConvertString(m_LibName) + std::string( ". System Error: " ) + GetDynamicLibError();
                throw std::exception(msg.c_str()); // TODO: Create a more elaborate exception classes to store more information and can accept wide character strings in UNICODE mode!.
            }
            m_hInst = NULL;
        }

        void* DynamicLib::GetSymbol( const String& strName ) const throw()
        {
            BOOST_ASSERT( m_hInst != NULL );
            return (void*)DYNLIB_GETSYM( m_hInst, ConvertString(strName).c_str() );
        }

        std::string DynamicLib::GetDynamicLibError( void ) 
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