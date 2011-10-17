/**
 * @file CoreUtils.hpp
 * @date September 25, 2009
 * @author Jeremiah van Oosten
 *
 * Utility classes and functions.
 */

#ifndef ILL_CORE_COREUTILS_HPP
#define ILL_CORE_COREUTILS_HPP

// Converts a wide character string to a multi-byte string.
std::string CORE_DLL ConvertString( const std::wstring& strW );

#endif // ILL_CORE_COREUTILS_HPP