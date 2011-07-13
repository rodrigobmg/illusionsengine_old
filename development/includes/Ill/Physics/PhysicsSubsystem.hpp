/**
 * The Physics Subsystem
 */

#ifndef ILL_PHYSICS_PHYSICSSUBSYSTEM_HEADER_HPP
#define ILL_PHYSICS_PHYSICSSUBSYSTEM_HEADER_HPP

#include <Ill/Core/Subsystem.hpp>

namespace Ill
{
	namespace Physics
	{
		class PhysicsSubsystem : public Ill::Core::Subsystem
		{
			CLASS(PhysicsSubsystem,Ill::Core::Subsystem);
			CONSTRUCTOR(public,PhysicsSubsystem,());

			/**
			* Startup
			*/
			VIRTUAL_METHOD(public,bool,Startup,( const Ill::Core::PropertyMap& startupOptions ));

			/**
			* Shutdown
			*/
			VIRTUAL_METHOD(public,bool,Shutdown,());

		};

		typedef boost::intrusive_ptr<PhysicsSubsystem> PhysicsSubsystemPtr;

	}
}

#endif // ILL_PHYSICS_PHYSICSSUBSYSTEM_HEADER_HPP