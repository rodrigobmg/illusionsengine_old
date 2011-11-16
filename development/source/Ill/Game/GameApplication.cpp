/**
 * @file: GameApplication.cpp
 * @date: September 22, 2009
 *
 * GameApplication base class.
 */

#include <Ill/Game/GamePCH.hpp>
#include <Ill/Game/ElapsedTime.hpp>
#include <Ill/Game/GameApplication.hpp>

namespace Ill
{
    namespace Game
    {
        GameApplication::GameApplication()
            : m_bIsRunning( false )
            , m_fTotalTime( 0.0f )
        {}

        void GameApplication::Initialize()
        {
            Super::Initialize();
        }

        bool GameApplication::StartUp(const Ill::Core::PropertyMap& startupOptions)
        {
            bool bSuccess = Super::StartUp( startupOptions );
            if ( bSuccess )
            {
                
            }
            return true;
        }

        int GameApplication::Run()
        {

            static ElapsedTime elapsedTime;

            SDL_Event event;
            m_bIsRunning = true;

            while ( m_bIsRunning )
            {
                while ( SDL_PollEvent(&event) )
                {
                    EventHandler( event );
                }

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


        void GameApplication::Terminate()
        {
            Super::Terminate();
        }

        void GameApplication::EventHandler( SDL_Event& event )
        {
            switch ( event.type )
            {
            case SDL_ACTIVEEVENT:
                {
                    Ill::Core::EventArgs activeEventArgs(*this);
                    switch ( event.active.state )
                    {
                    case SDL_APPMOUSEFOCUS:
                        {
                            if ( event.active.gain > 0 )
                            {
                                OnMouseFocus( activeEventArgs );
                            }
                            else
                            {
                                OnMouseBlur( activeEventArgs );
                            }
                        }
                        break;
                    case SDL_APPINPUTFOCUS:
                        {
                            if ( event.active.gain > 0 )
                            {
                                OnInputFocus( activeEventArgs );
                            }
                            else 
                            {
                                OnInputBlur( activeEventArgs );
                            }
                        }
                        break;
                    case SDL_APPACTIVE:
                        {
                            if ( event.active.gain > 0 )
                            {
                                OnRestore( activeEventArgs );
                            }
                            else
                            {
                                OnMinimize( activeEventArgs );
                            }
                        }
                        break;
                    }
                }
                break; // SDL_ACTIVEEVENT
            case SDL_KEYDOWN:
                {
                    KeyEventArgs keyEventArgs( *this, event.key.keysym.sym, event.key.keysym.mod, event.key.state, event.key.keysym.unicode );
                    OnKeyPressed( keyEventArgs );
                }
                break;
            case SDL_KEYUP:
                {
                    KeyEventArgs keyEventArgs( *this, event.key.keysym.sym, event.key.keysym.mod, event.key.state, event.key.keysym.unicode );
                    OnKeyReleased( keyEventArgs );
                }
                break;
            case SDL_MOUSEMOTION:
                {
                    MouseMotionEventArgs mouseMotionEventArgs( *this, event.motion.state, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel );
                    OnMouseMoved( mouseMotionEventArgs );
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    MouseButtonEventArgs mouseButtonEventArgs( *this, event.button.button, event.button.state, event.button.x, event.button.y );
                    OnMouseButtonPressed( mouseButtonEventArgs );
                }
                break;
            case SDL_MOUSEBUTTONUP:
                {
                    MouseButtonEventArgs mouseButtonEventArgs( *this, event.button.button, event.button.state, event.button.x, event.button.y );
                    OnMouseButtonReleased( mouseButtonEventArgs );
                }
                break;
            case SDL_VIDEORESIZE:
                {
                    Ill::Core::ResizeEventArgs resizeEventArgs( *this, event.resize.w, event.resize.h );
                    OnResize( resizeEventArgs );
                }
                break;
            case SDL_VIDEOEXPOSE:
                {
                    Ill::Core::EventArgs exposeEventArgs( *this );
                    OnExpose( exposeEventArgs );
                }
                break;
            case SDL_QUIT:
                {
                    Ill::Core::EventArgs quitEventArgs( *this );
                    OnExit( quitEventArgs );
                }
                break;
            default:
                {
                    Ill::Core::UserEventArgs userEventArgs( *this, event.user.code, event.user.data1, event.user.data2 );
                    OnUserEvent( userEventArgs );
                }
                break;
            }
        }

        void GameApplication::OnUpdate( Ill::Core::UpdateEventArgs& e )
        {
            Update( e );    
        }

        void GameApplication::OnRender( Ill::Core::RenderEventArgs& e )
        {
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
        void GameApplication::OnKeyPressed( KeyEventArgs& e )
        {
            KeyPressed( e );
        }

        // A keyboard key was released
        void GameApplication::OnKeyReleased( KeyEventArgs& e )
        {
            KeyReleased( e );
        }

        // The mouse was moved
        void GameApplication::OnMouseMoved( MouseMotionEventArgs& e )
        {
            MouseMoved( e );
        }

        // A button on the mouse was pressed
        void GameApplication::OnMouseButtonPressed( MouseButtonEventArgs& e )
        {
            MouseButtonPressed( e );
        }

        // A button on the mouse was released
        void GameApplication::OnMouseButtonReleased( MouseButtonEventArgs& e )
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