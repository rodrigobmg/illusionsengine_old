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
            glm::vec3 get_Scale() const;
            void set_Scale( glm::vec3 scale );

            glm::vec3 get_Position() const;
            void set_Position( glm::vec3 position );

            glm::quat get_Rotation() const;
            void set_Rotation( glm::quat rotation );

            // Private member variables.            
            glm::vec3   m_Scale;
            glm::vec3   m_Position;
            glm::quat   m_Rotation;

            glm::mat4   m_LocalToWorldMatrix;
            glm::mat4   m_WorldToLocalMatrix;

            bool        m_bTransformDirty;
        public:
            PROPERTY( CORE_DLL, glm::vec3, Scale );
            PROPERTY( CORE_DLL, glm::vec3, Position );
            PROPERTY( CORE_DLL, glm::quat, Rotation );
            
        };
    }
}

#endif // ILL_CORE_TRANSFORMCOMPONENT_HPP