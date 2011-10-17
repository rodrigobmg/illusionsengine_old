/**
 * @file PhysicsExports.hpp
 * @date October 17, 2011
 * @author Jeremiah van Oosten
 *
 * Define the macros of exporting/importing DLL interface types.
 */
//----------------------------------------------------------------------------

#ifndef ILL_PHYSICSEXPORTS_HPP
#define ILL_PHYSICSEXPORTS_HPP

// Windows Export Settings
#if ILL_PLATFORM == ILL_PLATFORM_WIN32

// If we're not including this from a client build, specify that the stuff
// should get exported. Otherwise, import it.
#	if defined( PHYSICS_STATIC_LIB )
#   	define PHYSICS_DLL
#   	define PHYSICS_PRIVATE
#   else
#   	if defined( PHYSICS_EXPORTS )
#       	define PHYSICS_DLL __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define PHYSICS_DLL
#           else
#       	    define PHYSICS_DLL __declspec( dllimport )
#           endif
#   	endif
#   	define PHYSICS_PRIVATE
#	endif

#elif ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE

// Enable GCC symbol visibility
#   if defined( PHYSICS_GCC_VISIBILITY )
#       define PHYSICS_DLL  __attribute__ ((visibility("default")))
#       define PHYSICS_PRIVATE __attribute__ ((visibility("hidden")))
#   else
#       define PHYSICS_DLL
#       define PHYSICS_PRIVATE
#   endif
#endif // ILL_PLATFORM == ILL_PLATFORM_LINUX || ILL_PLATFORM == ILL_PLATFORM_APPLE 

#endif // ILL_PHYSICSEXPORTS_HPP