/**
 * @file Horde3DPluginExports.hpp
 * @date December 27, 2011
 * @author Jeremiah van Oosten
 *
 * Define the macros of exporting/importing DLL interface types.
 */
//----------------------------------------------------------------------------

#ifndef ILL_PLUGIN_HORDE3D_EXPORTS_HPP
#define ILL_PLUGIN_HORDE3D_EXPORTS_HPP

// Windows Export Settings
#if ILL_PLATFORM == ILL_PLATFORM_WIN32

// If we're not including this from a client build, specify that the stuff
// should get exported. Otherwise, import it.
#	if defined( HORDE3DPLUGIN_STATIC_LIB )
#   	define HORDE3DPLUGIN_DLL
#   	define HORDE3DPLUGIN_PRIVATE
#   else
#   	if defined( HORDE3DPLUGIN_EXPORTS )
#       	define HORDE3DPLUGIN_DLL __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define HORDE3DPLUGIN_DLL
#           else
#       	    define HORDE3DPLUGIN_DLL __declspec( dllimport )
#           endif
#   	endif
#   	define HORDE3DPLUGIN_PRIVATE
#	endif

#elif ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE

// Enable GCC symbol visibility
#   if defined( HORDE3DPLUGIN_GCC_VISIBILITY )
#       define HORDE3DPLUGIN_DLL  __attribute__ ((visibility("default")))
#       define HORDE3DPLUGIN_PRIVATE __attribute__ ((visibility("hidden")))
#   else
#       define HORDE3DPLUGIN_DLL
#       define HORDE3DPLUGIN_PRIVATE
#   endif
#endif // ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE 

#endif // ILL_PLUGIN_HORDE3D_EXPORTS_HPP