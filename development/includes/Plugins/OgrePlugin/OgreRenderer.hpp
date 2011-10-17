#ifndef ILL_OGREPLUGIN_OGRERENDERER_HPP
#define ILL_OGREPLUGIN_OGRERENDERER_HPP

#include <Ill/Graphics/GraphicsRenderer.hpp>
#include <Ill/Graphics/GraphicsTypes.hpp>

// These functions will be exported to load our OgrePlugin.
extern "C" OGREPLUGIN_DLL Ill::Graphics::GraphicsRenderer* GetGraphicsRenderer();
extern "C" OGREPLUGIN_DLL void DestroyGraphicsRenderer();

// Forward-declaration of Ogre types
//namespace Ogre
//{
//    class Root;
//    class SceneManager;
//    class Camera;
//    class RenderWindow;
//}

namespace Ill
{
    namespace OgrePlugin
    {
        class OGREPLUGIN_DLL OgreRenderer : public Ill::Graphics::GraphicsRenderer
        {
        public:
            CLASS( OgreRenderer, Ill::Graphics::GraphicsRenderer );
            CONSTRUCTOR( OGREPLUGIN_DLL, public, OgreRenderer, () );

            VIRTUAL_METHOD( OGREPLUGIN_DLL, public, bool, GetProperties, (const Ill::Core::PropertyMap& properties) );
            VIRTUAL_METHOD( OGREPLUGIN_DLL, public, bool, Initialize, () );
            VIRTUAL_METHOD( OGREPLUGIN_DLL, public, bool, Terminate, () );

        protected:
            /**
            * Setup the resource paths.  
            * This method is called in the @see(Startup) method.
            */
            VIRTUAL_METHOD( OGREPLUGIN_DLL, protected, void, SetupResourcesPaths, () );

            /**
            * Default implementation is to show a configure dialog box.
            * Override this method to configure the OgreSDK yourself.
            * This method is called directly by the @see(Startup) method.
            * @return true if configuration was successful, false if the user canceled the configuration
            * or the configuration options were not valid.
            */
            VIRTUAL_METHOD( OGREPLUGIN_DLL, protected, bool, ConfigureRenderer, () );

            /**
            * If the configuration worked, we can create a render window
            * from the configuration options.  This method is called from 
            * the @see(Startup) method.
            * @precondition Configurations have been read and are valid.
            */
            VIRTUAL_METHOD( OGREPLUGIN_DLL, protected, void, CreateRenderWindow, () );

            /**
            * Initialise the scene manager.
            */
            VIRTUAL_METHOD( OGREPLUGIN_DLL, protected, void, CreateSceneManager, () );

            /**
            * Create a default camera for our scene.
            */
            VIRTUAL_METHOD( OGREPLUGIN_DLL, protected, void, CreateCamera, () );

            /**
            * Setup the camera's properties like position, orientation, FOV, clip planes..
            */
            VIRTUAL_METHOD( OGREPLUGIN_DLL, protected, void, SetupCamera, () );

            /**
            * Create a viewport
            */
            VIRTUAL_METHOD( OGREPLUGIN_DLL, protected, void, CreateViewport, () );

            /**
            * Create a default resource listener (used for loading screens)
            * Override this method to implement your resource listener.
            */
            VIRTUAL_METHOD( OGREPLUGIN_DLL, protected, void, CreateResourceListener, () ) {}

            /**
            * Optionally override this method to handle resource group loading.
            * At a minimum, it must invoke the ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
            * method, which is all this function actually does.
            */
            VIRTUAL_METHOD( OGREPLUGIN_DLL, protected, void, LoadResources, () );

            /**
            * Create the initial scene.
            * This method must be overridden if you want to see anything in your render window.
            */
            VIRTUAL_METHOD( OGREPLUGIN_DLL, protected, void, CreateScene, () );

        private:
            std::wstring            m_ConfigFilename;
            std::wstring            m_ResourceFilename;
            std::wstring            m_PluginFilename;
            std::wstring            m_LogFilename;

            std::string             m_DefaultSceneInstanceName;
            Graphics::SceneType     m_DefaultSceneType;

            std::string             m_DefaultCameraName;

            
            // Ogre specific types
            //Ogre::Root*             m_pOgreRoot;
            //Ogre::Camera*           m_pOgreCamera;
            //Ogre::SceneManager*     m_pOgreSceneManager;
            //Ogre::RenderWindow*     m_pRenderWindow;
        };
    }
}

#endif // ILL_OGREPLUGIN_OGRERENDERER_HPP