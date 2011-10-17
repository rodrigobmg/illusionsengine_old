#ifndef ILL_CORE_OBJECT_HPP
#define ILL_CORE_OBJECT_HPP
/**
* @file Object.h
* @date April 14, 2009
* @author Jeremiah van Oosten
* 
* @brief The base class for all managed objects.
* @description All classes should be derived from this class.<br>
* The Object class defines the base class for all other classes.<br>
* The Object class defines the main interface for:<br>
* <ul>
*  <li>Run-Time Type Information (RTTI)</li>
*  <li>Reflection</li>
*  <li>Memory Management and Garbage Collection</li>
*  <li>Serialization and class versioning</li>
* </ul>
*/
#include <Ill/Core/NoCopyObject.hpp>
#include <Ill/Core/Object.fwd.hpp>

namespace Ill
{
	namespace Core
	{
		class CORE_DLL Object : public NoCopyObject
		{
		public:
			CLASS( Object, NoCopyObject );
			CONSTRUCTOR( CORE_DLL, public, Object, () );

			// TODO: Implement object serialization methods (see boost/Serialization)
		protected:
            // Getters and setters for properties
            const std::string& get_Name() const;
            void set_Name( const std::string& name );

            const boost::uuids::uuid& get_UUID() const;
            void set_UUID( const boost::uuids::uuid& uuid );

        private:
            // Data members
            std::string     m_Name;
            // A unique identifier that represents this object.
            boost::uuids::uuid m_UUID;

        public:
            PROPERTY( CORE_DLL, const std::string&, Name );
            PROPERTY( CORE_DLL, const boost::uuids::uuid&, UUID );

		};
	}
}

#endif // __Ill_System_Object_H__