#ifndef ILL_GRAPHICS_GRAPHICSWINDOW_FWD_HPP
#define ILL_GRAPHICS_GRAPHICSWINDOW_FWD_HPP

/**
 * Forward declaration for the GraphicsWindow type.
 */

namespace Ill
{
    namespace Graphics
    {
        class GraphicsWindow;

        typedef boost::shared_ptr<GraphicsWindow> GraphicsWindowPtr;
        typedef boost::weak_ptr<GraphicsWindow> GraphicsWindowWeakPtr;
    }
}

#endif // ILL_GRAPHICS_GRAPHICSWINDOW_FWD_HPP