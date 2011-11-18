#include <MyGamePCH.hpp>
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
    Ill::Core::InstantiateTypes();
    Ill::Graphics::InstantiateTypes();
    Ill::Game::InstantiateTypes();
}

void OnKeyPressed( Ill::Graphics::KeyEventArgs& e );

// Globals
Ill::Game::GameApplicationPtr g_pGameApp;

int main( int argc, char* argv[] )
{
    InstantiateTypes();

    // A property map to store the game options.
    Ill::Core::PropertyMap gameOptions;

#ifdef ILL_DEBUG
    gameOptions.AddValue( "PluginFilename", std::wstring(L"../Configuration/Plugins_Debug.cfg") );
    gameOptions.AddValue( "GraphicsLibName", std::wstring(L"Ill.OgrePlugin_d.dll") );
#else
    gameOptions.AddValue( "PluginFilename", std::wstring(L"../Configuration/Plugins.cfg") );
    gameOptions.AddValue( "GraphicsLibName", std::wstring(L"Ill.OgrePlugin.dll") );
#endif

    gameOptions.AddValue( "ConfigFilename", std::wstring(L"../Configuration/ogre.cfg") );
    gameOptions.AddValue( "ResourceFilename", std::wstring(L"../Configuration/resources.cfg") );
    gameOptions.AddValue( "LogFilename", std::wstring(L"../Logs/Ogre.log") );
    gameOptions.AddValue( "DefaultSceneInstanceName", std::wstring(L"MyGameSceneInstance") );


    // Create the game application class
    g_pGameApp = boost::make_shared<Ill::Game::GameApplication>(); // Ill::Game::GameApplicationPtr( new Ill::Game::GameApplication() );

    // Register the event handlers.
    g_pGameApp->KeyPressed += &OnKeyPressed;

    g_pGameApp->Initialize();

    // Parse the command-line options
    g_pGameApp->ParseConfigurations( argc, argv, gameOptions );

    // Register subsystems
    const Class* pGrapicsSubsystemClass = Class::forName( "class Ill::Graphics::GrapicsSubsystem" );
    BOOST_ASSERT( pGrapicsSubsystemClass != NULL && "Could not find GraphicsSubsystem class in class registry.");

    g_pGameApp->RegisterSubsystem( *pGrapicsSubsystemClass );

    if ( g_pGameApp->StartUp( gameOptions ) )
	{
		// Kick-off the game application
		g_pGameApp->Run();
	}
	else
	{
		std::cerr << "The application failed to start... Shutting down." << std::endl;
	}

#ifdef _DEBUG
    // Run a small test to see what classes the reflection system knows about.
    TestReflection();
#endif
    
    g_pGameApp->Shutdown();
    g_pGameApp->Terminate();
    g_pGameApp.reset();

#ifdef _DEBUG
    // Run a small test to see what classes the reflection system knows about.
    TestReflection();
#endif

    return 0;
}

void OnKeyPressed( Ill::Graphics::KeyEventArgs& e )
{
    if ( e.Key == SDLK_ESCAPE )
    {
        // Stop the application
        g_pGameApp->Stop();
    }
}