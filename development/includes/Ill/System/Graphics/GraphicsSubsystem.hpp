/**
 * @file: GraphicsSubsystem.hpp
 * @date: September 18, 2009
 * 
 * The GraphicsSubsystem is used to create and manage the graphics renderer.
 *
 */

#ifndef ILL_SYSTEM_GRAPHICS_GRAPHICSSUBSYSTEM_HPP
#define ILL_SYSTEM_GRAPHICS_GRAPHICSSUBSYSTEM_HPP

#include <Ill/System/Subsystem.hpp>
#include <Ill/System/Graphics/GraphicsTypes.h>

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
    namespace System
    {
        namespace Graphics
        {
            class GrapicsSubsystem : public Ill::System::Subsystem
            {
            public:

                CLASS( GrapicsSubsystem, Ill::System::Subsystem );
                CONSTRUCTOR(public,GrapicsSubsystem,());

                /**
                * Startup the graphics subsystem.
                */
                VIRTUAL_METHOD(public,bool,Startup,( const PropertyMap& startupOptions ));

                /**
                * Shutdown
                */
                VIRTUAL_METHOD(public,bool,Shutdown,());

            protected:

                /**
                * Populate my defined properties from the passed-in property map
                */
                VIRTUAL_METHOD(public,void,GetProperties,(const PropertyMap& properties) );

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
                 * Optionally override this method to handle resoure group loading.
                 * At a minimum, it must invoke the ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
                 * method, which is all this function actually does.
                 */
                VIRTUAL_METHOD(protected,void,LoadResources,() );

                /**
                 * Create the initial scene.
                 * This method must be overriden if you want to see anything in your render window.
                 */
                VIRTUAL_METHOD(protected,void,CreateScene,() );

            private:
                // Getters and setters for property types
                const std::string& get_PluginFilename() const
                {
                    return m_PluginFilename;
                }
                void set_PluginFilename( const std::string& pluginFilename )
                {
                    m_PluginFilename = pluginFilename;
                }

                const std::string& get_ConfigFilename() const
                {
                    return m_ConfigFilename;
                }
                void set_ConfigFilename( const std::string& configFilename )
                {
                    m_ConfigFilename = configFilename;
                }

                const std::string& get_ResourceFilename() const
                {
                    return m_ResourceFilename;
                }
                void set_ResourceFilename( const std::string& resourceFilename )
                {
                    m_ResourceFilename = resourceFilename;
                }

                const std::string& get_LogFilename() const
                {
                    return m_LogFilename;
                }
                void set_LogFilename( const std::string& logFilename )
                {
                    m_LogFilename = logFilename;
                }

                SceneType get_DefaultSceneType() const
                {
                    return m_DefaultSceneType;
                }
                void set_DefaultSceneType( SceneType defaultSceneType )
                {
                    m_DefaultSceneType = defaultSceneType;
                }

                const std::string& get_DefaultSceneInstanceName() const
                {
                    return m_DefaultSceneInstanceName;
                }
                void set_DefaultSceneInstanceName( const std::string& defaultSceneInstanceName )
                {
                    m_DefaultSceneInstanceName = defaultSceneInstanceName;
                }

                const std::string& get_DefaultCameraName() const
                {
                    return m_DefaultCameraName;
                }
                void set_DefaultCameraName( const std::string& cameraName )
                {
                    m_DefaultCameraName = cameraName;
                }

                // Data members
                std::string     m_ConfigFilename;
                std::string     m_ResourceFilename;
                std::string     m_PluginFilename;
                std::string     m_LogFilename;

                std::string     m_DefaultSceneInstanceName;
                SceneType       m_DefaultSceneType;

                std::string     m_DefaultCameraName;

                Ogre::Root*         m_pOgreRoot;
                Ogre::Camera*       m_pOgreCamera;
                Ogre::SceneManager* m_pOgreSceneManager;
                Ogre::RenderWindow* m_pRenderWindow;

            public:
                // Define properties at the bottom of the class to avoid VAssistX getting confused and hiding 
                // my member variables from using code-completion.

                PROPERTY(const std::string&, PluginFilename );
                PROPERTY(const std::string&, ConfigFilename );
                PROPERTY(const std::string&, ResourceFilename );
                PROPERTY(const std::string&, LogFilename );

                PROPERTY( SceneType, DefaultSceneType );
                PROPERTY( const std::string&, DefaultSceneInstanceName );

                PROPERTY( const std::string&, DefaultCameraName );
            };

            typedef boost::intrusive_ptr<GrapicsSubsystem> GraphicsSubsystemPtr;
        }
    }
}

#endif // ILL_SYSTEM_GRAPHICS_GRAPHICSSUBSYSTEM_HPP