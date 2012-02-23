#ifndef ILL_CORE_BOOSTINCLUDE_HPP
#define ILL_CORE_BOOSTINCLUDE_HPP

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
#include <boost/filesystem/fstream.hpp>
// Namespace alias for boost's filesystem
namespace fs = boost::filesystem;

// Serialization
#include <boost/serialization/serialization.hpp>

// Property trees
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH

// Smart pointer handling
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

#define DECLARE_PTR( CLASS_NAME )                                       \
    class CLASS_NAME;                                                   \
    typedef boost::shared_ptr<CLASS_NAME> CLASS_NAME##Ptr;              \
    typedef boost::weak_ptr<CLASS_NAME> CLASS_NAME##WeakPtr;

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/signal.hpp>
#include <boost/any.hpp>

// UUID's and Hash
#include <boost/functional/hash.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_serialize.hpp>

namespace Ill
{
    namespace Core
    {
        extern boost::uuids::random_generator uuid_generator;
    }
}

#endif // ILL_CORE_BOOSTINCLUDE_HPP