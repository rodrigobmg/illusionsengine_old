#ifndef ILL_SYSTEM_BOOSTINCLUDE_HPP
#define ILL_SYSTEM_BOOSTINCLUDE_HPP

/**
* @file BoostInclude.h
* @date April 14, 2009
* @author Jeremiah van Oosten
* 
* @brief Include all boost headers that are required by other projects using the Core library.
* @note Any project that uses the Core library, must also include the /boost_<version> directory
* in it's include search path.  At the time of this writing, the boost version was 1_38_0.
*/

// Boost common includes
#include <boost/assert.hpp>
#include <boost/filesystem.hpp>
#include <boost/any.hpp>

#endif // ILL_SYSTEM_BOOSTINCLUDE_HPP