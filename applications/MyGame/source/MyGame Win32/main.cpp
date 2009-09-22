#include <PrecompiledHeader.hpp>
#include <SDL.h>

// Include the game library.
#include <Ill/Game/Game.hpp>

#ifdef _DEBUG
// Testing code..
#include <TestReflection.h>
#endif

// We have to do this somewhere in our exec to ensure the 
// reflection library can register it's types.
void InstantiateTypes()
{
    Ill::System::InstantiateTypes();
    Ill::System::Graphics::InstantiateTypes();
}

// Gloabals
Ill::Game::GameApplicationPtr g_pGameApp;

int main( int argc, char* argv[] )
{
    InstantiateTypes();

#ifdef _DEBUG
    // Run a small test to see what classes the reflection system knows about.
    TestReflection();
#endif

    // A property map to store the game options.
    Ill::System::PropertyMap gameOptions;

    gameOptions.AddValue( "PluginFilename", std::string("plugins.cfg") );
    gameOptions.AddValue( "ConfigFilename", std::string("ogre.cfg") );
    gameOptions.AddValue( "LogFilename", std::string("Ogre.log") );

    // Create the game application class
    g_pGameApp = new Ill::Game::GameApplication();

    // Parse the command-line options
    g_pGameApp->ParseConfigurations( argc, argv, gameOptions );

    // Register subsystems
    g_pGameApp->RegisterSubsystem( Class::forName( "class Ill::System::Graphics::GrapicsSubsystem" ) );

    g_pGameApp->StartUp( gameOptions );

    // Kick-off the game application
    g_pGameApp->Run();
    
    g_pGameApp->Shutdown();

    g_pGameApp = NULL;

    return 0;
}
