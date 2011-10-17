#ifndef ILL_CORE_TRANSFORMCOMPONENT_HPP
#define ILL_CORE_TRANSFORMCOMPONENT_HPP

/**
 * @file TransformComponent.hpp
 * @date September 22, 2011
 * @author Jeremiah van Oosten
 *
 * @brief The TransformComponent is the basic component that is owned
 * by every game object.
 */
#include <Ill/Core/Component.hpp>
#include <Ill/Core/TransformComponent.fwd.hpp>

namespace Ill
{
    namespace Core
    {
        class CORE_DLL TransformComponent : public Component
        {
        public:
            CLASS( TransformComponent, Component );
            CONSTRUCTOR( CORE_DLL, public, TransformComponent, () );

            /**
             * Update the transform matrices if they are out-of-date.
             */
            VIRTUAL_METHOD( CORE_DLL, public, void, Update, (float elapsedTime) );

        protected:
            
        private:

            // Accessor methods.
            gmtl::Vec3f get_Scale() const;
            void set_Scale( gmtl::Vec3f scale );

            gmtl::Vec3f get_Position() const;
            void set_Position( gmtl::Vec3f position );

            gmtl::Quatf get_Rotation() const;
            void set_Rotation( gmtl::Quatf rotation );

            // Private member variables.            
            gmtl::Vec3f     m_Scale;
            gmtl::Vec3f     m_Position;
            gmtl::Quatf     m_Rotation;

            gmtl::Matrix44f m_LocalToWorldMatrix;
            gmtl::Matrix44f m_WorldToLocalMatrix;

            bool            m_bTransformDirty;
        public:
            PROPERTY( CORE_DLL, gmtl::Vec3f, Scale );
            PROPERTY( CORE_DLL, gmtl::Vec3f, Position );
            PROPERTY( CORE_DLL, gmtl::Quatf, Rotation );
            
        };
    }
}

#endif // ILL_CORE_TRANSFORMCOMPONENT_HPP