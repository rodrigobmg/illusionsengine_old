/**
 * @file Platform.h
 * @date September 25, 2009
 *
 * Create some platform specific macros from platform specific macros.
 */

#ifndef ILL_CORE_PLATFORM_HPP
#define ILL_CORE_PLATFORM_HPP

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


// Win32 compilers use _DEBUG for specifying debug builds. Other compilers
// may define the DEBUG symbol if debug is enabled.
#if defined _DEBUG || defined DEBUG
#   define ILL_DEBUG 1
#endif // defined _DEBUG || defined DEBUG

// A quick define to overcome different names for the same function
#define stricmp strcasecmp

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

typedef int int32;
typedef short int16;
typedef char int8;

// define 64-bit integer type
#if ILL_COMPILER == ILL_COMPILER_MSVC
    typedef unsigned __int64 uint64;
    typedef __int64 int64;
#else
    typedef unsigned long long uint64;
    typedef long long int64;
#endif

// Include the Platform specific headers.
#if ILL_PLATFORM == ILL_PLATFORM_WIN32
#   include <Ill/Core/CoreWin32.hpp>
#elif ILL_PLATFORM == ILL_PLATFORM_APPLE
#   include <Ill/Core/CoreApple.hpp>
#elif ILL_PLATFORM == ILL_PLATFORM_LINUX
#   include <Ill/Core/CoreLinux.hpp>
#endif // ILL_PLATFORM == ILL_PLATFORM_WIN32

// Include the DLL export definitions.
#include <Ill/Core/CoreExports.hpp>

#endif // ILL_CORE_PLATFORM_HPP