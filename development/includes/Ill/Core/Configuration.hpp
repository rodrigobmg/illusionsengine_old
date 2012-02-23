#ifndef ILL_CORE_CONFIGURATION_HPP
#define ILL_CORE_CONFIGURATION_HPP

#include <Ill/Core/Object.hpp>

namespace Ill
{
    namespace Core
    {
        class CORE_DLL Configuration : public Object
        {
            CLASS(Configuration, Object);
            /**
             * Loads an XML configuration file.
             */
            STATIC_METHOD( CORE_DLL, public, bool, LoadXMLConfiguration, (const std::string& fileName, const std::string& nodeName ) );
            /**
             * Loads an XML configuration file into the default node named "Root".
             */
            STATIC_METHOD( CORE_DLL, public, bool, LoadXMLConfiguration, (const std::string& fileName ) );

            /**
             * Saves the configuration starting with nodeName to an XLM file.
             */
            STATIC_METHOD( CORE_DLL, public, bool, SaveXMLConfiguration, (const std::string& fileName, const std::string& nodeName) );
            /**
             * Saves the default node named "Root" configuration data to an XML file.
             */
            STATIC_METHOD( CORE_DLL, public, bool, SaveXMLConfiguration, (const std::string& fileName) );

            /**
             * Get the configuration node with the name specified.
             */
            STATIC_METHOD( CORE_DLL, public, boost::property_tree::ptree&, GetConfigurationNode, ( const std::string& nodeName ) );
            /**
             * Gets the default configuration node with the name "Root"
             */
            STATIC_METHOD( CORE_DLL, public, boost::property_tree::ptree&, GetRootConfiguration, () );
        };
    }
}

#endif // ILL_CORE_CONFIGURATION_HPP