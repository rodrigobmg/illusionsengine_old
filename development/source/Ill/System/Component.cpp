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

		bool Component::Initialize() 
		{
			return true;
		}

		bool Component::Serialize()
		{
			return true;
		}

		bool Component::LoadResources()
		{
			return true;
		}

		bool Component::FlushResources()
		{
			return true;
		}

		bool Component::Terminiate()
		{
			return true;
		}
	}
}