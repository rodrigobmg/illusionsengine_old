/**
 * @file DynamicLibSubsystem.cpp
 * @date September 28, 2009
 *
 */

#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/DynamicLibSubsystem.hpp>

namespace Ill
{
    namespace Core
    {
		DynamicLibSubsystem* DynamicLibSubsystem::ms_Singleton = NULL;

        DynamicLibSubsystem::DynamicLibSubsystem()
        {
			BOOST_ASSERT( ms_Singleton == NULL );
			ms_Singleton = this;
		}

        DynamicLibSubsystem::~DynamicLibSubsystem()
        {
            BOOST_ASSERT( m_LibList.empty() );
			BOOST_ASSERT( ms_Singleton != NULL );
			ms_Singleton = NULL;
        }

		DynamicLibSubsystem& DynamicLibSubsystem::GetSingleton()
		{
			BOOST_ASSERT( ms_Singleton != NULL );
			return *ms_Singleton;
		}

        bool DynamicLibSubsystem::Startup( const PropertyMap& startupOptions )
        {
            return Super::Startup( startupOptions );
        }

        bool DynamicLibSubsystem::Shutdown()
        {
            Super::Shutdown();

            // Unload any libs that may still be loaded.
            LibList::iterator iter = m_LibList.begin();
            while( iter != m_LibList.end() )
            {
                DynamicLib* lib = iter->second;
                lib->Unload();
                delete lib;

                ++iter;
            }

            m_LibList.clear();

            return true;
        }

        DynamicLib* DynamicLibSubsystem::Load( const String& libName )
        {
            LibList::iterator iter = m_LibList.find( libName );
            if ( iter != m_LibList.end() )
            {
                return iter->second;
            }

            DynamicLib* pLib = new DynamicLib( libName );
            pLib->Load();
            m_LibList.insert( LibList::value_type( libName, pLib ) );

            return pLib;
        }

        void DynamicLibSubsystem::Unload( DynamicLib* lib )
        {
			if ( lib != NULL )
			{
				LibList::iterator iter = m_LibList.find( lib->LibName );
				if ( iter != m_LibList.end() )
				{
					m_LibList.erase( iter );
				}

				lib->Unload();
				delete lib;
			}
        }

    }
}