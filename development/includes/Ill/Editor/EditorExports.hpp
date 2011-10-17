/**
 * @file EditorExports.hpp
 * @date October 17, 2011
 * @author Jeremiah van Oosten
 *
 * Define the macros of exporting/importing DLL interface types.
 */
//----------------------------------------------------------------------------

#ifndef ILL_EDITOREXPORTS_HPP
#define ILL_EDITOREXPORTS_HPP

// Windows Export Settings
#if ILL_PLATFORM == ILL_PLATFORM_WIN32

// If we're not including this from a client build, specify that the stuff
// should get exported. Otherwise, import it.
#	if defined( EDITOR_STATIC_LIB )
#   	define EDITOR_DLL
#   	define EDITOR_PRIVATE
#   else
#   	if defined( EDITOR_EXPORTS )
#       	define EDITOR_DLL __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define EDITOR_DLL
#           else
#       	    define EDITOR_DLL __declspec( dllimport )
#           endif
#   	endif
#   	define EDITOR_PRIVATE
#	endif

#elif ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE

// Enable GCC symbol visibility
#   if defined( EDITOR_GCC_VISIBILITY )
#       define EDITOR_DLL  __attribute__ ((visibility("default")))
#       define EDITOR_PRIVATE __attribute__ ((visibility("hidden")))
#   else
#       define EDITOR_DLL
#       define EDITOR_PRIVATE
#   endif
#endif // ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE 

#endif // ILL_EDITOREXPORTS_HPP