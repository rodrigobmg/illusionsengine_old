#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/Object.hpp>

namespace Ill
{
	namespace Core
	{
		Object::Object() {}

        const std::string& Object::get_Name() const
        {
            return m_Name;
        }

        void Object::set_Name( const std::string& name )
        {
            m_Name = name;
        }
	}
}