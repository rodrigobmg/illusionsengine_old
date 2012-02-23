#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/Subsystem.hpp>

namespace Ill
{
	namespace Core
	{
		Subsystem::Subsystem()
		{}

        void Subsystem::Initialize()
		{
            Super::Initialize();
		}

		void Subsystem::Terminate()
		{
            Super::Terminate();
		}
	}
}