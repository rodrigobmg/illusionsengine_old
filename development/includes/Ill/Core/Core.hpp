/**
 * @file
 */

#ifndef ILL_CORE_HPP
#define ILL_CORE_HPP

#include <Ill/Core/CorePlatform.hpp>
#include <Ill/Core/KeyboardKeys.hpp>
#include <Ill/Core/MouseDefines.hpp>
#include <Ill/Core/Events.hpp>
#include <Ill/Core/CoreUtils.hpp>
#include <Ill/Core/Singleton.hpp>
#include <Ill/Core/NoCopyObject.hpp>
#include <Ill/Core/RefCountedObject.hpp>
#include <Ill/Core/Object.hpp>
#include <Ill/Core/GameObject.hpp>
#include <Ill/Core/PropertyMap.hpp>
#include <Ill/Core/Component.hpp>
#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/Application.hpp>
#include <Ill/Core/Plugin.hpp>
#include <Ill/Core/DynamicLibSubsystem.hpp>
#include <Ill/Core/DynamicLib.hpp>

namespace Ill
{
	namespace Core
	{
		/**
		* This method is used to instantiate all the class types that use reflection.
		* This is necessary to ensure the class types can be queried from the reflection system.
		*/
		CORE_DLL void InstantiateTypes();
	}
}

#endif
