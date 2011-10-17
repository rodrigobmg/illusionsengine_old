/**
 * @file GraphicsExports.hpp
 * @date October 17, 2011
 * @author Jeremiah van Oosten
 *
 * Define the macros of exporting/importing DLL interface types.
 */
//----------------------------------------------------------------------------

#ifndef ILL_GRAPHICSEXPORTS_HPP
#define ILL_GRAPHICSEXPORTS_HPP

// Windows Export Settings
#if ILL_PLATFORM == ILL_PLATFORM_WIN32

// If we're not including this from a client build, specify that the stuff
// should get exported. Otherwise, import it.
#	if defined( GRAPHICS_STATIC_LIB )
#   	define GRAPHICS_DLL
#   	define GRAPHICS_PRIVATE
#   else
#   	if defined( GRAPHICS_EXPORTS )
#       	define GRAPHICS_DLL __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define GRAPHICS_DLL
#           else
#       	    define GRAPHICS_DLL __declspec( dllimport )
#           endif
#   	endif
#   	define GRAPHICS_PRIVATE
#	endif

#elif ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE

// Enable GCC symbol visibility
#   if defined( GRAPHICS_GCC_VISIBILITY )
#       define GRAPHICS_DLL  __attribute__ ((visibility("default")))
#       define GRAPHICS_PRIVATE __attribute__ ((visibility("hidden")))
#   else
#       define GRAPHICS_DLL
#       define GRAPHICS_PRIVATE
#   endif
#endif // ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE 

#endif // ILL_GRAPHICSEXPORTS_HPP