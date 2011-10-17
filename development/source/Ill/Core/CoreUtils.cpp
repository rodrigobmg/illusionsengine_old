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
    const wchar_t* inputIterator;
    // A pointer to the element in the output sequence.
    // When the function returns, this points to the element in the destination 
    // range beyond the last one successfully translated.
    char* outputIterator;

    size_t length = strW.length();
    // A temporary buffer to store the result of the translated string.
    char* chA = new char[length + 1];

    result_type result = facet.out( mystate, strW.c_str(), strW.c_str()+length+1, inputIterator, chA , chA+length+1, outputIterator );
    BOOST_ASSERT( result == codecvt_t::ok && "Could not convert the wide-character string to a narrow-character string." );

    std::string strA( chA );

    delete [] chA;

    return strA;
}
