/**
 * @file OgrePluginExports.hpp
 * @date October 17, 2011
 * @author Jeremiah van Oosten
 *
 * Define the macros of exporting/importing DLL interface types.
 */
//----------------------------------------------------------------------------

#ifndef ILL_OGREPLUGINEXPORTS_HPP
#define ILL_OGREPLUGINEXPORTS_HPP

// Windows Export Settings
#if ILL_PLATFORM == ILL_PLATFORM_WIN32

// If we're not including this from a client build, specify that the stuff
// should get exported. Otherwise, import it.
#	if defined( OGREPLUGIN_STATIC_LIB )
#   	define OGREPLUGIN_DLL
#   	define OGREPLUGIN_PRIVATE
#   else
#   	if defined( OGREPLUGIN_EXPORTS )
#       	define OGREPLUGIN_DLL __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define OGREPLUGIN_DLL
#           else
#       	    define OGREPLUGIN_DLL __declspec( dllimport )
#           endif
#   	endif
#   	define OGREPLUGIN_PRIVATE
#	endif

#elif ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE

// Enable GCC symbol visibility
#   if defined( OGREPLUGIN_GCC_VISIBILITY )
#       define OGREPLUGIN_DLL  __attribute__ ((visibility("default")))
#       define OGREPLUGIN_PRIVATE __attribute__ ((visibility("hidden")))
#   else
#       define OGREPLUGIN_DLL
#       define OGREPLUGIN_PRIVATE
#   endif
#endif // ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE 

#endif // ILL_OGREPLUGINEXPORTS_HPP