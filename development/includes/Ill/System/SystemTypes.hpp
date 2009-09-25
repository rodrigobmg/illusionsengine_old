/**
 * @file SystemTypes.hpp
 * @date September 25, 2009
 */

#ifndef ILL_SYSTEM_SYSTEMTYPES_HPP
#define ILL_SYSTEM_SYSTEMTYPES_HPP

namespace Ill
{
    namespace System
    {
#ifdef UNICODE
        typedef std::wstring _StringBase;
#else
        typedef std::string _StringBase;
#endif
        typedef _StringBase String;

    }
}

#endif