/**
 * @file CoreExports.hpp
 * @date October 17, 2011
 * @author Jeremiah van Oosten
 *
 * Define the macros of exporting/importing DLL interface types.
 */
//----------------------------------------------------------------------------

#ifndef ILL_GAMEEXPORTS_HPP
#define ILL_GAMEEXPORTS_HPP

// Windows Export Settings
#if ILL_PLATFORM == ILL_PLATFORM_WIN32

// If we're not including this from a client build, specify that the stuff
// should get exported. Otherwise, import it.
#	if defined( GAME_STATIC_LIB )
#   	define GAME_DLL
#   	define GAME_PRIVATE
#   else
#   	if defined( GAME_EXPORTS )
#       	define GAME_DLL __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define GAME_DLL
#           else
#       	    define GAME_DLL __declspec( dllimport )
#           endif
#   	endif
#   	define GAME_PRIVATE
#	endif

#elif ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE

// Enable GCC symbol visibility
#   if defined( GAME_GCC_VISIBILITY )
#       define GAME_DLL  __attribute__ ((visibility("default")))
#       define GAME_PRIVATE __attribute__ ((visibility("hidden")))
#   else
#       define GAME_DLL
#       define GAME_PRIVATE
#   endif
#endif // ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE 

#endif // ILL_GAMEEXPORTS_HPP