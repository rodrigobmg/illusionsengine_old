/**
 * @file CoreWin32.hpp
 * @date October 17, 2011
 * @author Jeremiah van Oosten
 *
 * Win32 specific includes for the Core library.
 * 
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#pragma warning (disable : 4251)
