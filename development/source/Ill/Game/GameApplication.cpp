/**
 * @file: GameApplication.cpp
 * @date: September 22, 2009
 *
 * GameApplication base class.
 */

#include <Ill/Game/GamePCH.hpp>

#include <Ill/Graphics/GraphicsWindow.hpp>

#include <Ill/Game/ElapsedTime.hpp>
#include <Ill/Game/GameApplication.hpp>

namespace Ill
{
    namespace Game
    {
        GameApplication::GameApplication()
            : m_bIsRunning( false )
            , m_fTotalTime( 0.0f )
        {
        }

        void GameApplication::Initialize()
        {
            Super::Initialize();
        }

        bool GameApplication::StartUp(const boost::property_tree::ptree& startupOptions)
        {
            // For now, the default window description should do.
            Ill::Graphics::GraphicsWindow::WindowDescription windowDescription;

            std::string windowClassName = startupOptions.get<std::string>("WindowClass");
            const Class* windowClass = Class::forName(windowClassName);
            BOOST_ASSERT_MSG( windowClass != NULL, "Could not find window class");

            m_pRenderWindow = boost::shared_ptr<Ill::Graphics::GraphicsWindow>( (Ill::Graphics::GraphicsWindow*)windowClass->newInstance() );
            BOOST_ASSERT_MSG( m_pRenderWindow, ("Could not create window instance") );

            m_pRenderWindow->Initialize();

            // Window events
            m_pRenderWindow->InputFocus += boost::bind( &GameApplication::OnInputFocus, this, _1 );
            m_pRenderWindow->InputBlur += boost::bind( &GameApplication::OnInputBlur, this, _1 );
            m_pRenderWindow->MouseFocus += boost::bind( &GameApplication::OnMouseFocus, this, _1 );
            m_pRenderWindow->MouseBlur += boost::bind( &GameApplication::OnMouseBlur, this, _1 );
            m_pRenderWindow->Minimize += boost::bind( &GameApplication::OnMinimize, this, _1 );
            m_pRenderWindow->Restore += boost::bind( &GameApplication::OnRestore, this, _1 );
            m_pRenderWindow->Resize += boost::bind( &GameApplication::OnResize, this, _1 );
            m_pRenderWindow->Expose += boost::bind( &GameApplication::OnExpose, this, _1 );
            m_pRenderWindow->Exit += boost::bind( &GameApplication::OnExit, this, _1 );

            // Keyboard events
            m_pRenderWindow->KeyPressed += boost::bind( &GameApplication::OnKeyPressed, this, _1 );
            m_pRenderWindow->KeyReleased += boost::bind( &GameApplication::OnKeyReleased, this, _1 );

            // Mouse events
            m_pRenderWindow->MouseMoved += boost::bind( &GameApplication::OnMouseMoved, this, _1 );
            m_pRenderWindow->MouseButtonPressed += boost::bind( &GameApplication::OnMouseButtonPressed, this, _1 );
            m_pRenderWindow->MouseButtonReleased += boost::bind( &GameApplication::OnMouseButtonReleased, this, _1 );

            // User events
            m_pRenderWindow->UserEvent += boost::bind( &GameApplication::OnUserEvent, this, _1 );            

            // Create the render window. This will also create the OpenGL context
            // and associate it with this window.
            windowDescription.Width = startupOptions.get("WindowDescription.Width", 800 );
            windowDescription.Height= startupOptions.get("WindowDescription.Height", 600 );
            windowDescription.Fullscreen = startupOptions.get("WindowDescription.Fullscreen", false );

            bool bSuccess = m_pRenderWindow->CreateWindow( windowDescription );

            return bSuccess && Super::StartUp( startupOptions );
        }

