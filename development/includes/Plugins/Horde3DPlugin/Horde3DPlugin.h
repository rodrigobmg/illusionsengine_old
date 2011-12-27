/**
 * @file
 */

#ifndef ILL_PLUGINS_HORDE3D_HPP
#define ILL_PLUGINS_HORDE3D_HPP

#include <Ill/Core/Core.hpp>
#include <Ill/Graphics/Graphics.hpp>
#include <Plugins/Horde3DPlugin/Horde3DPluginExports.hpp>
#include <Plugins/Horde3DPlugin/Horde3DPlugin.fwd.hpp>

NAMESPACE_H3D_BEGIN
void HORDE3DPLUGIN_DLL InstantiateTypes();
NAMESPACE_H3D_END

HORDE3DPLUGIN_DLL Ill::Core::Plugin* CreatePlugin(void);
HORDE3DPLUGIN_DLL void DestroyPlugin(void);

NAMESPACE_H3D_BEGIN
class Horde3DPlugin : public Ill::Core::Plugin
{
public:
    CLASS( Horde3DPlugin, Ill::Core::Plugin );
    CONSTRUCTOR( HORDE3DPLUGIN_DLL, public, Horde3DPlugin, () );

    /**
     * Initialize the plug-in including registering types
     * with the class registry, registering subsystems, and 
     * performing any other initialization steps required by the plug-in.
     */
    VIRTUAL_METHOD( HORDE3DPLUGIN_DLL, public, bool, Initialize, () );

    /**
     * Terminate the plug-in including unregistering subsystems that 
     * were initialized in the Initialize() method.
     */
    VIRTUAL_METHOD( HORDE3DPLUGIN_DLL, public, void, Terminiate, () );

};
NAMESPACE_H3D_END

#endif // ILL_GRAPHICS_HPP
