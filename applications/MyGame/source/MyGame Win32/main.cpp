#include <MyGamePCH.hpp>
#include <SDL_main.h>

// Include the game library.
#include <Ill/Game/Game.hpp>

// We have to do this somewhere in our exec to ensure the 
// reflection library can register it's types.
void InstantiateTypes()
{
    Ill::Core::InstantiateTypes();
    Ill::Graphics::InstantiateTypes();
    Ill::Game::InstantiateTypes();
}

// Globals
Ill::Game::GameApplicationPtr g_pApplication;

void OnKeyPressed( Ill::Graphics::KeyEventArgs& e );
bool LoadXMLConfiguration( const std::string& fileName, boost::property_tree::ptree& propertyTree );
void SaveXMLConfiguration( const std::string& fileName, const boost::property_tree::ptree& propertyTree );

int main( int argc, char* argv[] )
{
    InstantiateTypes();

    // A property tree to store the game configuration.
    boost::property_tree::ptree gameConfiguration;
    std::string configFile = "../Configuration/configuration.xml";

    LoadXMLConfiguration( configFile, gameConfiguration );

    // TODO: Parse command-line options that should override (or add) configuration options.

    // Create the game application class
    std::string applicationClassName = gameConfiguration.get( "MyGame.ApplicationClass", "Ill::Game::GameApplication" );
    const Class* applicationClass = Class::forName(applicationClassName);

    BOOST_ASSERT( applicationClass != NULL && "Failed to load Application class" );
    g_pApplication = boost::shared_ptr<Ill::Game::GameApplication>( (Ill::Game::GameApplication*)applicationClass->newInstance() );

    g_pApplication->Initialize();

    // Load plug-ins
#if ILL_DEBUG
    std::string pluginsConfigurationNodeName = "MyGameDebug.Plugins";
#else
    std::string pluginsConfigurationNodeName = "MyGameRelease.Plugins";
#endif 

    foreach( boost::property_tree::ptree::value_type& pluginName, gameConfiguration.get_child(pluginsConfigurationNodeName) )
    {
        fs::path pluginPath( pluginName.second.data() );
        g_pApplication->LoadPlugin( pluginPath.wstring() );
    }

    // Register the event handlers.
    g_pApplication->KeyPressed += &OnKeyPressed;
    
    boost::property_tree::ptree applicationConfiguration = gameConfiguration.get_child("MyGame.GameApplication");
    g_pApplication->Initialize();
    if ( g_pApplication->StartUp( applicationConfiguration ) )
	{
		// Kick-off the game application
		g_pApplication->Run();
	}
	else
	{
		std::cerr << "The application failed to start... Shutting down." << std::endl;
	}
    
    g_pApplication->Shutdown();
    g_pApplication->Terminate();
    g_pApplication.reset();

    return 0;
}

void OnKeyPressed( Ill::Graphics::KeyEventArgs& e )
{
    if ( e.Key == SDLK_ESCAPE )
    {
        // Stop the application
        g_pApplication->Stop();
    }
}

bool LoadXMLConfiguration( const std::string& fileName, boost::property_tree::ptree& propertyTree )
{
    boost::property_tree::read_xml( fileName, propertyTree );
    return true;
}

void SaveXMLConfiguration( const std::string& fileName, const boost::property_tree::ptree& propertyTree )
{
    boost::property_tree::write_xml( fileName, propertyTree );
}