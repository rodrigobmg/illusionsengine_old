/**
 * @file CoreExports.hpp
 * @date October 17, 2011
 * @author Jeremiah van Oosten
 *
 * Define the macros of exporting/importing DLL interface types.
 */
//----------------------------------------------------------------------------

#ifndef ILL_COREEXPORTS_HPP
#define ILL_COREEXPORTS_HPP

// Windows Export Settings
#if ILL_PLATFORM == ILL_PLATFORM_WIN32

// If we're not including this from a client build, specify that the stuff
// should get exported. Otherwise, import it.
#	if defined( CORE_STATIC_LIB )
#   	define CORE_DLL
#   	define CORE_PRIVATE
#   else
#   	if defined( CORE_EXPORTS )
#       	define CORE_DLL __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define CORE_DLL
#           else
#       	    define CORE_DLL __declspec( dllimport )
#           endif
#   	endif
#   	define CORE_PRIVATE
#	endif

#elif ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE

// Enable GCC symbol visibility
#   if defined( CORE_GCC_VISIBILITY )
#       define CORE_DLL  __attribute__ ((visibility("default")))
#       define CORE_PRIVATE __attribute__ ((visibility("hidden")))
#   else
#       define CORE_DLL
#       define CORE_PRIVATE
#   endif
#endif // ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE 

#endif // ILL_COREEXPORTS_HPP