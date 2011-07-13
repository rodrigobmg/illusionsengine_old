#ifndef ILL_CORE_NOCOPYOBJECT_HPP
#define ILL_CORE_NOCOPYOBJECT_HPP

/**
* @file NoCopyObject.h
* @date April 14, 2009
* @author Jeremiah van Oosten
* 
* @brief Derive your class from this base class if you want to prevent
* copies of your class being created unless explicitly stated by 
* changing the scope of the member functions.  
* @description This is to prevent users from creating a classes that have 
* default (compiler-generated) copy-constructor and assignment operator which 
* can be bad if the class owns heap-allocated or shared memory.
*/

#include <Ill/Core/reflection.hpp>

using namespace agm::reflection;

namespace Ill
{
	namespace Core
	{
		class _IllExport NoCopyObject
		{
		public:
			CLASS(NoCopyObject,NullClass);
			// Object can still be created or destroyed
			CONSTRUCTOR(public,NoCopyObject,());
			virtual ~NoCopyObject();

		private:
			// No default copy constructor
			NoCopyObject( const NoCopyObject& copy );
			// No default assignment operator
			NoCopyObject& operator=( const NoCopyObject& other );
		};
	}
}

#endif // ILL_CORE_NOCOPYOBJECT_HPP