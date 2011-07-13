/**
 * @file PluginSubsystem.cpp
 * @date September 28, 2009
 *
 */

#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/PluginSubsystem.hpp>

namespace Ill
{
    namespace Core
    {
		PluginSubsystem* PluginSubsystem::ms_Singleton = NULL;

        PluginSubsystem::PluginSubsystem()
        {
			BOOST_ASSERT( ms_Singleton == NULL );
			ms_Singleton = this;
		}

        PluginSubsystem::~PluginSubsystem()
        {
            BOOST_ASSERT( m_PluginList.empty() );
			BOOST_ASSERT( ms_Singleton != NULL );
			ms_Singleton = NULL;
        }

		PluginSubsystem& PluginSubsystem::GetSingleton()
		{
			BOOST_ASSERT( ms_Singleton != NULL );
			return *ms_Singleton;
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
                Plugin* lib = iter->second;
                lib->Unload();
                delete lib;

                ++iter;
            }

            m_PluginList.clear();

            return true;
        }

        Plugin* PluginSubsystem::Load( const std::wstring& pluginName )
        {
            PluginList::iterator iter = m_PluginList.find( pluginName );
            if ( iter != m_PluginList.end() )
            {
                return iter->second;
            }

            Plugin* pLib = new Plugin( pluginName );
            pLib->Load();
            m_PluginList.insert( PluginList::value_type( pluginName, pLib ) );

            return pLib;
        }

        void PluginSubsystem::Unload( Plugin* plugin )
        {
			if ( plugin  != NULL )
			{
                PluginList::iterator iter = m_PluginList.find( plugin->PluginName );
                if ( iter != m_PluginList.end() )
				{
                    m_PluginList.erase( iter );
				}

				plugin->Unload();
				delete plugin;
			}
        }

    }
}