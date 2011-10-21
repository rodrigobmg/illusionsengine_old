/**
 * @file Plugin.cpp
 * @date September 25, 2009
 */

#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/Plugin.hpp>

namespace Ill
{
    namespace Core
    {
        Plugin::Plugin()
        {}

        Plugin::~Plugin()
        {}

        bool Plugin::Initialize()
        {
            return true;
        }

        void Plugin::Terminiate()
        {}
    }
}