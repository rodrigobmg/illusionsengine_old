#include <Ill/System/PrecompiledHeader.hpp>
#include <Ill/System/Object.hpp>

namespace Ill
{
	namespace System
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