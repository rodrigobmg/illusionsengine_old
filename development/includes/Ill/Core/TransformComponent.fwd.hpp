#ifndef ILL_CORE_TRANSFORMCOMPONENT_FWD_HPP
#define ILL_CORE_TRANSFORMCOMPONENT_FWD_HPP
/**
 * Forward declaration for the TransformComponent type.
 */

namespace Ill
{
    namespace Core
    {
        class TransformComponent;
//        DECLARE_PTR( TransformComponent ); 
        typedef boost::shared_ptr<TransformComponent> TransformComponentPtr;
        typedef boost::weak_ptr<TransformComponent> TransformComponentWeakPtr;

    }
}

#endif // ILL_CORE_TRANSFORMCOMPONENT_FWD_HPP