/**
 * @file DynamicLibSubsystem.cpp
 * @date September 28, 2009
 *
 */

#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/DynamicLib.hpp>
#include <Ill/Core/DynamicLibSubsystem.hpp>

namespace Ill
{
    namespace Core
    {
        DynamicLibSubsystem::DynamicLibSubsystem()
        {
		}

        DynamicLibSubsystem::~DynamicLibSubsystem()
        {
        }

        bool DynamicLibSubsystem::Startup( const PropertyMap& startupOptions )
        {
            return Super::Startup( startupOptions );
        }

        bool DynamicLibSubsystem::Shutdown()
        {
            Super::Shutdown();

            // Unload any libs that may still be loaded.
            LibraryList::iterator iter = m_Libs.begin();
            while( iter != m_Libs.end() )
            {
                DynamicLibPtr lib = iter->second;
                lib->Unload();

                ++iter;
            }

            m_Libs.clear();

            return true;
        }

        DynamicLibWeakPtr DynamicLibSubsystem::Load( const std::wstring& libPath )
        {
            LibraryList::iterator iter = m_Libs.find( libPath );
            if ( iter != m_Libs.end() )
            {
                return iter->second;
            }

            DynamicLibPtr pLib = boost::make_shared<DynamicLib>( libPath );
            pLib->Load();
            m_Libs.insert( LibraryList::value_type( libPath, pLib ) );

            return pLib;
        }

        void DynamicLibSubsystem::Unload( DynamicLibWeakPtr lib )
        {            
			if ( DynamicLibPtr pLib = lib.lock() )
			{
                LibraryList::iterator iter = m_Libs.find( pLib->LibName );
                if ( iter != m_Libs.end() )
				{
                    m_Libs.erase( iter );
				}

				pLib->Unload();
			}
        }

    }
}