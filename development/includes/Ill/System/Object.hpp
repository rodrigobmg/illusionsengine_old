#ifndef __Ill_System_Object_H__
#define __Ill_System_Object_H__
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
#include "Ill/System/RefCountedObject.hpp"

namespace Ill
{
	namespace System
	{
		class Object : public RefCountedObject
		{
		public:
			CLASS(Object,RefCountedObject);
			CONSTRUCTOR(public,Object,() );

            PROPERTY( const std::string&, Name );

			// TODO: Implement object serialization methods (see boost/Serialization)
		protected:
		private:

            // Getters and setters for properties
            const std::string& get_Name() const;
            void set_Name( const std::string& name );

            // Data members
            std::string     m_Name;


		};

		typedef boost::intrusive_ptr<Object> ObjectPtr;
	}
}

#endif // __Ill_System_Object_H__