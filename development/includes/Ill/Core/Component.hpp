#ifndef ILL_CORE_COMPONENT_HPP
#define ILL_CORE_COMPONENT_HPP
/**
* @file Component.h
* @date April 15, 2009
* @author Jeremiah van Oosten
* 
* @brief The main component class.
* @description Components are any objects that need to implement the basic
* component life-cycle: <br>
* <ol>
*  <li>Initialize</li>
*  <li>Serialize</li>
*  <li>LoadResources</li>
*  <li>FlushResources</li>
*  <li>Terminate</li>
* </ol>
*/

#include <Ill/Core/Object.hpp>

namespace Ill
{
	namespace Core
	{
		class Component : public Object
		{
		public:

			CLASS(Component,Object);
			CONSTRUCTOR(public,Component,());
			virtual ~Component();

			/**
			* Initialize any memory needed by this component.
			* 
			* @returns true if all memory allocations were successful.
			*/
			VIRTUAL_METHOD(public,void,Initialize,());
			/**
			* Serialize this component.
			* TODO: Create the serialize class that holds the serialization 
			* stream (boost/serialize).
			* 
			* @returns true if serialization was successful.
			*/
			VIRTUAL_METHOD(public,void,Serialize,());

			/**
			* Load any resources from disc.
			* Resource loading should be limited to this function to ensure 
			* that objects can be re-serialized properly at run-time.
			*
			* @returns true if all resources were loaded successfully.
			*/
			VIRTUAL_METHOD(public,void,LoadResources,());

			/**
			* Resources should be released here.
			* Usually nothing needs to be done here as resources will be 
			* released automatically if the handles to those resources goes out
			* of scope or the handle is reset to another resource.
			*
			* @returns true if all resources were released properly.
			*/
			VIRTUAL_METHOD(public,void,FlushResources,());

			/**
			* Deallocate the memory that was allocated in Initialize.
			*
			* @returns true if all memory allocations were successful.
			*/
			VIRTUAL_METHOD(public,void,Terminiate,());

		protected:

		private:
			// Property accessors

		};

		typedef boost::intrusive_ptr<Component> ComponentPtr;
	}
}


#endif // ILL_CORE_COMPONENT_HPP