/**
 * @file DynamicLibSubsystem.hpp
 * @date September 25, 2009
 *
 * Handles loading and unlading Dynamic libraries (DLL on Windows, Shared Objects on Linux).
 */

#include <Ill/System/Subsystem.hpp>
#include <Ill/System/DynamicLib.hpp>

namespace Ill
{
    namespace System
    {
        class DynamicLibSubsystem : public Subsystem
        {
        public:
            CLASS(DynamicLibSubsystem,Subsystem);
            CONSTRUCTOR(public,DynamicLibSubsystem,());
            virtual ~DynamicLibSubsystem();

            /**
            * Startup
            */
            VIRTUAL_METHOD(public,bool,Startup,( const PropertyMap& startupOptions ));

            /**
            * Shutdown
            */
            VIRTUAL_METHOD(public,bool,Shutdown,());

            /**
             * Loads a .DLL or an .SO by filename.
             * @returns a pointer to the loaded lib, or a NULL pointer if the lib can't be loaded.
             */
            VIRTUAL_METHOD(public, DynamicLib*, Load,( const String& libName ) );

            /**
             * Unloads a dynamic loaded lib
             */
            VIRTUAL_METHOD(public,void,Unload, ( DynamicLib* lib ) );

        private:
            typedef std::map<String, DynamicLib* > LibList;
            LibList     m_LibList;
        };
    }
}