/**
 * @file: GraphicsUtils.h
 * @date: September 24, 2009
 * 
 * Helper functions and utility classes used in the
 * Graphics library.
 * 
 * This is a private header specific to the Graphics library.
 */

#ifndef ILL_SYSTEM_GRAPHICS_GRAPHICSUTILS_HPP
#define ILL_SYSTEM_GRAPHICS_GRAPHICSUTILS_HPP

namespace Ill
{
    namespace System
    {
        namespace Graphics
        {
            // A class that defines a set of methods that convert types to types known by Ogre.
            class OgreConvert
            {
            public:
                // Convert from a generic scene type to an ogre scene type.
                static Ogre::SceneType SceneType( Ill::System::Graphics::SceneType sceneType )
                {
                    switch( sceneType )
                    {
                    case SceneType_Generic: return Ogre::ST_GENERIC; break;
                    case SceneType_Exterior_Close: return Ogre::ST_EXTERIOR_CLOSE; break;
                    case SceneType_Exterior_Far: return Ogre::ST_EXTERIOR_FAR; break;
                    case SceneType_Exterior_RealFar: return Ogre::ST_EXTERIOR_REAL_FAR; break;
                    case SceneType_Interior: return Ogre::ST_INTERIOR; break;
                    };

                    // This shouldn't happen if we have defined all the types in the switch statement.
                    return Ogre::ST_GENERIC;
                }
            };
        }
    }
}

#endif // ILL_SYSTEM_GRAPHICS_GRAPHICSUTILS_HPP