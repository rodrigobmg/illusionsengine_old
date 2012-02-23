#include <Plugins/Horde3DPlugin/Horde3DPluginPCH.hpp>
#include <Plugins/Horde3DPlugin/Horde3DGraphicsRenderer.hpp>
#include <Plugins/Horde3DPlugin/Horde3DPluginSubsystem.hpp>

NAMESPACE_H3D_BEGIN

Horde3DPluginSubsystem::Horde3DPluginSubsystem()
{

}

void Horde3DPluginSubsystem::Initialize()
{
    Super::Initialize();

    // Create the graphics renderer
    m_pGraphicsRenderer = boost::make_shared<Horde3DGraphicsRenderer>();
    // Initialize the renderer. This will initialize the Hord3D render system.
    // The render window should already be initialized at this point.
    m_pGraphicsRenderer->Initialize();
}

void Horde3DPluginSubsystem::Terminate()
{
    m_pGraphicsRenderer->Terminate();
    m_pGraphicsRenderer.reset();

    Super::Terminate();
}

Ill::Graphics::GraphicsRendererPtr Horde3DPluginSubsystem::GetGraphicsRenderer()
{
    BOOST_ASSERT_MSG( m_pGraphicsRenderer, "The GraphicsRenderer is not yet initialized." );
    return boost::static_pointer_cast< Ill::Graphics::GraphicsRenderer >( m_pGraphicsRenderer );
}

NAMESPACE_H3D_END