/**
 * @file DynamicLibSubsystem.hpp
 * @date September 25, 2009
 *
 * Handles loading and unlading Dynamic libraries (DLL on Windows, Shared Objects on Linux).
 */

#ifndef ILL_CORE_DYNAMICLIBSUBSYSTEM_HPP
#define ILL_CORE_DYNAMICLIBSUBSYSTEM_HPP

#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/DynamicLib.hpp>

namespace Ill
{
    namespace Core
    {
        class DynamicLibSubsystem : public Subsystem
        {
        public:
            CLASS(DynamicLibSubsystem,Subsystem);
            CONSTRUCTOR(public,DynamicLibSubsystem,());
            virtual ~DynamicLibSubsystem();

			/**
			 * Get a reference to our singleton instance.
			 */
			STATIC_METHOD( public, DynamicLibSubsystem&, GetSingleton, () );

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

			static DynamicLibSubsystem* ms_Singleton;
        };
    }
}

#endif // ILL_CORE_DYNAMICLIBSUBSYSTEM_HPP