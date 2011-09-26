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
            GameObject();
			Component();
			Subsystem();
			PluginSubsystem();
			Application();
			PropertyMap();
		}

        boost::uuids::random_generator uuid_generator;
	}
}