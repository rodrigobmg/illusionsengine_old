/**
 * @file: GraphicsSubsystem.hpp
 * @date: September 18, 2009
 * 
 * The GraphicsSubsystem is used to create and manage the graphics renderer.
 *
 */

#ifndef ILL_GRAPHICS_GRAPHICSSUBSYSTEM_HPP
#define ILL_GRAPHICS_GRAPHICSSUBSYSTEM_HPP

#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/Application.fwd.hpp>
#include <Ill/Graphics/GraphicsTypes.hpp>
#include <Ill/Graphics/GraphicsRenderer.fwd.hpp>

namespace Ill
{
    namespace Graphics
    {
        class GRAPHICS_DLL GrapicsSubsystem : public Ill::Core::Subsystem
        {
        public:

            CLASS( GrapicsSubsystem, Ill::Core::Subsystem );
//            CONSTRUCTOR( GRAPHICS_DLL, public, GrapicsSubsystem, () );

            /**
            * Initialize the graphics subsystem.
            */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, void, Initialize, () );
       
            /**
            * Terminate the graphics subsystem.
            */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, void, Terminate, () );

            /**
             * Retrieve a pointer to the GraphicsRenderer implementation.
             * @precondition The subsystem must have been initialized before
             * you can get a pointer to the GraphicsRenderer implementation.
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, GraphicsRendererPtr, GetGraphicsRenderer, () ) = 0;

        protected:

        };
    }
}

#endif // ILL_GRAPHICS_GRAPHICSSUBSYSTEM_HPP