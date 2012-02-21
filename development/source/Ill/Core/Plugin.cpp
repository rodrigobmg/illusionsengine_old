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
        {
        }

        Plugin::~Plugin()
        {
        }

        bool Plugin::Initialize()
        {
            return true;
        }

        void Plugin::Terminiate()
        {}

        const std::wstring& Plugin::get_PluginName() const
        {
            return m_PluginName;
        }

        void Plugin::set_PluginName( const std::wstring& pluginName )
        {
            m_PluginName = pluginName;
        }

        const std::wstring& Plugin::get_FileName() const
        {
            return m_FileName;
        }

        void Plugin::set_FileName( const std::wstring& fileName )
        {
            m_FileName = fileName;
        }

    }
}