/**
 * @file: SceneDescription
 * @date: September 16, 2009
 *
 * Scene description is used to create a physics scene.
 */

#ifndef ILL_SYSTEM_PHYSICS_SCENEDESCRIPTION_HEADER_HPP
#define ILL_SYSTEM_PHYSICS_SCENEDESCRIPTION_HEADER_HPP

#include <Ill/System/Object.hpp>

namespace Ill
{
	namespace System
	{
		namespace Physics
		{
			class SceneDescription : public Ill::System::Object
			{
			public:
				CLASS(SceneDescription,Ill::System::Object);
				CONSTRUCTOR(public,SceneDescription,());



			};
		}
	}
}

#endif // ILL_SYSTEM_PHYSICS_SCENEDESCRIPTION_HEADER_HPP