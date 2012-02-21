/**
 * @file: PhysicsSubsystem.cpp
 * @date: September 16, 2009
 * 
 * 
 */

#include <Ill/Physics/PhysicsPCH.hpp>
#include <Ill/Physics/PhysicsSubsystem.hpp>

namespace Ill
{
	namespace Physics
	{
		PhysicsSubsystem::PhysicsSubsystem()
		{}

		bool PhysicsSubsystem::Startup( const boost::property_tree::ptree& statupOptions )
		{
			return true;
		}

		bool PhysicsSubsystem::Shutdown()
		{
			return true;
		}
	}
}
