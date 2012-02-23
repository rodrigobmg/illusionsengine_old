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

        void DynamicLibSubsystem::Initialize()
        {
            Super::Initialize();
        }

        void DynamicLibSubsystem::Terminate()
        {
            Super::Terminate();

            // Unload any libs that may still be loaded.
            LibraryList::iterator iter = m_Libs.begin();
            while( iter != m_Libs.end() )
            {
                DynamicLibPtr lib = iter->second;
                Unload( lib );
                ++iter;
            }
            
            BOOST_ASSERT( m_Libs.empty() );

            // The Application class must manually flush the dynamic lib subsystem
            // after all pointers to objects loaded from the library are released.
            // Flush()
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
                    m_LibsToFlush.push_back( lib );
                    m_Libs.erase( iter );
				}
			}
        }

        void DynamicLibSubsystem::Flush()
        {
            LibraryVector::iterator iter = m_LibsToFlush.begin();
            while ( iter != m_LibsToFlush.end() )
            {
                DynamicLibPtr lib = (*iter);
                lib->Unload();

                ++iter;
            }
            m_LibsToFlush.clear();
        }
    }
}