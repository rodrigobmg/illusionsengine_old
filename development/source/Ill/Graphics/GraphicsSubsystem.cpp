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

        bool GrapicsSubsystem::Startup( const boost::property_tree::ptree& startupOptions )
        {
            Super::Startup(startupOptions);       
            return true;
        }

        bool GrapicsSubsystem::Shutdown()
        {
            Super::Shutdown();

            return true;
        }
    }
}