#include <Ill/Core/CorePCH.hpp>
//#include <Ill/Core/TransformComponent.hpp>
#include <Ill/Core/GameObject.hpp>

namespace Ill
{
    namespace Core
    {
        GameObject::GameObject()
            : m_TransformPtr( new TransformComponent() )
        {

        }

        Component::Ptr GameObject::AddComponent( Component::Ptr component )
        {
            typedef std::pair< ComponentMap::iterator, bool > InsertIterator;
            InsertIterator returnValue;
            
            std::size_t hashID = hash_value( component->UUID );

            // Insert the new component into the components list
            returnValue = m_Components.insert( ComponentMap::value_type( hashID, component ) );

            if ( returnValue.second == false )
            {
                // The value was already found in the component list for this game object.
                // This should generate an error if the same component is added multiple times to the same
                // game object.
                assert(false);
            }

            // Return the Component pointer that was inserted, or the value that was already in the map with the same hash ID.
            return returnValue.first->second;
        }

        Component::WeakPtr GameObject::GetComponent( const Class& typeID )
        {
            // Find the first component with the give class ID
            ComponentMap::iterator iter = m_Components.begin();
            while ( iter != m_Components.end() )
            {
                Component::Ptr pComponent = (*iter).second;
                if ( typeID.isSame( pComponent->getClass() ) || typeID.isBase( pComponent->getClass() ) )
                {
                    return pComponent;
                }
                ++iter;
            }

            // No component found.  Return an empty weak pointer.
            return Component::WeakPtr();
        }

        GameObject::ComponentList GameObject::GetComponents( const Class& typeID )
        {
            ComponentList result;

            ComponentMap::iterator iter = m_Components.begin();
            while ( iter != m_Components.end() )
            {
                Component::Ptr pComponent = (*iter).second;
                if ( typeID.isSame( pComponent->getClass() ) || typeID.isBase( pComponent->getClass() ) )
                {
                    result.push_back( pComponent );
                }
                ++iter;
            }

            return result;
        }

        const TransformComponent::WeakPtr GameObject::get_Transform() const
        {
            return m_TransformPtr;
        }

        void GameObject::set_Transform( const TransformComponent::WeakPtr transform )
        {
            m_TransformPtr = transform.lock();
        }

    }
}