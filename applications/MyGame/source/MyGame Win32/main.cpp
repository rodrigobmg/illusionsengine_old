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

int main( int argc, char* argv[] )
{
    InstantiateTypes();

    std::string configFile = "../Configuration/DefaultConfiguration.xml";
    if ( !Ill::Core::Configuration::LoadXMLConfiguration( configFile ) )
    {
        std::cerr << "Failed to load configuration file from \"" << configFile << "\"" << std::endl;
        return -1;
    }

    boost::property_tree::ptree& configurationData = Ill::Core::Configuration::GetRootConfiguration();

    // Create the game application class
    std::string applicationClassName = configurationData.get( "default.ApplicationClass", "Ill::Game::GameApplication" );
    const Class* applicationClass = Class::forName(applicationClassName);

    BOOST_ASSERT( applicationClass != NULL && "Failed to load Application class" );
    g_pApplication = Ill::Game::GameApplicationPtr( (Ill::Game::GameApplication*)applicationClass->newInstance() );

    // Load plug-ins
#if ILL_DEBUG
    std::string pluginsConfigurationNodeName = "debug.Plugins";
#else
    std::string pluginsConfigurationNodeName = "release.Plugins";
#endif 

    foreach( boost::property_tree::ptree::value_type& pluginName, configurationData.get_child(pluginsConfigurationNodeName) )
    {
        fs::path pluginPath( pluginName.second.data() );
        g_pApplication->LoadPlugin( pluginPath.wstring() );
    }

    g_pApplication->Initialize();

    // Register the event handlers.
    g_pApplication->KeyPressed += &OnKeyPressed;
    
    // Kick-off the game application
	int returnValue = g_pApplication->Run();
    
    g_pApplication->Terminate();
    g_pApplication.reset();

    return returnValue;
}

void OnKeyPressed( Ill::Graphics::KeyEventArgs& e )
{
    if ( e.Key == SDLK_ESCAPE )
    {
        // Stop the application
        g_pApplication->Stop();
    }
}
