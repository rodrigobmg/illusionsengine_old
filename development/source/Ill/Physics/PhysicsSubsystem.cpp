/**
 * @file: PhysicsSubsystem.cpp
 * @date: September 16, 2009
 * 
 * 
 */

#include <Ill/Physics/PrecompiledHeader.hpp>
#include <Ill/Physics/PhysicsSubsystem.hpp>

namespace Ill
{
	namespace Physics
	{
		PhysicsSubsystem::PhysicsSubsystem()
		{}

		bool PhysicsSubsystem::Startup( const Ill::System::PropertyMap& statupOptions )
		{
			return true;
		}

		bool PhysicsSubsystem::Shutdown()
		{
			return true;
		}
	}
}
