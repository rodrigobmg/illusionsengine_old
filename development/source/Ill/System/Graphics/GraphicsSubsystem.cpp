/**
 * @file: GraphicsSubsystem.cpp
 * @date: September 18, 2009
 *
 */

#include <Ill/System/Graphics/PrecompiledHeader.hpp>
#include <Ill/System/Graphics/GraphicsSubsystem.hpp>

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
                // you could just call m_pOgreRoot->restoreConfig to load the configuration file.
                if ( m_pOgreRoot->showConfigDialog() )
                {
                    // Create a rendering window based on the configuration options.
                    m_pRenderWindow = m_pOgreRoot->initialise(true);
                    return true;
                }
                else
                {
                    return false;
                }
            }


            void GrapicsSubsystem::GetProperties(const PropertyMap& properties)
            {
                Super::GetProperties( properties );

                properties.GetValue( "PluginFilename", m_PluginFilename );
                properties.GetValue( "ConfigFilename", m_ConfigFilename );
                properties.GetValue( "ResourceFilename", m_ResourceFilename );
                properties.GetValue( "LogFilename", m_LogFilename );
            }

        }
    }
}