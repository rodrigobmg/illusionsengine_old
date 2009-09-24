/**
 * @file: GraphicsSubsystem.cpp
 * @date: September 18, 2009
 *
 */

#include <Ill/System/Graphics/PrecompiledHeader.hpp>
#include <Ill/System/Graphics/GraphicsSubsystem.hpp>

// Private includes
#include "GraphicsUtils.hpp"

namespace Ill
{
    namespace System
    {
        namespace Graphics
        {
            GrapicsSubsystem::GrapicsSubsystem()
                : m_ConfigFilename( "ogre.cfg" )
                , m_ResourceFilename( "resource.cfg")
                , m_PluginFilename( "plugins.cfg" )
                , m_LogFilename( "Ogre.log" )
                , m_DefaultSceneInstanceName( "DefaultSceneManager" )
                , m_DefaultSceneType( SceneType_Generic )
                , m_pOgreRoot ( NULL )
                , m_pOgreCamera( NULL )
                , m_pOgreSceneManager( NULL )
                , m_pRenderWindow( NULL )
            {}

            bool GrapicsSubsystem::Startup( const PropertyMap& startupOptions )
            {
                Super::Startup(startupOptions);

                // Populate our properties from our startup options.
                GetProperties( startupOptions );
           
                // Create our ogre root object
                m_pOgreRoot = OGRE_NEW Ogre::Root( m_PluginFilename, m_ConfigFilename, m_LogFilename );

                // Setup the resource paths
                SetupResourcesPaths();
            
                // Load the configuration options
                if ( !ConfigureRenderer() )
                {
                    // startup for this subsystem failed.
                    // Either throw an exception, or return false.
                    // The rest of the game should not start but instead show
                    // some kind of dialog box that describes the problem.
                    return false;
                }
                
                CreateRenderWindow();
                CreateSceneManager();
                CreateCamera();
                SetupCamera();
                CreateViewport();

                // Set default mipmap level (NB some APIs ignore this)
                Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

                CreateResourceListener();
                LoadResources();
                CreateScene();

                return true;

            }

            bool GrapicsSubsystem::Shutdown()
            {
                Super::Shutdown();

                OGRE_DELETE m_pOgreRoot;
                m_pOgreRoot = NULL;

                return true;
            }

            void GrapicsSubsystem::SetupResourcesPaths()
            {
                // Load the resource paths from a configuration file.
                Ogre::ConfigFile configFile;
                configFile.load( m_ResourceFilename );

                Ogre::ConfigFile::SectionIterator secIter = configFile.getSectionIterator();
                Ogre::String archiveName, sectionName, typeName;
                
                while ( secIter.hasMoreElements() )
                {
                    sectionName = secIter.peekNextKey();
                    Ogre::ConfigFile::SettingsMultiMap* settings = secIter.getNext();
                    Ogre::ConfigFile::SettingsMultiMap::iterator iter = settings->begin();
                    while( iter != settings->end() )
                    {
                        typeName = iter->first;
                        archiveName = iter->second;

                        // Now add the resource to the resource manager.
                        Ogre::ResourceGroupManager::getSingleton().addResourceLocation( archiveName, typeName, sectionName );

                        ++iter;
                    }
                }
            }

            bool GrapicsSubsystem::ConfigureRenderer() 
            {
                BOOST_ASSERT( m_pOgreRoot != NULL );

                // This will present the user with a configuration dialog box.
                // If you are sure the configuration file contains valid settings, 
                // you could just call m_pOgreRoot->restoreConfig to load the saved 
                // configuration file.
                return m_pOgreRoot->showConfigDialog();
            }

            void GrapicsSubsystem::CreateRenderWindow() 
            {
                BOOST_ASSERT( m_pOgreRoot != NULL );

                // Create a rendering window based on the configuration options.
                m_pRenderWindow = m_pOgreRoot->initialise(true);
            }

            void GrapicsSubsystem::CreateSceneManager()
            {
                BOOST_ASSERT( m_pOgreRoot != NULL );

                // Create the scene manager based on assigned properties.
                m_pOgreSceneManager = m_pOgreRoot->createSceneManager( Ogre::SceneTypeMask( OgreConvert::SceneType(m_DefaultSceneType) ), m_DefaultSceneInstanceName );
            }

            void GrapicsSubsystem::CreateCamera()
            {
                BOOST_ASSERT( m_pOgreSceneManager != NULL );

                // Create the default camera that will be used to render the scene
                m_pOgreCamera = m_pOgreSceneManager->createCamera( m_DefaultCameraName );
            }

            void GrapicsSubsystem::SetupCamera()
            {
                BOOST_ASSERT( m_pOgreCamera != NULL );

                // Setup the camera to view our scene.
                // Position it at 500 in +Z direction
                m_pOgreCamera->setPosition(Ogre::Vector3(0,0,500));
                // Look back along -Z
                m_pOgreCamera->lookAt(Ogre::Vector3(0,0,-300));
                m_pOgreCamera->setNearClipDistance(5);
            }

            void GrapicsSubsystem::CreateViewport()
            {
                BOOST_ASSERT( m_pRenderWindow != NULL && m_pOgreCamera != NULL );

                Ogre::Viewport* vp = m_pRenderWindow->addViewport( m_pOgreCamera );
                vp->setBackgroundColour( Ogre::ColourValue(0.0f, 0.0f, 0.0f, 0.0f) );

                // Modify the camera's aspect ratio to match the viewport's actual dimensions
                m_pOgreCamera->setAspectRatio( Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()) );
            }

            void GrapicsSubsystem::LoadResources()
            {
                Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
            }

            void GrapicsSubsystem::CreateScene()
            {
                // TODO: Create a default scene with a plane, a box, and some lights.
                // Set some default scene settings.
            }

            void GrapicsSubsystem::GetProperties(const PropertyMap& properties)
            {
                Super::GetProperties( properties );

                properties.GetValue( "PluginFilename", m_PluginFilename );
                properties.GetValue( "ConfigFilename", m_ConfigFilename );
                properties.GetValue( "ResourceFilename", m_ResourceFilename );
                properties.GetValue( "LogFilename", m_LogFilename );

                properties.GetValue( "DefaultSceneInstanceName", m_DefaultSceneInstanceName );
                properties.GetValue( "DefaultSceneType", m_DefaultSceneType );

                properties.GetValue( "DefaultCameraName", m_DefaultCameraName );
            }

        }
    }
}