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
                : m_pOgreRoot ( NULL )
                , m_PluginFilename( "plugins.cfg" )
                , m_ConfigFilename( "ogre.cfg" )
                , m_LogFilename( "Ogre.log" )
            {}

            bool GrapicsSubsystem::Startup( const PropertyMap& startupOptions )
            {
                Super::Startup(startupOptions);

                // Populate our properties from our startup options.
                GetProperties( startupOptions );
           
                // Create our ogre root object
                m_pOgreRoot = new Ogre::Root( m_PluginFilename, m_ConfigFilename, m_LogFilename );

                return true;

            }

            bool GrapicsSubsystem::Shutdown()
            {
                Super::Shutdown();

                delete m_pOgreRoot;
                m_pOgreRoot = NULL;

                return true;
            }

            void GrapicsSubsystem::GetProperties(const PropertyMap& properties)
            {
                Super::GetProperties( properties );

                properties.GetValue( "PluginFilename", m_PluginFilename );
                properties.GetValue( "ConfigFilename", m_ConfigFilename );
                properties.GetValue( "LogFilename", m_LogFilename );
            }

        }
    }
}