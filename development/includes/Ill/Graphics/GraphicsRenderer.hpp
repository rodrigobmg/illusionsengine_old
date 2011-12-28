/**
 * @file GraphicsRenderer.hpp
 * @date September 25, 2009
 *
 * The GraphicsRenderer abstract base class is the main interface that all 
 * implementations must derive from.
 */

#ifndef ILL_GRAPHICS_GRAPHICSRENDERER_HPP
#define ILL_GRAPHICS_GRAPHICSRENDERER_HPP

#include <Ill/Core/Object.hpp>
#include <Ill/Core/PropertyMap.hpp>
#include <Ill/Graphics/GraphicsRenderer.fwd.hpp>

namespace Ill
{
    namespace Graphics
    {
        class GRAPHICS_DLL GraphicsRenderer : public Ill::Core::Object
        {
        public:
            CLASS( GraphicsRenderer, Ill::Core::Object );
            // This is an abstract class, no constructor.

            /**
             * Parse the properties map for startup parameters.
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, bool, GetProperties, (const Ill::Core::PropertyMap& properties) ) = 0;

            /**
             * Initialize the graphics renderer. The "GetProperties" method should be called
             * first to store the startup options, otherwise default options will be used.
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, bool, Initialize, () ) = 0;

            /**
             * Terminiate the graphics renderer.  Cleanup any memory used by the renderer
             * in this method.
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, void, Terminate, () ) = 0;

        protected:
            

        };
    }
}

#endif // ILL_GRAPHICS_GRAPHICSRENDERER_HPP