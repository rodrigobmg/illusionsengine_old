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

#include <Ill/Core/Object.hpp>
#include <Ill/Core/Subsystem.fwd.hpp>
#include <Ill/Core/Application.fwd.hpp>

namespace Ill
{
	namespace Core
	{
		class CORE_DLL Subsystem : public Object
		{
		public:
			CLASS( Subsystem, Object );
			CONSTRUCTOR( CORE_DLL, public, Subsystem, () );

			/**
			* Initialize
			*/
			VIRTUAL_METHOD( CORE_DLL, public, void, Initialize, () );

			/**
			* Terminate
			*/
			VIRTUAL_METHOD( CORE_DLL, public, void, Terminate, () );

        protected:

        private:
		};
	}
}

#endif // ILL_CORE_SUBSYSTEM_HPP