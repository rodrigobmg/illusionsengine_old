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
                * Startup
                */
                VIRTUAL_METHOD(public,bool,Startup,( const PropertyMap& startupOptions ));

                /**
                * Shutdown
                */
                VIRTUAL_METHOD(public,bool,Shutdown,());

                PROPERTY(const std::string&, PluginFilename );
                PROPERTY(const std::string&, ConfigFilename );
                PROPERTY(const std::string&, LogFilename );

            protected:

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
                std::string     m_PluginFilename;
                std::string     m_LogFilename;

                Ogre::Root*     m_pOgreRoot;
            };
        }
    }
}

#endif // ILL_SYSTEM_GRAPHICS_GRAPHICSSUBSYSTEM_HPP