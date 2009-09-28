/**
 * @file SystemTypes.hpp
 * @date September 25, 2009
 */

#ifndef ILL_SYSTEM_SYSTEMTYPES_HPP
#define ILL_SYSTEM_SYSTEMTYPES_HPP

#include <string>

namespace Ill
{
    namespace System
    {
        // Convert to wide-character string
        std::wstring ConvertStringW( const std::string& fromString );
        std::wstring ConvertStringW( const std::wstring& fromString );

        // Convert to single-character string
        std::string ConvertStringA( const std::wstring& fromString );
        std::string ConvertStringA( const std::string& fromString );

#ifdef UNICODE
        typedef std::wstring _StringBase;
#define ConvertString ConvertStringA
#else
        typedef std::string _StringBase;
#define ConvertString ConvertStringW
#endif
        typedef _StringBase String;



    }
}

#endif