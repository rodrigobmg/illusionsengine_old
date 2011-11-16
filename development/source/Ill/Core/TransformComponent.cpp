#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/TransformComponent.hpp>

namespace Ill
{
    namespace Core
    {
        TransformComponent::TransformComponent()
        {}

        void TransformComponent::Update(float)
        {
            if ( m_bTransformDirty )
            {
                glm::mat4 translate = glm::translate( m_Position );
                glm::mat4 rotate = glm::toMat4( m_Rotation );
                glm::mat4 scale = glm::scale( m_Scale );
                // TODO: Find out if this is the right order 
                m_LocalToWorldMatrix = translate * rotate * scale;
            }
        }

        glm::vec3 TransformComponent::get_Scale() const
        {
            return m_Scale;
        }

        void TransformComponent::set_Scale( glm::vec3 scale )
        {
            m_Scale = scale;
            m_bTransformDirty = true;
        }

        glm::vec3 TransformComponent::get_Position() const
        {
            return m_Position;
        }

        void TransformComponent::set_Position( glm::vec3 position )
        {
            m_Position = position;
            m_bTransformDirty = true;
        }

        glm::quat TransformComponent::get_Rotation() const
        {
            return m_Rotation;
        }

        void TransformComponent::set_Rotation( glm::quat rotation )
        {
            m_Rotation = rotation;
            m_bTransformDirty = true;
        }

    }
}