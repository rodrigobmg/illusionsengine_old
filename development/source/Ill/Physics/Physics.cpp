#include <Ill/System/Physics/PrecompiledHeader.hpp>
#include <Ill/System/Physics/Physics.hpp>

namespace Ill
{
	namespace System
	{
		namespace Physics
		{
			void InstantiateTypes()
			{
				PhysicsSubsystem();
				SceneDescription();
//				PhysicsSimulation(); // This class is abstract
			}
		}
	}
}