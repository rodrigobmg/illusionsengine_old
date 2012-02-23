/**
 * @file DynamicLibSubsystem.hpp
 * @date September 25, 2009
 *
 * Handles loading and unloading of Dynamic libraries (DLL on Windows, Shared Objects on Linux).
 */

#ifndef ILL_CORE_DYNAMIDLIBSUBSYSTEM_HPP
#define ILL_CORE_DYNAMIDLIBSUBSYSTEM_HPP

#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/Plugin.fwd.hpp>
#include <Ill/Core/DynamicLibSubsystem.fwd.hpp>
#include <Ill/Core/DynamicLib.fwd.hpp>

namespace Ill
{
    namespace Core
    {
        class CORE_DLL DynamicLibSubsystem : public Subsystem
        {
        public:
            CLASS( DynamicLibSubsystem, Subsystem );
            CONSTRUCTOR( CORE_DLL, public, DynamicLibSubsystem, () );
            virtual ~DynamicLibSubsystem();

            /**
            * Initialize
            */
            VIRTUAL_METHOD( CORE_DLL, public, void, Initialize, () );

            /**
            * Terminate
            */
            VIRTUAL_METHOD( CORE_DLL, public, void, Terminate, () );

            /**
             * Loads a .DLL or an .SO by filename.
             * @returns a weak-pointer to the loaded library.
             * @throws This method will throw an exception if the library couldn't be loaded.
             */
            VIRTUAL_METHOD( CORE_DLL, public, DynamicLibPtr, Load, ( const std::wstring& libPath ) );

            /**
             * Returns a pointer to a previously loaded library or NULL if the library wasn't found.
             * @returns a pointer to the loaded library, or a empty pointer if the library isn't loaded.
             */
            VIRTUAL_METHOD( CORE_DLL, public, DynamicLibPtr, GetLibrary, ( const std::wstring& libPath ) );

            /**
             * Unloads a dynamic loaded lib
             */
            VIRTUAL_METHOD( CORE_DLL, public, void, Unload, ( DynamicLibPtr lib ) );
            
            /**
             * Flush all the libraries that have been unloaded.
             * This will cause any library that was unloaded to be flushed
             * from the system.  At this point, there shouldn't be any
             * valid handles to objects created inside the library including
             * handles to plug-ins that were created in the library.
             */
            VIRTUAL_METHOD( CORE_DLL, public, void, Flush, () );

        private:
            typedef std::map<std::wstring, DynamicLibPtr > LibraryList;
            typedef std::vector< DynamicLibPtr > LibraryVector;

            LibraryList m_Libs;
            LibraryVector m_LibsToFlush;
        };
    }
}

#endif // ILL_CORE_DYNAMIDLIBSUBSYSTEM_HPP