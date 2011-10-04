/**
 * @file PluginSubsystem.cpp
 * @date September 28, 2009
 *
 */

#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/Plugin.hpp>
#include <Ill/Core/PluginSubsystem.hpp>

namespace Ill
{
    namespace Core
    {
        PluginSubsystem::PluginSubsystem()
        {
		}

        PluginSubsystem::~PluginSubsystem()
        {
        }

        bool PluginSubsystem::Startup( const PropertyMap& startupOptions )
        {
            return Super::Startup( startupOptions );
        }

        bool PluginSubsystem::Shutdown()
        {
            Super::Shutdown();

            // Unload any libs that may still be loaded.
            PluginList::iterator iter = m_PluginList.begin();
            while( iter != m_PluginList.end() )
            {
                PluginPtr lib = iter->second;
                lib->Unload();

                ++iter;
            }

            m_PluginList.clear();

            return true;
        }

        PluginPtr PluginSubsystem::Load( const std::wstring& pluginName )
        {
            PluginList::iterator iter = m_PluginList.find( pluginName );
            if ( iter != m_PluginList.end() )
            {
                return iter->second;
            }

            PluginPtr pLib = boost::make_shared<Plugin>( pluginName );
            pLib->Load();
            m_PluginList.insert( PluginList::value_type( pluginName, pLib ) );

            return pLib;
        }

        void PluginSubsystem::Unload( PluginPtr plugin )
        {
			if ( plugin  != NULL )
			{
                PluginList::iterator iter = m_PluginList.find( plugin->PluginName );
                if ( iter != m_PluginList.end() )
				{
                    m_PluginList.erase( iter );
				}

				plugin->Unload();
			}
        }

    }
}