        int GameApplication::Run()
        {
            static ElapsedTime elapsedTime;

            m_bIsRunning = true;

            while ( m_bIsRunning )
            {
                // Allow the render window to process the event queue.
                // The appropriate event handlers in the application 
                // class should be called when the specified events occur.
                m_pRenderWindow->ProcessEvents();

                float fDeltaTime = elapsedTime.GetElapsedTime();

                m_fTotalTime += fDeltaTime;

                Ill::Core::UpdateEventArgs updateArgs( *this, fDeltaTime, m_fTotalTime );
                Ill::Core::RenderEventArgs renderArgs( *this, fDeltaTime, m_fTotalTime );

                OnUpdate( updateArgs );
                OnRender( renderArgs );
            }

            Terminate();

            return 0;
        }

        void GameApplication::Stop()
        {
            Super::Stop();
            // Closing the window will cause the OnExit event handler to be invoked
            // at the right time.
            m_pRenderWindow->CloseWindow();
        }

        void GameApplication::Terminate()
        {
            // Destroying the window will actually clean-up the memory allocated
            // by the window object.
            m_pRenderWindow->DestroyWindow();
            // Terminating the window will cause the windowing subsystem
            // to be terminated.
            m_pRenderWindow->Terminate();

            Super::Terminate();
        }

        void GameApplication::OnUpdate( Ill::Core::UpdateEventArgs& e )
        {
            // Invoke the update event for listeners to 
            // perform game logic.
            Update( e );    
        }

        void GameApplication::OnRender( Ill::Core::RenderEventArgs& e )
        {
            // Invoke the render event for listeners to render
            // the game scene.
            Render( e );
        }

        // The application window has received focus
        void GameApplication::OnInputFocus( Ill::Core::EventArgs& e )
        {
            InputFocus( e );
        }

        // The application window has lost focus
        void GameApplication::OnInputBlur( Ill::Core::EventArgs& e )
        {
            InputBlur( e );
        }

        // The application window has received mouse focus
        void GameApplication::OnMouseFocus( Ill::Core::EventArgs& e )
        {
            MouseFocus( e );
        }

        // The application window has lost mouse focus
        void GameApplication::OnMouseBlur( Ill::Core::EventArgs& e )
        {
            MouseBlur( e );
        }

        // A keyboard key was pressed
        void GameApplication::OnKeyPressed( Ill::Graphics::KeyEventArgs& e )
        {
            KeyPressed( e );
        }

        // A keyboard key was released
        void GameApplication::OnKeyReleased( Ill::Graphics::KeyEventArgs& e )
        {
            KeyReleased( e );
        }

        // The mouse was moved
        void GameApplication::OnMouseMoved( Ill::Graphics::MouseMotionEventArgs& e )
        {
            MouseMoved( e );
        }

        // A button on the mouse was pressed
        void GameApplication::OnMouseButtonPressed( Ill::Graphics::MouseButtonEventArgs& e )
        {
            MouseButtonPressed( e );
        }

        // A button on the mouse was released
        void GameApplication::OnMouseButtonReleased( Ill::Graphics::MouseButtonEventArgs& e )
        {
            MouseButtonReleased( e );
        }

        // The application window has been minimized
        void GameApplication::OnMinimize( Ill::Core::EventArgs& e )
        {
            Minimize( e );
        }

        // The application window has been restored
        void GameApplication::OnRestore( Ill::Core::EventArgs& e )
        {
            Restore( e );
        }

        // The application window has be resized
        void GameApplication::OnResize( Ill::Core::ResizeEventArgs& e )
        {
            Resize( e );
        }

        // The window contents should be repainted
        void GameApplication::OnExpose( Ill::Core::EventArgs& e )
        {
            Expose( e );
        }

        // The user requested to exit the application
        void GameApplication::OnExit( Ill::Core::EventArgs& e )
        {
            Exit( e );

            // Setting this to false will cause the main application window
            // to close
            m_bIsRunning = false;
        }

        // A user event was generated
        void GameApplication::OnUserEvent( Ill::Core::UserEventArgs& e )
        {
            UserEvent( e );
        }
    }
}