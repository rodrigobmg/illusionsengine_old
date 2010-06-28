/**
 * The Physics Subsystem
 */

#ifndef ILL_PHYSICS_PHYSICSSUBSYSTEM_HEADER_HPP
#define ILL_PHYSICS_PHYSICSSUBSYSTEM_HEADER_HPP

#include <Ill/System/Subsystem.hpp>

namespace Ill
{
	namespace Physics
	{
		class PhysicsSubsystem : public Ill::System::Subsystem
		{
			CLASS(PhysicsSubsystem,Ill::System::Subsystem);
			CONSTRUCTOR(public,PhysicsSubsystem,());

			/**
			* Startup
			*/
			VIRTUAL_METHOD(public,bool,Startup,( const Ill::System::PropertyMap& startupOptions ));

			/**
			* Shutdown
			*/
			VIRTUAL_METHOD(public,bool,Shutdown,());

		};

		typedef boost::intrusive_ptr<PhysicsSubsystem> PhysicsSubsystemPtr;

	}
}

#endif // ILL_PHYSICS_PHYSICSSUBSYSTEM_HEADER_HPP