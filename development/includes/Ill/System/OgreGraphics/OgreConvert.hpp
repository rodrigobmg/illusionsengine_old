#ifndef ILL_SYSTEM_OGREGRAPHICS_OGRECONVERT_HPP
#define ILL_SYSTEM_OGREGRAPHICS_OGRECONVERT_HPP

namespace Ill
{
    namespace System
    {
        namespace OgreGraphics
        {
            class OgreConvert
            {
            public:
                /**
                 * Convert Ill::System::Graphics::SceneType to Ogre::SceneType
                 */
                static Ogre::SceneType Convert( Graphics::SceneType sceneType );
            };
        }
    }
}


#endif // ILL_SYSTEM_OGREGRAPHICS_OGRECONVERT_HPP