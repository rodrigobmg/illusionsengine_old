#include <PrecompiledHeader.hpp>
#include <SDL_main.h>

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

// Typedefs
typedef Ill::System::String String;

int main( int argc, char* argv[] )
{
    InstantiateTypes();

#ifdef _DEBUG
    // Run a small test to see what classes the reflection system knows about.
    TestReflection();
#endif

    // A property map to store the game options.
    Ill::System::PropertyMap gameOptions;

#ifdef _DEBUG
    gameOptions.AddValue( "PluginFilename", String( TEXT("../Configuration/Plugins_Debug.cfg") ) );
    gameOptions.AddValue( "GraphicsLibName", String( TEXT("Ill.System.OgreGraphics_d.dll") ) );
#else
    gameOptions.AddValue( "PluginFilename", String( TEXT("../Configuration/Plugins.cfg") ) );
    gameOptions.AddValue( "GraphicsLibName", String( TEXT("Ill.System.OgreGraphics.dll") ) );
#endif

    gameOptions.AddValue( "ConfigFilename", String( TEXT("../Configuration/ogre.cfg") ) );
    gameOptions.AddValue( "ResourceFilename", String( TEXT("../Configuration/resources.cfg") ) );
    gameOptions.AddValue( "LogFilename", String( TEXT("../Logs/Ogre.log") ) );
    gameOptions.AddValue( "DefaultSceneInstanceName", String( TEXT("MyGameSceneInstance") ) );


    // Create the game application class
    g_pGameApp = new Ill::Game::GameApplication();

    // Parse the command-line options
    g_pGameApp->ParseConfigurations( argc, argv, gameOptions );

    // Register subsystems
    g_pGameApp->RegisterSubsystem( Class::forName( "class Ill::System::DynamicLibSubsystem") );
    g_pGameApp->RegisterSubsystem( Class::forName( "class Ill::System::Graphics::GrapicsSubsystem" ) );

    if ( g_pGameApp->StartUp( gameOptions ) )
	{
		// Kick-off the game application
		g_pGameApp->Run();
	}
	else
	{
		std::cerr << "The application failed to start... Shutting down." << std::endl;
	}
    
    g_pGameApp->Shutdown();

    g_pGameApp = NULL;

    return 0;
}
