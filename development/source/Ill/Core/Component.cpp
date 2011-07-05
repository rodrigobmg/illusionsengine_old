#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/Component.hpp>

namespace Ill
{
	namespace Core
	{
		Component::Component()
		{}

		Component::~Component()
		{
		}

		void Component::Initialize() 
		{}

		void Component::Serialize()
		{}

		void Component::LoadResources()
		{}

		void Component::FlushResources()
		{}

		void Component::Terminiate()
		{}
	}
}