/**
 * @file
 */

#ifndef ILL_SYSTEM_HPP
#define ILL_SYSTEM_HPP

#include <Ill/System/NoCopyObject.hpp>
#include <Ill/System/RefCountedObject.hpp>
#include <Ill/System/Object.hpp>
#include <Ill/System/PropertyMap.hpp>
#include <Ill/System/Component.hpp>
#include <Ill/System/Subsystem.hpp>
#include <Ill/System/Application.hpp>

namespace Ill
{
	namespace System
	{
		/**
		* This method is used to instantiate all the class types that use reflection.
		* This is necessary to ensure the class types can be queried from the reflection system.
		*/
		void InstantiateTypes();
	}
}

#endif
