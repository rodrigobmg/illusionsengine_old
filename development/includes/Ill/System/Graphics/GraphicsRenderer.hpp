/**
 * @file GraphicsRenderer.hpp
 * @date September 25, 2009
 *
 * The GraphicsRenderer abstract base class is the main interface that all 
 * implementations must derive from.
 */

#ifndef ILL_SYSTEM_GRAPHICS_GRAPHICSRENDERER_HPP
#define ILL_SYSTEM_GRAPHICS_GRAPHICSRENDERER_HPP

namespace Ill
{
    namespace System
    {
        namespace Graphics
        {
            class _IllExport GraphicsRenderer : public Ill::System::Object
            {
            public:
                CLASS(GraphicsRenderer,Ill::System::Object);
                // This is an abstract class, no constructor.

                /**
                 * Parse the properties map for startup parameters.
                 */
                VIRTUAL_METHOD(public,bool,GetProperties,(const PropertyMap& properties)) = 0;

                /**
                 * Initialize the graphics renderer. The "GetProperties" method should be called
                 * first to store the startup options, otherwise default options will be used.
                 */
                VIRTUAL_METHOD(public,bool,Initialize,()) = 0;


            protected:
                

            };

            typedef boost::intrusive_ptr<GraphicsRenderer> GraphicsRendererPtr;
        }
    }
}

#endif // ILL_SYSTEM_GRAPHICS_GRAPHICSRENDERER_HPP