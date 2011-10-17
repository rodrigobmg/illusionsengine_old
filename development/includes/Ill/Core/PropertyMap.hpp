#ifndef ILL_CORE_PROPERTYMAP_HPP
#define ILL_CORE_PROPERTYMAP_HPP
/**
* @file PropertyMap.h
* @date April 15, 2008
* @author Jeremiah van Oosten
* 
* @brief A container class that can store any type in it's value.
*/
#include <boost/any.hpp>
#include <Ill/Core/Object.hpp>

namespace Ill
{
	namespace Core
	{
		class CORE_DLL PropertyMap : public Object
		{
		public:
			typedef std::map< std::string, boost::any > map;
			typedef map::iterator						iterator;
			typedef map::const_iterator					const_iterator;

			CLASS( PropertyMap, Object );
			CONSTRUCTOR( CORE_DLL, public, PropertyMap,() );
			virtual ~PropertyMap();

			/**
			* Add a value to the property map.
			*
			* @param key The key that is associated with the value.
			* @param value The value to insert into the property map.
			* 
			* @precondition none
			* @postcondition The value is inserted into the map as a new value
			* or if there is a value with the associated key already exists in the map,
			* it will be replaced.
			*/
			template <typename T>
			void AddValue( const std::string& key, const T& value );

			/**
			* Retrieve a value from the map.
			* 
			* @param key The key that is associated with the value to retrieve.
			* @param value A non-const holder for the value found in the map.
			* @returns true if the value was found in the map and stored in the value,
			* or false if the key was not found in the map.
			*/
			template <typename T>
			bool GetValue( const std::string& key, T& value ) const;

            /**
             * Specialization for a boost::any type. (Useful if we don't know the type in advance).
             */
            bool GetValue( const std::string& key, boost::any& value ) const;

			/**
			* Clear this property map.
			* 
			* @postcondition The property map is empty.
			*/
			void Clear();


		private:
			map		m_Properties;

		};
	}
}

#include "PropertyMap.inl"

#endif //ILL_CORE_PROPERTYMAP_HPP