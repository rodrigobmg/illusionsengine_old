#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/NoCopyObject.hpp>

namespace Ill
{
	namespace Core
	{
		// Public ctors.
		NoCopyObject::NoCopyObject() {}
		NoCopyObject::~NoCopyObject() {}

		// Private operations
		// These need to be overridden to allow classes to be copied
		//		NoCopyObject::NoCopyObject( const NoCopyObject& copy ) {}
		//		NoCopyObject& NoCopyObject::operator=( const NoCopyObject& other ) { return *this; }
	}
}