#include <Ill/Physics/PrecompiledHeader.hpp>
#include <Ill/Physics/Physics.hpp>

namespace Ill
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