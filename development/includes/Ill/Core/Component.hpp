#ifndef ILL_CORE_COMPONENT_HPP
#define ILL_CORE_COMPONENT_HPP
/**
* @file Component.h
* @date April 15, 2009
* @author Jeremiah van Oosten
*/

#include <Ill/Core/Object.hpp>
#include <Ill/Core/Component.fwd.hpp>

namespace Ill
{
	namespace Core
	{
		class CORE_DLL Component : public Object
		{
		public:
            
			CLASS( Component, Object );
			CONSTRUCTOR( CORE_DLL, public, Component, () );
			virtual ~Component();

			/**
			* Serialize this component.
			* TODO: Create the serialize class that holds the serialization 
			* stream (boost/serialize).
			* 
			* @returns true if serialization was successful.
			*/
			VIRTUAL_METHOD( CORE_DLL, public, void, Serialize,() );

            /**
			* Initialize any memory needed by this component.
			* This should be called on all newly created components
            * since the constructor will usually never allocate anything.
            *
			* @returns true if all memory allocations were successful.
			*/
			VIRTUAL_METHOD( CORE_DLL, public, void, Initialize, () );

			/**
			* Load any resources from disc.
			* Resource loading should be limited to this function to ensure 
			* that objects can be re-serialized properly at run-time.
			*
			* @returns true if all resources were loaded successfully.
			*/
			VIRTUAL_METHOD( CORE_DLL, public, void, LoadResources, () );

            /**
             * Allows this component to be updated using a variable time-step.
             * If you need the component to be updated using a fixed time-step,
             * override the @see(FixedUpdate) method instead.
             */
            VIRTUAL_METHOD( CORE_DLL, public, void, Update, (float elapsedTime) );

            /**
             * Allows this component to be updated using a fixed time-step.
             * If you need the component to be updated with a variable time-step,
             * override the @see(Update) method instead.
             */
            VIRTUAL_METHOD( CORE_DLL, public, void, FixedUpdate, (float elapsedTime) );

			/**
			* Resources should be released here.
			* Usually nothing needs to be done here as resources will be 
			* released automatically if the handles to those resources goes out
			* of scope or the handle is reset to another resource.
			*
			* @returns true if all resources were released properly.
			*/
			VIRTUAL_METHOD( CORE_DLL, public, void, FlushResources, () );

			/**
			* Deallocate the memory that was allocated in Initialize.
			* It should be possible to invoke this method many times
            * without an error or exception being thrown.  This way, 
            * components can be recycled without deleting them.
            * 
			* @returns true if all memory allocations were successful.
			*/
			VIRTUAL_METHOD( CORE_DLL, public, void, Terminiate, () );

		protected:

		private:
			// Property accessors

		};
	}
}


#endif // ILL_CORE_COMPONENT_HPP