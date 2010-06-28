/**
 * @file Platform.h
 * @date September 25, 2009
 *
 * Create some platform specific macros from platform specific macros.
 * Note: These macros are pretty much just ripped from Ogre's (version 1.6.3) OgrePlatform.h
 */

#ifndef ILL_SYSTEM_PLATFORM_HPP
#define ILL_SYSTEM_PLATFORM_HPP

namespace Ill
{
    namespace System
    {
        /**
         * Platform definitions
         */
#define ILL_PLATFORM_WIN32 1
#define ILL_PLATFORM_LINUX 2
#define ILL_PLATFORM_APPLE 3

        /**
         * Compiler definitions
         */
#define ILL_COMPILER_MSVC 1
#define ILL_COMPILER_GNUC 2
#define ILL_COMPILER_BORL 3

        /**
         * Endian definitions
         */
#define ILL_ENDIAN_LITTLE 1
#define ILL_ENDIAN_BIG    2

#define ILL_ARCHITECTURE_32 1
#define ILL_ARCHITECTURE_64 2

        /**
         * Derive the compiler type and version.
         */
#if defined( _MSC_VER )
#   define ILL_COMPILER ILL_COMPILER_MSVC
#   define ILL_COMP_VER _MSC_VER

#elif defined( __GNUC__ )
#   define ILL_COMPILER ILL_COMPILER_GNUC
#   define ILL_COMP_VER (((__GNUC__)*100) + \
    (__GNUC_MINOR__*10) + \
    __GNUC_PATCHLEVEL__)

#elif defined( __BORLANDC__ )
#   define ILL_COMPILER ILL_COMPILER_BORL
#   define ILL_COMP_VER __BCPLUSPLUS__
#   define __FUNCTION__ __FUNC__ 
#else
#   pragma error "No known compiler. Abort! Abort!"
#endif

        /* See if we can use __forceinline or if we need to use __inline instead */
#if ILL_COMPILER == ILL_COMPILER_MSVC
#   if ILL_COMP_VER >= 1200
#       define FORCEINLINE __forceinline
#   endif
#elif defined(__MINGW32__)
#   if !defined(FORCEINLINE)
#       define FORCEINLINE __inline
#   endif
#else
#   define FORCEINLINE __inline
#endif

        /**
         * Determine the platform
         */ 
#if defined( __WIN32__ ) || defined( _WIN32 )
#   define ILL_PLATFORM ILL_PLATFORM_WIN32

#elif defined( __APPLE_CC__)
#   define ILL_PLATFORM ILL_PLATFORM_APPLE

#else
#   define ILL_PLATFORM ILL_PLATFORM_LINUX
#endif

        /* Find the arch type */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define ILL_ARCH_TYPE ILL_ARCHITECTURE_64
#else
#   define ILL_ARCH_TYPE ILL_ARCHITECTURE_32
#endif

        // For generating compiler warnings - should work on any compiler
        // As a side note, if you start your message with 'Warning: ', the MSVC
        // IDE actually does catch a warning :)
#define ILL_QUOTE_INPLACE(x) # x
#define ILL_QUOTE(x) ILL_QUOTE_INPLACE(x)
#define ILL_WARN( x )  message( __FILE__ "(" QUOTE( __LINE__ ) ") : " x "\n" )

        //----------------------------------------------------------------------------
        // Windows Settings
#if ILL_PLATFORM == ILL_PLATFORM_WIN32

        // If we're not including this from a client build, specify that the stuff
        // should get exported. Otherwise, import it.
#	if defined( ILL_STATIC_LIB )
        // Linux compilers don't have symbol import/export directives.
#   	define _IllExport
#   	define _IllPrivate
#   else
#   	if defined( ILL_EXPORT )
#       	define _IllExport __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define _IllExport
#           else
#       	    define _IllExport __declspec( dllimport )
#           endif
#   	endif
#   	define _IllPrivate
#	endif
        // Win32 compilers use _DEBUG for specifying debug builds.
#   ifdef _DEBUG
#       define ILL_DEBUG_MODE 1
#   else
#       define ILL_DEBUG_MODE 0
#   endif

        // Disable unicode support on MingW at the moment, poorly supported in stdlibc++
        // STLPORT fixes this though so allow if found
        // MinGW C++ Toolkit supports unicode and sets the define __MINGW32_TOOLKIT_UNICODE__ in _mingw.h
#if defined( __MINGW32__ ) && !defined(_STLPORT_VERSION)
#   include<_mingw.h>
#   if defined(__MINGW32_TOOLBOX_UNICODE__)
#	    define ILL_UNICODE_SUPPORT 1
#   else
#       define ILL_UNICODE_SUPPORT 0
#   endif
#else
#	define ILL_UNICODE_SUPPORT 1
#endif

#endif
        //----------------------------------------------------------------------------

        //----------------------------------------------------------------------------
        // Linux/Apple Settings
#if ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE

        // Enable GCC symbol visibility
#   if defined( ILL_GCC_VISIBILITY )
#       define _IllExport  __attribute__ ((visibility("default")))
#       define _IllPrivate __attribute__ ((visibility("hidden")))
#   else
#       define _IllExport
#       define _IllPrivate
#   endif

        // A quick define to overcome different names for the same function
#   define stricmp strcasecmp

        // Unlike the Win32 compilers, Linux compilers seem to use DEBUG for when
        // specifying a debug build.
        // (??? this is wrong, on Linux debug builds aren't marked in any way unless
        // you mark it yourself any way you like it -- zap ???)
#   ifdef DEBUG
#       define ILL_DEBUG_MODE 1
#   else
#       define ILL_DEBUG_MODE 0
#   endif

#if ILL_PLATFORM == ILL_PLATFORM_APPLE
#define ILL_PLATFORM_LIB "OgrePlatform.bundle"
#else
        //ILL_PLATFORM_LINUX
#define ILL_PLATFORM_LIB "libOgrePlatform.so"
#endif

        // Always enable unicode support for the moment
        // Perhaps disable in old versions of gcc if necessary
#define ILL_UNICODE_SUPPORT 1

#endif

        //For apple, we always have a custom config.h file
//#if ILL_PLATFORM == ILL_PLATFORM_APPLE
//#    include "config.h"
//#endif

        //----------------------------------------------------------------------------

        //----------------------------------------------------------------------------
        // Endian Settings
        // check for BIG_ENDIAN config flag, set ILL_ENDIAN correctly
#ifdef ILL_CONFIG_BIG_ENDIAN
#    define ILL_ENDIAN ILL_ENDIAN_BIG
#else
#    define ILL_ENDIAN ILL_ENDIAN_LITTLE
#endif

        // Integer formats of fixed bit width
        typedef unsigned int uint32;
        typedef unsigned short uint16;
        typedef unsigned char uint8;
        // define uint64 type
#if ILL_COMPILER == ILL_COMPILER_MSVC
        typedef unsigned __int64 uint64;
#else
        typedef unsigned long long uint64;
#endif

    }
}

#endif // ILL_SYSTEM_PLATFORM_HPP