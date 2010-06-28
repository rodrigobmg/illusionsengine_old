/**
 * @file: GraphicsSubsystem.hpp
 * @date: September 18, 2009
 * 
 * The GraphicsSubsystem is used to create and manage the graphics renderer.
 *
 */

#ifndef ILL_SYSTEM_GRAPHICS_GRAPHICSSUBSYSTEM_HPP
#define ILL_SYSTEM_GRAPHICS_GRAPHICSSUBSYSTEM_HPP

#include <Ill/System/Subsystem.hpp>
#include <Ill/System/Graphics/GraphicsTypes.hpp>

// Forward-declaration of Ogre types
namespace Ogre
{
    class Root;
    class SceneManager;
    class Camera;
    class RenderWindow;
}

namespace Ill
{
    namespace System
    {
        namespace Graphics
        {
            class GraphicsRenderer;

            class GrapicsSubsystem : public Ill::System::Subsystem
            {
            public:

                CLASS( GrapicsSubsystem, Ill::System::Subsystem );
                CONSTRUCTOR(public,GrapicsSubsystem,());

                /**
                * Startup the graphics subsystem.
                */
                VIRTUAL_METHOD(public,bool,Startup,( const PropertyMap& startupOptions ));

                /**
                * Shutdown
                */
                VIRTUAL_METHOD(public,bool,Shutdown,());

                /**
                 * Retrieve a pointer to the GraphicsRenderer implementation.
                 * @precondition The subsystem must have been initialized before
                 * you can get a pointer to the GraphicsRenderer implementation.
                 */
                VIRTUAL_METHOD(public, GraphicsRenderer*, GetGraphicsRenderer, () );

            protected:

                /**
                * Populate my defined properties from the passed-in property map
                */
                VIRTUAL_METHOD(public,void,GetProperties,(const PropertyMap& properties) );

            private:
                // Getters and setters for property types
                const String& get_GraphicsLibName() const
                {
                    return m_GraphicsLibName;
                }
                void set_GraphicsLibName( const String& libName )
                {
                    m_GraphicsLibName = libName;
                }

                // Data members
                // The name of graphics library that is used to load the graphics renderer.
                String              m_GraphicsLibName;

                GraphicsRenderer*   m_pGraphicsRenderer;

            public:
                // Define properties at the bottom of the class to avoid VAssistX getting confused and hiding 
                // my member variables from using code-completion.
                PROPERTY(const String&,  GraphicsLibName );
            };

            typedef boost::intrusive_ptr<GrapicsSubsystem> GraphicsSubsystemPtr;
        }
    }
}

#endif // ILL_SYSTEM_GRAPHICS_GRAPHICSSUBSYSTEM_HPP