#include <Ill/System/PrecompiledHeader.hpp>
#include <Ill/System/Component.hpp>

namespace Ill
{
	namespace System
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