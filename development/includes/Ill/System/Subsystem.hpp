#ifndef __Ill_System_Subsystem_H__
#define __Ill_System_Subsystem_H__
/**
* @file Subsystem.h
* @date December 09, 2008
* @author Jeremiah van Oosten
* 
* @brief The subsystem definition.
* @description This class is the abstract base class for all subsystem components
* that can be registered and managed by the Application class.
*/
#include <Ill/System/PropertyMap.hpp>
#include <Ill/System/Component.hpp>

namespace Ill
{
	namespace System
	{
		class Subsystem : public Component
		{
		public:
			CLASS(Subsystem,Component);
			CONSTRUCTOR(public,Subsystem,());

			/**
			* Startup
			*/
			VIRTUAL_METHOD(public,bool,Startup,( const PropertyMap& startupOptions ));

			/**
			* Shutdown
			*/
			VIRTUAL_METHOD(public,bool,Shutdown,());

        protected:
            /**
            * Populate my defined properties from the passed-in property map
            */
            VIRTUAL_METHOD(public,void,GetProperties,(const PropertyMap& properties) );

		};

		typedef boost::intrusive_ptr<Subsystem> SubsystemPtr;
	}
}

#endif // __Ill_System_Subsystem_H__