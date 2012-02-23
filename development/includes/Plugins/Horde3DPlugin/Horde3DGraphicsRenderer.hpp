#ifndef ILL_PLUGINS_HORDE3DGRAPHICSRENDERER_HPP
#define ILL_PLUGINS_HORDE3DGRAPHICSRENDERER_HPP

#include <Plugins/Horde3DPlugin/Horde3DPlugin.h>
#include <Plugins/Horde3DPlugin/Horde3DGraphicsRenderer.fwd.hpp>

NAMESPACE_H3D_BEGIN

class HORDE3DPLUGIN_DLL Horde3DGraphicsRenderer : public Ill::Graphics::GraphicsRenderer
{
public:
    CLASS(Horde3DGraphicsRenderer, Ill::Graphics::GraphicsRenderer);
    CONSTRUCTOR( HORDE3DPLUGIN_DLL, public, Horde3DGraphicsRenderer, () );

    /**
    * Initialize the graphics renderer. The "GetProperties" method should be called
    * first to store the startup options, otherwise default options will be used.
    */
    VIRTUAL_METHOD( HORDE3DPLUGIN_DLL, public, void, Initialize, () );

    /**
    * Terminiate the graphics renderer.  Cleanup any memory used by the renderer
    * in this method.
    */
    VIRTUAL_METHOD( HORDE3DPLUGIN_DLL, public, void, Terminate, () );

protected:
    
private: 
    bool m_bInitialized;

};

NAMESPACE_H3D_END

#endif // ILL_PLUGINS_HORDE3DGRAPHICSRENDERER_HPP