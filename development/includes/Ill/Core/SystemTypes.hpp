/**
 * @file SystemTypes.hpp
 * @date September 25, 2009
 */

#ifndef ILL_CORE_SYSTEMTYPES_HPP
#define ILL_CORE_SYSTEMTYPES_HPP

#include <string>

namespace Ill
{
    namespace Core
    {
        // Convert to wide-character string
        std::wstring ConvertStringA( const std::string& fromString );
        std::wstring ConvertStringA( const std::wstring& fromString );

        // Convert to single-character string
        std::string ConvertStringW( const std::wstring& fromString );
        std::string ConvertStringW( const std::string& fromString );

#ifdef UNICODE
        typedef std::wstring _StringBase;
#define ConvertString ConvertStringW
#else
        typedef std::string _StringBase;
#define ConvertString ConvertStringA
#endif
        typedef _StringBase String;



    }
}

#endif