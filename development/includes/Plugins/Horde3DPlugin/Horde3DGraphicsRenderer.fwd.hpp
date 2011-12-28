#ifndef ILL_PLUGINS_HORDE3DGRAPHICSRENDERER_FWD_HPP
#define ILL_PLUGINS_HORDE3DGRAPHICSRENDERER_FWD_HPP

/**
* @file Horde3DGraphicsRenderer.fwd.hpp
* @date December 28, 2011
* @author Jeremiah van Oosten
*
* Forward declarations for the Horde3DGraphicsRendere types.
*/

namespace Ill 
{ 
    namespace Plugins 
    { 
        namespace Horde3D 
        {
            class Horde3DGraphicsRenderer;
            typedef boost::shared_ptr<Horde3DGraphicsRenderer> Horde3DGraphicsRendererPtr;
            typedef boost::weak_ptr<Horde3DGraphicsRenderer> Horde3DGraphicsRendererWeakPtr;
        }
    }
}

#endif // ILL_PLUGINS_HORDE3DGRAPHICSRENDERER_FWD_HPP