/**
 * @file: GraphicsSubsystem.cpp
 * @date: September 18, 2009
 *
 */

#include <Ill/Graphics/PrecompiledHeader.hpp>
#include <Ill/Graphics/GraphicsSubsystem.hpp>
#include <Ill/Graphics/GraphicsRenderer.hpp>

// Define a function that will be used to get a pointer to our graphics renderer implementation.
typedef Ill::Graphics::GraphicsRenderer* (*GET_RENDERER_FUNC)(void);
typedef void (*DESTROY_RENDERER_FUNC)(void);

namespace Ill
{
    namespace Graphics
    {
        GrapicsSubsystem::GrapicsSubsystem()
            : m_GraphicsLibName( TEXT("") )
            , m_pGraphicsRenderer( NULL )
        {}

        bool GrapicsSubsystem::Startup( const Ill::Core::PropertyMap& startupOptions )
        {
            Super::Startup(startupOptions);

            // Populate our properties from our startup options.
            GetProperties( startupOptions );
       
			Ill::Core::PluginSubsystem& pluginMgr = Ill::Core::PluginSubsystem::GetSingleton();
			Ill::Core::Plugin* plugin = NULL;
			try
			{
				plugin = pluginMgr.Load( m_GraphicsLibName );
                GET_RENDERER_FUNC pFunc = (GET_RENDERER_FUNC)plugin->GetSymbol( "GetGraphicsRenderer" );

                if ( pFunc != NULL )
                {
                    m_pGraphicsRenderer = pFunc();

                    BOOST_ASSERT( m_pGraphicsRenderer != NULL );

                    m_pGraphicsRenderer->GetProperties( startupOptions );
                    m_pGraphicsRenderer->Initialize();
                }
			}
			catch ( std::exception& exp )
			{
				std::cerr << "Could not load graphics lib: " << ConvertString( m_GraphicsLibName ) << exp.what() << std::endl;
				return false;
			}

            return true;
        }

        bool GrapicsSubsystem::Shutdown()
        {
            Super::Shutdown();

            Ill::Core::PluginSubsystem& pluginMgr = Ill::Core::PluginSubsystem::GetSingleton();
            Ill::Core::Plugin* plugin = NULL;

            try
            {
                plugin = pluginMgr.Load( m_GraphicsLibName );
                DESTROY_RENDERER_FUNC pFunc = (DESTROY_RENDERER_FUNC)plugin->GetSymbol( "DestroyGraphicsRenderer" );
                if ( pFunc != NULL )
                {
                    pFunc();
                }
            }
            catch ( std::exception& exp )
            {
                std::cerr << "Could not destroy graphics lib: " << ConvertString( m_GraphicsLibName ) << exp.what() << std::endl;
            }


            return true;
        }

        GraphicsRenderer* GrapicsSubsystem::GetGraphicsRenderer()
        {
            return m_pGraphicsRenderer;
        }

        void GrapicsSubsystem::GetProperties(const Ill::Core::PropertyMap& properties)
        {
            Super::GetProperties( properties );

            properties.GetValue( "GraphicsLibName", m_GraphicsLibName );
        }
    }
}