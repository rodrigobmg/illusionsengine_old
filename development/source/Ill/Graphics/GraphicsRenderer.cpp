/**
 * @file GraphicsRenderer.cpp
 * @date September 28, 2009
 *
 */

#include <Ill/Graphics/GraphicsPCH.hpp>
#include <Ill/Graphics/GraphicsRenderer.hpp>

namespace Ill
{
    namespace Graphics
    {
        bool GraphicsRenderer::GetProperties( const Ill::Core::PropertyMap& properties )
        {
            return true;
        }

        bool GraphicsRenderer::Initialize()
        {
            return true;
        }

        void GraphicsRenderer::Terminate()
        {

        }
    }
}