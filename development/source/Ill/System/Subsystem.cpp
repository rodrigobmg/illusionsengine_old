#include <Ill/System/PrecompiledHeader.hpp>
#include <Ill/System/Subsystem.hpp>

namespace Ill
{
	namespace System
	{
		Subsystem::Subsystem()
		{}

		bool Subsystem::Startup( const PropertyMap& statupOptions )
		{
			return true;
		}

		bool Subsystem::Shutdown()
		{
			return true;
		}

        void Subsystem::GetProperties(const PropertyMap& properties)
        {
            const Class& myClass = getClass();
            const Class::PropertyList& props = myClass.getProperties();
            Class::PropertyList::const_iterator iter = props.begin();

            while( iter != props.end() )
            {
                const Property& prop = (*iter);

                std::string propertyName = prop.getName();

                // Try to find the property in the property map
                boost::any propertyValue;
                if( properties.GetValue( propertyName, propertyValue ) )
                {
                    const std::type_info& type = propertyValue.type();
                    // Try to determine the type of the property 
                    if ( type == typeid(std::string) )
                    {
                        prop.set( this, boost::any_cast<std::string>(propertyValue) );
                    }
                }

                ++iter;
            }
        }
	}
}