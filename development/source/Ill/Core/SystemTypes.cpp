/**
 * @file SystemTypes.cpp
 * @date September 28, 2009
 * 
 * 
 */

#include <Ill/Core/CorePCH.hpp>

namespace Ill
{
    namespace Core
    {
        // Convert to wide-character string
        std::wstring ConvertStringW( const std::string& fromString )
        {
            std::wstring temp( fromString.length(), L' ' );
            std::copy( fromString.begin(), fromString.end(), temp.begin() );
            return temp;
        }

        std::wstring ConvertStringW( const std::wstring& fromString )
        {
            return fromString;
        }


        // Convert to single-character string
        std::string ConvertStringA( const std::wstring& fromString )
        {
            std::string temp( fromString.length(), ' ' );
            std::copy( fromString.begin(), fromString.end(), temp.begin() );
            return temp;
        }

        std::string ConvertStringA( const std::string& fromString )
        {
            return fromString;
        }
    }
}