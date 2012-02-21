/**
 * @file Horde3DPluginSubsystem.hpp
 * @date December 28, 2011
 * @author Jeremiah van Oosten
 *
 * The subsystem is registered with the application class
 * so that it is accessible to other parts of the application (including other
 * subsystems).
 * The graphics renderer and the graphics device are accessible
 * from the graphics subsystem.
 */

#ifndef ILL_PLUGINS_HORDE3DPLUGINSUBSYSTEM_HPP
#define ILL_PLUGINS_HORDE3DPLUGINSUBSYSTEM_HPP

#include <Ill/Graphics/GraphicsSubsystem.hpp>
#include <Ill/Graphics/GraphicsRenderer.hpp>

#include <Plugins/Horde3DPlugin/Horde3DPluginExports.hpp>
#include <Plugins/Horde3DPlugin/Horde3DPluginDefines.hpp>
#include <Plugins/Horde3DPlugin/Horde3DGraphicsRenderer.fwd.hpp>

NAMESPACE_H3D_BEGIN

class HORDE3DPLUGIN_DLL Horde3DPluginSubsystem : public Ill::Graphics::GrapicsSubsystem
{
public:
    CLASS( Horde3DPluginSubsystem, Ill::Graphics::GrapicsSubsystem );
    CONSTRUCTOR( HORDE3DPLUGIN_DLL, public, Horde3DPluginSubsystem, () );

    /**
    * Startup the plug-in subsystem. This will cause the graphics renderer to be created.
    *
    * @precondition There is a valid render window to draw to. The default OpenGL context should 
    * be associated with the render window so we can draw to it.
    */
    VIRTUAL_METHOD( HORDE3DPLUGIN_DLL, public, bool, Startup, ( const boost::property_tree::ptree& startupOptions ) );

    /**
    * Shutdown
    */
    VIRTUAL_METHOD( HORDE3DPLUGIN_DLL, public, bool, Shutdown, () );

    /**
    * Retrieve a pointer to the GraphicsRenderer implementation.
    * @precondition The subsystem must have been initialized before
    * you can get a pointer to the GraphicsRenderer implementation.
    */
    VIRTUAL_METHOD( HORDE3DPLUGIN_DLL, public, Ill::Graphics::GraphicsRendererPtr, GetGraphicsRenderer, () );

protected:

private: 
    Horde3DGraphicsRendererPtr m_pGraphicsRenderer;
};

NAMESPACE_H3D_END

#endif // ILL_PLUGINS_HORDE3DPLUGINSUBSYSTEM_HPP