/**
 * @file GraphicsTypes.hpp
 * @date September 24, 2009
 *
 * Types that are used by the graphics system.
 */

#ifndef ILL_GRAPHICS_GRAPHICSTYPES_HPP
#define ILL_GRAPHICS_GRAPHICSTYPES_HPP

namespace Ill
{
    namespace Graphics
    {
        /**
        * Scene type classification for initializing a scene manager.
        */
        enum SceneType
        {
            SceneType_Generic = 1,
            SceneType_Exterior_Close = 2,
            SceneType_Exterior_Far = 4,
            SceneType_Exterior_RealFar = 8,
            SceneType_Interior = 16
        };
    }
}

#endif
