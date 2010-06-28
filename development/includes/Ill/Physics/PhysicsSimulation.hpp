/**
 * @file: PhysicsSimulation.hpp
 * @date: September 16, 2009
 * 
 * The Physics Simulation is the interface to the Physics implementation.
 */

#ifndef ILL_SYSTEM_PHYSICS_PHYSICSSIMULATION_HEADER_HPP
#define ILL_SYSTEM_PHYSICS_PHYSICSSIMULATION_HEADER_HPP

#include <Ill/System/Object.hpp>
#include <Ill/System/Physics/SceneDescription.hpp>

namespace Ill
{
	namespace System
	{
		namespace Physics
		{
			class PhysicsSimulation : public Ill::System::Object
			{
			public:
				CLASS(PhysicsSimulation,Ill::System::Object);
				CONSTRUCTOR(public,PhysicsSimulation,());

				VIRTUAL_METHOD(public,void,CreatePhysicsScene,(const SceneDescription& desc));
			};
		}
	}
}

#endif // ILL_SYSTEM_PHYSICS_PHYSICSSIMULATION_HEADER_HPP