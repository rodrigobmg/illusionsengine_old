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
		class PHYSICS_DLL PhysicsSubsystem : public Ill::Core::Subsystem
		{
			CLASS( PhysicsSubsystem, Ill::Core::Subsystem );
			CONSTRUCTOR( PHYSICS_DLL, public, PhysicsSubsystem, () );

			/**
			* Startup
			*/
            VIRTUAL_METHOD( PHYSICS_DLL, public, bool, Startup, ( const boost::property_tree::ptree& startupOptions ) );

			/**
			* Shutdown
			*/
			VIRTUAL_METHOD( PHYSICS_DLL, public, bool, Shutdown, () );

		};
	}
}

#endif // ILL_PHYSICS_PHYSICSSUBSYSTEM_HEADER_HPP