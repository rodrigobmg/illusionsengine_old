/**
 * @file GraphicsRenderer.hpp
 * @date September 25, 2009
 *
 * The GraphicsRenderer abstract base class is the main interface that all 
 * implementation must derive from.
 */

#ifndef ILL_SYSTEM_GRAPHICS_GRAPHICSRENDERER_HPP
#define ILL_SYSTEM_GRAPHICS_GRAPHICSRENDERER_HPP

namespace Ill
{
    namespace System
    {
        namespace Graphics
        {
            class GraphicsRenderer : public Ill::System::Object
            {
            public:
                CLASS(GraphicsRenderer,Ill::System::Object);

                // This is an abstract class, no constructor.


            };

            typedef boost::intrusive_ptr<GraphicsRenderer> GraphicsRendererPtr;
        }
    }
}

#endif // ILL_SYSTEM_GRAPHICS_GRAPHICSRENDERER_HPP