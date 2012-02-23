#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/Object.hpp>

namespace Ill
{
	namespace Core
	{
		Object::Object()
            : m_UUID(uuid_generator())
        {}

        template<class Archive>
        void Object::serialize( Archive& ar, const unsigned int version )
        {
            ar & m_Name;
            ar & m_UUID;
        }

        void Object::Initialize()
        {}

        void Object::Terminate()
        {}

        const std::string& Object::get_Name() const
        {
            return m_Name;
        }

        void Object::set_Name( const std::string& name )
        {
            m_Name = name;
        }

        const boost::uuids::uuid& Object::get_UUID() const
        {
            return m_UUID;
        }

        void Object::set_UUID( const boost::uuids::uuid& uuid )
        {
            // Should it be allowed to change the UUID of an object?
            // Maybe only during deserialization of the object.
            m_UUID = uuid;
        }

	}
}