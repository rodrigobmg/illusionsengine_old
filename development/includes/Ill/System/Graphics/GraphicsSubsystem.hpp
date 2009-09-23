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


                PROPERTY(const std::string&, PluginFilename );
                PROPERTY(const std::string&, ConfigFilename );
                PROPERTY(const std::string&, ResourceFilename );
                PROPERTY(const std::string&, LogFilename );

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

                // Data memebers
                std::string     m_ConfigFilename;
                std::string     m_ResourceFilename;
                std::string     m_PluginFilename;
                std::string     m_LogFilename;

                Ogre::Root*         m_pOgreRoot;
                Ogre::Camera*       m_pOgreCamera;
                Ogre::SceneManager* m_pOgreSceneManager;
                Ogre::RenderWindow* m_pRenderWindow;
            };

            typedef boost::intrusive_ptr<GrapicsSubsystem> GraphicsSubsystemPtr;
        }
    }
}

#endif // ILL_SYSTEM_GRAPHICS_GRAPHICSSUBSYSTEM_HPP