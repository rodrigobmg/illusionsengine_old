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

        DynamicLibPtr DynamicLibSubsystem::Load( const std::wstring& libPath )
        {
            DynamicLibPtr ptrLib = GetLibrary( libPath );
            if ( ptrLib )
            {
                return ptrLib;
            }

            DynamicLibPtr pLib = boost::make_shared<DynamicLib>( libPath );
            pLib->Load();
            m_Libs.insert( LibraryList::value_type( libPath, pLib ) );

            return pLib;
        }

        DynamicLibPtr DynamicLibSubsystem::GetLibrary( const std::wstring& libPath )
        {
            DynamicLibPtr ptrLib;
            LibraryList::iterator iter = m_Libs.find(libPath);
            if ( iter != m_Libs.end() )
            {
                ptrLib = (iter->second);
            }

            return ptrLib;
        }

        void DynamicLibSubsystem::Unload( DynamicLibPtr lib )
        {            
			if ( lib )
			{
                LibraryList::iterator iter = m_Libs.find( lib->FileName );
                if ( iter != m_Libs.end() )
				{
                    m_Libs.erase( iter );
				}

				lib->Unload();
			}
        }

    }
}