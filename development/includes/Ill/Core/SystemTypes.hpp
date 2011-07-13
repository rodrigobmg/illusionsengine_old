/**
 * @file SystemTypes.hpp
 * @date September 25, 2009
 */

#ifndef ILL_CORE_SYSTEMTYPES_HPP
#define ILL_CORE_SYSTEMTYPES_HPP

#include <locale>
#include <string>

// Converts a wide character string to a multi-byte string.
std::string ConvertString( const std::wstring& strW );

#endif // ILL_CORE_SYSTEMTYPES_HPP