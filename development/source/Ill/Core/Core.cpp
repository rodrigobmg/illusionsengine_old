#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/Core.hpp>

namespace Ill
{
	namespace Core
	{
		void InstantiateTypes()
		{
			NoCopyObject();
			RefCountedObject();
			Object();
			Component();
			Subsystem();
			PluginSubsystem();
			Application();
			PropertyMap();
		}
	}
}