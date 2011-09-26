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
                gmtl::Matrix44f translateMatrix = gmtl::makeTrans<gmtl::Matrix44f>( m_Position );
                gmtl::Matrix44f scaleMatrix = gmtl::makeScale<gmtl::Matrix44f>( m_Scale );
                gmtl::Matrix44f rotationMatrix = gmtl::makeRot<gmtl::Matrix44f>( m_Rotation );

                m_LocalToWorldMatrix = translateMatrix * rotationMatrix * scaleMatrix;
            }
        }

        gmtl::Vec3f TransformComponent::get_Scale() const
        {
            return m_Scale;
        }

        void TransformComponent::set_Scale( gmtl::Vec3f scale )
        {
            m_Scale = scale;
            m_bTransformDirty = true;
        }

        gmtl::Vec3f TransformComponent::get_Position() const
        {
            return m_Position;
        }

        void TransformComponent::set_Position( gmtl::Vec3f position )
        {
            m_Position = position;
            m_bTransformDirty = true;
        }

        gmtl::Quatf TransformComponent::get_Rotation() const
        {
            return m_Rotation;
        }

        void TransformComponent::set_Rotation( gmtl::Quatf rotation )
        {
            m_Rotation = rotation;
            m_bTransformDirty = true;
        }

    }
}