/**
 * @file: SceneDescription
 * @date: September 16, 2009
 *
 * Scene description is used to create a physics scene.
 */

#ifndef ILL_PHYSICS_SCENEDESCRIPTION_HEADER_HPP
#define ILL_PHYSICS_SCENEDESCRIPTION_HEADER_HPP

#include <Ill/Core/Object.hpp>

namespace Ill
{
	namespace Physics
	{
		class SceneDescription : public Ill::Core::Object
		{
		public:
			CLASS( SceneDescription, Ill::Core::Object );
			CONSTRUCTOR( public, SceneDescription, () );



		};
	}
}

#endif // ILL_PHYSICS_SCENEDESCRIPTION_HEADER_HPP