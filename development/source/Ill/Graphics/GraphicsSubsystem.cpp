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

        void GrapicsSubsystem::Initialize()
        {
            Super::Initialize();       
        }

        void GrapicsSubsystem::Terminate()
        {
            Super::Terminate();
        }
    }
}