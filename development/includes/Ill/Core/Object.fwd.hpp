#ifndef ILL_CORE_OBJECT_FWD_HPP
#define ILL_CORE_OBJECT_FWD_HPP
/**
 * Forward declaration for the Object type.
 */
namespace Ill
{
    namespace Core
    {
        class Object;
//        DECLARE_PTR( Object );
        typedef boost::shared_ptr<Object> ObjectPtr;
        typedef boost::weak_ptr<Object> ObjectWeakPtr;

    }
}

#endif // ILL_CORE_OBJECT_FWD_HPP