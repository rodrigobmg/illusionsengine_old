#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/Component.hpp>

namespace Ill
{
	namespace Core
	{
		Component::Component()
		{}

		Component::~Component()
		{}

        void Component::Serialize()
        {}

        void Component::Initialize() 
		{}

		void Component::LoadResources()
		{}

        void Component::Update( float elapsedTime )
        {}

        void Component::FixedUpdate( float elapsedTime )
        {}

		void Component::FlushResources()
		{}

		void Component::Terminiate()
		{}
	}
}