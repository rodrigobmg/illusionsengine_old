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

            /**
            * Initialize any memory needed by this object.
            * 
            * @returns true if all memory allocations were successful.
            */
            VIRTUAL_METHOD( CORE_DLL, public, void, Initialize, () );

            /**
            * Deallocate the memory that was allocated in Initialize.
            * It should be possible to invoke this method many times
            * without an error or exception being thrown.  This way, 
            * objects can be recycled without deleting them.
            * 
            * @returns true if all memory allocations were successful.
            */
            VIRTUAL_METHOD( CORE_DLL, public, void, Terminate, () );

		protected:
            // Getters and setters for properties
            const std::string& get_Name() const;
            void set_Name( const std::string& name );

            const boost::uuids::uuid& get_UUID() const;
            void set_UUID( const boost::uuids::uuid& uuid );

        private:
            friend class boost::serialization::access;
            /**
             * Serialize or de-serialize the properties of an object.
             * Note: This method must always be declared private.
             * To allow the archive class access to private members
             * and methods of base classes, your class must allow
             * the boost::serialization::access class friend access by declaring 
             * it as a friend class.  Base classes are serialized by calling 
             * ar & boost::serialization::base_object<Super>(*this)
             * inside the serialize method.
             *
             * @param ar The archive object to serialize from or to.
             * @param version The class version when the object was serialized.
             */
            template<class Archive>
            void serialize( Archive& ar, const unsigned int version );

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

BOOST_CLASS_VERSION( Ill::Core::Object, 0 )

#endif // ILL_CORE_OBJECT_HPP