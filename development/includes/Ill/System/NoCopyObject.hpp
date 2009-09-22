#ifndef __Ill_System_NoCopyObject_H__
#define __Ill_System_NoCopyObject_H__

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

#include <boost/intrusive_ptr.hpp>
#include <Ill/System/reflection.hpp>

using namespace agm::reflection;

namespace Ill
{
	namespace System
	{
		class NoCopyObject
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

#endif // __Ill_System_NoCopyObject_H__