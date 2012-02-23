#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/Configuration.hpp>

using boost::property_tree::ptree;

static ptree g_RootConfiguration;
// The empty configuration is returned when an error occurs.
static ptree g_EmptyConfiguration;

namespace Ill
{
    namespace Core
    {
        bool Configuration::LoadXMLConfiguration( const std::string& fileName, const std::string& nodeName )
        {
           try
           {
               ptree properties;
               read_xml( fileName, properties );

               g_RootConfiguration.insert(g_RootConfiguration.end(), ptree::value_type(nodeName, properties) );
               return true;
           }
           catch ( std::exception& )
           {
               std::cerr << "An error occurred while trying to load the configuration file: \"" << fileName << "\"" << std::endl;
           }

           return false;
        }

        bool Configuration::LoadXMLConfiguration( const std::string& fileName )
        {
            return LoadXMLConfiguration( fileName, "Root" );
        }

        bool SaveXMLConfigurationData( const std::string& fileName, ptree& pt )
        {
            try 
            {
                write_xml( fileName, pt );
                return true;
            }
            catch ( std::exception& )
            {
                std::cerr << "An error occurred while trying to save the configuration file: \"" << fileName << "\"" << std::endl;
            }

            return false;

        }

        bool Configuration::SaveXMLConfiguration( const std::string& fileName, const std::string& nodeName )
        {
            ptree& configurationNode = GetConfigurationNode( nodeName );
            if ( &configurationNode != &g_EmptyConfiguration )
            {
                return SaveXMLConfigurationData( fileName, configurationNode );
            }

            return false;
        }

        bool Configuration::SaveXMLConfiguration( const std::string& fileName )
        {
            return SaveXMLConfiguration( fileName, "Root" );
        }

        ptree& Configuration::GetConfigurationNode( const std::string& nodeName )
        {
            try 
            {
                return g_RootConfiguration.get_child(nodeName);
            }
            catch ( std::exception& )
            {
                std::cerr << "Could not find node with name \"" << nodeName << "\" in configuration data." << std::endl;
            }
            return g_EmptyConfiguration;
        }

        ptree& Configuration::GetRootConfiguration()
        {
            return GetConfigurationNode("Root");
        }
    }
}