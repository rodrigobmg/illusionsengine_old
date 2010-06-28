#include <Ill/System/OgreGraphics/PrecompiledHeader.hpp>
#include <Ill/System/OgreGraphics/OgreConvert.hpp>

namespace Ill
{
    namespace System
    {
        namespace OgreGraphics
        {
            Ogre::SceneType OgreConvert::Convert( Graphics::SceneType sceneType )
            {
                switch ( sceneType )
                {
                case Graphics::SceneType_Generic: return Ogre::ST_GENERIC; break;
                case Graphics::SceneType_Exterior_Close: return Ogre::ST_EXTERIOR_CLOSE; break;
                case Graphics::SceneType_Exterior_Far: return Ogre::ST_EXTERIOR_FAR; break;
                case Graphics::SceneType_Exterior_RealFar: return Ogre::ST_EXTERIOR_REAL_FAR; break;
                }

                return Ogre::ST_GENERIC;
            }
        }
    }
}