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
                    // NOTE: This doesn't work.  The property doesn't like the value returned from boost::any_cast.
                    // I don't know why yet, but for now, each class has to populate it's own property data.
                    
                    if ( type == typeid(std::string) )
                    {
                        try 
                        {
                            prop.set( this, boost::any_cast<std::string>(propertyValue) );
                        }
                        catch ( boost::bad_any_cast& exp )
                        {
                            std::cerr << "Could not cast boost::any: " << exp.what() << std::endl;
                        }
                        catch ( TypeMismatchError& )
                        {
                            std::cerr << "Could not cast \"" << type.name() << "\" to property type \"" << propertyValue.type().name() << "\"" << std::endl;
                        }
                        catch ( std::exception& exp )
                        {
                            std::cerr << "A general error occurred while trying to cast a property value: " << exp.what() << std::endl;
                        }
                    }
                    
                }

                ++iter;
            }
        }
	}
}