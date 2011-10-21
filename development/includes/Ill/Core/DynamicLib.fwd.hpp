#ifndef ILL_CORE_DYNAMICLIB_FWD_HPP
#define ILL_CORE_DYNAMICLIB_FWD_HPP
/**
 * Forward declaration for plugin type.
 */

namespace Ill
{
    namespace Core
    {
        class DynamicLib;
        //DECLARE_PTR( DynamicLib );
        typedef boost::shared_ptr<DynamicLib> DynamicLibPtr;
        typedef boost::weak_ptr<DynamicLib> DynamicLibWeakPtr;
    }
}

#endif // ILL_CORE_DYNAMICLIB_FWD_HPP