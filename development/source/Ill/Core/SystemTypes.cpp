/**
 * @file SystemTypes.cpp
 * @date September 28, 2009
 * 
 * 
 */

#include <Ill/Core/CorePCH.hpp>

std::string ConvertString( const std::wstring& strW )
{
    typedef std::codecvt<wchar_t, char, mbstate_t> codecvt_t;
    typedef codecvt_t::result result_type;

    std::locale mylocale;
    // The code conversion facet that is used to perform the conversion.
    const codecvt_t& facet = std::use_facet< codecvt_t >(mylocale);

    // State object to keep track of the state of a multibyte character conversion.
    mbstate_t   mystate = mbstate_t();

    // A pointer to the current character of the input string.
    // When the function returns, this points to the element in the source range
    // beyond the last one successfully translated.
    const wchar_t* inputIterator = NULL;

    // The destination sequence
    std::string strA( strW.length()+1, 0 );
    // A pointer to the element in the output sequence.
    // When the function returns, this points to the element in the destination 
    // range beyond the last one successfully translated.
    char* outputIterator = NULL;

    result_type result = facet.out( mystate, &(*strW.begin()), &(*strW.end()), inputIterator, &(*strA.begin()), &(*strA.end()), outputIterator );

    return strA;
}
