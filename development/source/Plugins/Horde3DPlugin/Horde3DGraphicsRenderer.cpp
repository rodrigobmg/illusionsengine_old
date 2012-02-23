#include <Plugins/Horde3DPlugin/Horde3DPluginPCH.hpp>
#include <Plugins/Horde3DPlugin/Horde3DGraphicsRenderer.hpp>

NAMESPACE_H3D_BEGIN

Horde3DGraphicsRenderer::Horde3DGraphicsRenderer()
: m_bInitialized( false )
{

}

void Horde3DGraphicsRenderer::Initialize()
{
    if ( !m_bInitialized )
    {
        m_bInitialized = h3dInit();
    }
}

void Horde3DGraphicsRenderer::Terminate()
{
    if ( m_bInitialized )
    {
        h3dRelease();
        m_bInitialized = false;
    }
}


NAMESPACE_H3D_END