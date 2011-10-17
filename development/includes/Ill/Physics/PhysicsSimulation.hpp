/**
 * @file: PhysicsSimulation.hpp
 * @date: September 16, 2009
 * 
 * The Physics Simulation is the interface to the Physics implementation.
 */

#ifndef ILL_PHYSICS_PHYSICSSIMULATION_HPP
#define ILL_PHYSICS_PHYSICSSIMULATION_HPP

#include <Ill/Core/Object.hpp>
#include <Ill/Physics/SceneDescription.hpp>

namespace Ill
{
	namespace Physics
	{
		class PHYSICS_DLL PhysicsSimulation : public Ill::Core::Object
		{
		public:
			CLASS( PhysicsSimulation, Ill::Core::Object );
			CONSTRUCTOR( PHYSICS_DLL, public, PhysicsSimulation, () );

			VIRTUAL_METHOD( PHYSICS_DLL, public, void, CreatePhysicsScene, (const SceneDescription& desc) );
		};
	}
}

#endif // ILL_PHYSICS_PHYSICSSIMULATION_HPP