#include <Plugins/Horde3DPlugin/Horde3DPluginPCH.hpp>
#include <Plugins/Horde3DPlugin/Horde3DGraphicsRenderer.hpp>
#include <Plugins/Horde3DPlugin/Horde3DPluginSubsystem.hpp>

NAMESPACE_H3D_BEGIN

Horde3DPluginSubsystem::Horde3DPluginSubsystem()
{

}

bool Horde3DPluginSubsystem::Startup( const Ill::Core::PropertyMap& startupOptions )
{
    bool bSuccess = false;
    bSuccess = Super::Startup( startupOptions );

    if ( bSuccess )
    {
        // Create the graphics renderer
        m_pGraphicsRenderer = boost::make_shared<Horde3DGraphicsRenderer>();
        // Initialize the renderer. This will initialize the Hord3D render system.
        // The render window should already be initialized at this point.
        m_pGraphicsRenderer->Initialize();
    }

    return bSuccess;
}

bool Horde3DPluginSubsystem::Shutdown()
{
    return Super::Shutdown();
}

void Horde3DPluginSubsystem::SetProperties( const Ill::Core::PropertyMap& properties )
{
    Super::SetProperties( properties );
}

Ill::Graphics::GraphicsRendererPtr Horde3DPluginSubsystem::GetGraphicsRenderer()
{
    BOOST_ASSERT_MSG( m_pGraphicsRenderer, "The GraphicsRenderer is not yet initialized." );
    return boost::static_pointer_cast< Ill::Graphics::GraphicsRenderer >( m_pGraphicsRenderer );
}

NAMESPACE_H3D_END