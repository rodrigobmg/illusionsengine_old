#include <Ill/System/PrecompiledHeader.hpp>
#include <Ill/System/System.hpp>

namespace Ill
{
	namespace System
	{
		void InstantiateTypes()
		{
			NoCopyObject();
			RefCountedObject();
			Object();
			Component();
			Subsystem();
			DynamicLibSubsystem();
			Application();
			PropertyMap();
		}
	}
}