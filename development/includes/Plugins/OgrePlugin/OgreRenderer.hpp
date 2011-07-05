#ifndef ILL_OGREGRAPHICS_OGRERENDERER
#define ILL_OGREGRAPHICS_OGRERENDERER

// This function will be exported to load our Ogre graphics renderer.
extern Ill::Graphics::GraphicsRenderer* gs_GraphicsRenderer;

// Forward-declaration of Ogre types
namespace Ogre
{
    class Root;
    class SceneManager;
    class Camera;
    class RenderWindow;
}

namespace Ill
{
    namespace OgreGraphics
    {
        class _IllExport OgreRenderer : public Ill::Graphics::GraphicsRenderer
        {
        public:
            CLASS( OgreRenderer, Ill::Graphics::GraphicsRenderer );
            CONSTRUCTOR(public,OgreRenderer,());

            VIRTUAL_METHOD(public,bool,GetProperties,(const PropertyMap& properties));
            VIRTUAL_METHOD(public,bool,Initialize,());
            VIRTUAL_METHOD(public,bool,Terminate,());

        protected:
            /**
            * Setup the resource paths.  
            * This method is called in the @see(Startup) method.
            */
            VIRTUAL_METHOD(protected,void,SetupResourcesPaths,() );

            /**
            * Default implementation is to show a configure dialog box.
            * Override this method to configure the OgreSDK yourself.
            * This method is called directly by the @see(Startup) method.
            * @return true if configuration was successful, false if the user canceled the configuration
            * or the configuration options were not valid.
            */
            VIRTUAL_METHOD(protected,bool,ConfigureRenderer,() );

            /**
            * If the configuration worked, we can create a render window
            * from the configuration options.  This method is called from 
            * the @see(Startup) method.
            * @precondition Configurations have been read and are valid.
            */
            VIRTUAL_METHOD(protected,void,CreateRenderWindow,() );

            /**
            * Initialise the scene manager.
            */
            VIRTUAL_METHOD(protected,void,CreateSceneManager,() );

            /**
            * Create a default camera for our scene.
            */
            VIRTUAL_METHOD(protected,void,CreateCamera,() );

            /**
            * Setup the camera's properties like position, orientation, FOV, clip planes..
            */
            VIRTUAL_METHOD(protected,void,SetupCamera,() );

            /**
            * Create a viewport
            */
            VIRTUAL_METHOD(protected,void,CreateViewport,() );

            /**
            * Create a default resource listener (used for loading screens)
            * Override this method to implement your resource listener.
            */
            VIRTUAL_METHOD(protected,void,CreateResourceListener,() ) {}

            /**
            * Optionally override this method to handle resource group loading.
            * At a minimum, it must invoke the ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
            * method, which is all this function actually does.
            */
            VIRTUAL_METHOD(protected,void,LoadResources,() );

            /**
            * Create the initial scene.
            * This method must be overridden if you want to see anything in your render window.
            */
            VIRTUAL_METHOD(protected,void,CreateScene,() );

        private:
            String                  m_ConfigFilename;
            String                  m_ResourceFilename;
            String                  m_PluginFilename;
            String                  m_LogFilename;

            String                  m_DefaultSceneInstanceName;
            Graphics::SceneType     m_DefaultSceneType;

            String                  m_DefaultCameraName;

            
            // Ogre specific types
            Ogre::Root*             m_pOgreRoot;
            Ogre::Camera*           m_pOgreCamera;
            Ogre::SceneManager*     m_pOgreSceneManager;
            Ogre::RenderWindow*     m_pRenderWindow;
        };
    }
}

#endif // ILL_SYSTEM_OGREGRAPHICS_OGRERENDERER