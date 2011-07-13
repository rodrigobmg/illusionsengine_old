/**
* @file Subsystem.h
* @date December 09, 2008
* @author Jeremiah van Oosten
* 
* @brief The subsystem definition.
* @description This class is the abstract base class for all subsystem components
* that can be registered and managed by the Application class.
*/

#ifndef ILL_CORE_SUBSYSTEM_HPP
#define ILL_CORE_SUBSYSTEM_HPP

#include <Ill/Core/PropertyMap.hpp>
#include <Ill/Core/Object.hpp>

namespace Ill
{
	namespace Core
	{
		class Subsystem : public Object
		{
		public:
			CLASS(Subsystem,Object);
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
	}
}

#endif // ILL_CORE_SUBSYSTEM_HPP