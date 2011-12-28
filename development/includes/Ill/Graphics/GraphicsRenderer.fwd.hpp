#ifndef ILL_GRAPHICS_GRAPHICSRENDERER_FWD_HPP
#define ILL_GRAPHICS_GRAPHICSRENDERER_FWD_HPP

namespace Ill
{
    namespace Graphics
    {
        class GraphicsRenderer;
        typedef boost::shared_ptr< GraphicsRenderer > GraphicsRendererPtr;
        typedef boost::weak_ptr< GraphicsRenderer > GraphicsRendererWeakPtr;
    }
}

#endif // ILL_GRAPHICS_GRAPHICSRENDERER_FWD_HPP