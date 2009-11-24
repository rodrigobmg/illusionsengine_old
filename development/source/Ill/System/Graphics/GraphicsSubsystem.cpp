/**
 * @file: GraphicsSubsystem.cpp
 * @date: September 18, 2009
 *
 */

#include <Ill/System/Graphics/PrecompiledHeader.hpp>
#include <Ill/System/Graphics/GraphicsSubsystem.hpp>
#include <Ill/System/Graphics/GraphicsRenderer.hpp>

// Private includes
#include "GraphicsUtils.hpp"

// Define a function that will be used to get a pointer to our graphics renderer implementation.
typedef Ill::System::Graphics::GraphicsRenderer* (*GET_RENDERER_FUNC)(void);
typedef void (*DESTROY_RENDERER_FUNC)(void);

namespace Ill
{
    namespace System
    {
        namespace Graphics
        {
            GrapicsSubsystem::GrapicsSubsystem()
                : m_GraphicsLibName( TEXT("") )
                , m_pGraphicsRenderer( NULL )
            {}

            bool GrapicsSubsystem::Startup( const PropertyMap& startupOptions )
            {
                Super::Startup(startupOptions);

                // Populate our properties from our startup options.
                GetProperties( startupOptions );
           
				Ill::System::DynamicLibSubsystem& dynLibMgr = Ill::System::DynamicLibSubsystem::GetSingleton();
				Ill::System::DynamicLib* dynLib = NULL;
				try
				{
					dynLib = dynLibMgr.Load( m_GraphicsLibName );
                    GET_RENDERER_FUNC pFunc = (GET_RENDERER_FUNC)dynLib->GetSymbol( TEXT("GetGraphicsRenderer") );

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

                Ill::System::DynamicLibSubsystem& dynLibMgr = Ill::System::DynamicLibSubsystem::GetSingleton();
                Ill::System::DynamicLib* dynLib = NULL;

                try
                {
                    dynLib = dynLibMgr.Load( m_GraphicsLibName );
                    DESTROY_RENDERER_FUNC pFunc = (DESTROY_RENDERER_FUNC)dynLib->GetSymbol( TEXT("DestroyGraphicsRenderer") );
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

            void GrapicsSubsystem::GetProperties(const PropertyMap& properties)
            {
                Super::GetProperties( properties );

                properties.GetValue( "GraphicsLibName", m_GraphicsLibName );
            }

        }
    }
}