/**
 * @file: GraphicsSubsystem.cpp
 * @date: September 18, 2009
 *
 */
#include <Ill/Graphics/GraphicsPCH.hpp>

#include <Ill/Core/CoreUtils.hpp>
#include <Ill/Core/Application.hpp>
#include <Ill/Core/DynamicLibSubsystem.hpp>
#include <Ill/Core/DynamicLib.hpp>

#include <Ill/Graphics/GraphicsSubsystem.hpp>
#include <Ill/Graphics/GraphicsRenderer.hpp>

namespace Ill
{
    namespace Graphics
    {
        GrapicsSubsystem::GrapicsSubsystem()
            : m_pGraphicsRenderer( NULL )
        {}

        bool GrapicsSubsystem::Startup( const Ill::Core::PropertyMap& startupOptions )
        {
            Super::Startup(startupOptions);
            SetProperties( startupOptions );
       
            return true;
        }

        bool GrapicsSubsystem::Shutdown()
        {
            Super::Shutdown();

            return true;
        }

        GraphicsRenderer* GrapicsSubsystem::GetGraphicsRenderer()
        {
            return m_pGraphicsRenderer;
        }

        void GrapicsSubsystem::SetProperties(const Ill::Core::PropertyMap& properties)
        {
            Super::SetProperties( properties );
        }
    }
}