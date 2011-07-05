#ifndef ILL_OGREGRAPHICS_OGRECONVERT_HPP
#define ILL_OGREGRAPHICS_OGRECONVERT_HPP

namespace Ill
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


#endif // ILL_OGREGRAPHICS_OGRECONVERT_HPP