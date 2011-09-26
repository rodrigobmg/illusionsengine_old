#ifndef ILL_CORE_GAMEOBJECT_HPP
#define ILL_CORE_GAMEOBJECT_HPP

/**
 * @file GameObject.hpp
 * @date September 22, 2011
 * @author Jeremiah van Oosten
 * 
 * @brief A Game Object is the basic entity that can exist in the game world.
 * At a minimum, the game object consists of a transformation component which
 * represents it's position and orientation in 3D space.
 * Components can be added to the game object. The components that are added
 * to the game object will determine it's functionality in the world.
 */

#include <Ill/Core/Object.hpp>
 #include <Ill/Core/Component.hpp>
 #include <Ill/Core/TransformComponent.hpp>

namespace Ill
{
    namespace Core
    {
        class _IllExport GameObject : public Object
        {
        public:
            typedef std::vector<Component::WeakPtr> ComponentList;

            CLASS( GameObject, Object );
            CONSTRUCTOR( public, GameObject, () );

            // Add a component to the GameObject's component list.
            // @returns the component that was added to the list.
            METHOD( public, Component::Ptr, AddComponent, ( Component::Ptr component ) );

            // Retrieve the first component in the component list that matches the class type.
            METHOD( public, Component::WeakPtr, GetComponent, ( const Class& type ) );

            // Retrieve all the components in the component list that matches the class type.
            METHOD( public, ComponentList, GetComponents, ( const Class& type ) );
        protected:
            


        private:
            // A component map stores the UUID of the component as a hash value.
            typedef std::map< std::size_t , Component::Ptr > ComponentMap;

            const TransformComponent::WeakPtr get_Transform() const;
            void set_Transform( const TransformComponent::WeakPtr transform );

            TransformComponent::Ptr m_TransformPtr;
            ComponentMap m_Components;

        public:
            PROPERTY( const TransformComponent::WeakPtr, Transform );
        };
    }
}

#endif // ILL_CORE_GAMEOBJECT_HPP