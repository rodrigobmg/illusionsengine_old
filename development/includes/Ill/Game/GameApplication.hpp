/**
 * @file: GameApplication.h
 * @date: September 22, 2009
 *
 * The game application base class.
 */

#ifndef ILL_GAME_GAMEAPPLICATION_HPP
#define ILL_GAME_GAMEAPPLICATION_HPP

#include <Ill/Core/Application.hpp>
#include <Ill/Game/GameEvents.hpp>
#include <Ill/Game/GameApplication.fwd.hpp>


namespace Ill
{
    namespace Game
    {
		class GAME_DLL GameApplication : public Ill::Core::Application
        {
        public:
            CLASS( GameApplication, Ill::Core::Application );
            CONSTRUCTOR( GAME_DLL, public, GameApplication, () );  

            /**
             * Initialize any memory needed by this component.
             * 
             * @returns true if all memory allocations were successful.
             */
            VIRTUAL_METHOD( GAME_DLL, public, void, Initialize, () );

            /**
 			 * Start up the application subsystem.
			 *
			 * @param options Contains all the startup options that have
			 * been either, parsed from the application config file, or parsed
			 * on the command line.
			 */
            VIRTUAL_METHOD( GAME_DLL, public, bool, StartUp, (const Ill::Core::PropertyMap& startupOptions) );


            /**
			 * Run the application with the options specified application 
			 * options specified in StartUp.
			 */
			VIRTUAL_METHOD( GAME_DLL, public, int, Run, () );

            /**
             * Deallocate the memory that was allocated in Initialize.
             * It should be possible to invoke this method many times
             * without an error or exception being thrown.  This way, 
             * components can be recycled without deleting them.
             * 
             * @returns true if all memory allocations were successful.
             */
            VIRTUAL_METHOD( GAME_DLL, public, void, Terminate, () );

            /**
             * Events supported by the GameApplication class
             */
            // Window events
            Ill::Core::Event            InputFocus;
            Ill::Core::Event            InputBlur;
            Ill::Core::Event            MouseFocus;
            Ill::Core::Event            MouseBlur;
            Ill::Core::Event            Minimize;
            Ill::Core::Event            Restore;
            Ill::Core::ResizeEvent      Resize;
            Ill::Core::Event            Expose;
            Ill::Core::Event            Exit;

            Ill::Core::UpdateEvent      Update;
            Ill::Core::RenderEvent      Render;

            // Keyboard events
            Ill::Game::KeyboardEvent    KeyPressed;
            Ill::Game::KeyboardEvent    KeyReleased;

            // Mouse events
            Ill::Game::MouseMotionEvent MouseMoved;
            Ill::Game::MouseButtonEvent MouseButtonPressed;
            Ill::Game::MouseButtonEvent MouseButtonReleased;

            // User events
            Ill::Core::UserEvent        UserEvent;

        protected:

            // The generic event handler will dispatch events to the proper
            // event handlers
            virtual void EventHandler( SDL_Event& event );

            virtual void OnUpdate( Ill::Core::UpdateEventArgs& e );
            virtual void OnRender( Ill::Core::RenderEventArgs& e );

            // The application window has received focus
            virtual void OnInputFocus( Ill::Core::EventArgs& e );
            // The application window has lost focus
            virtual void OnInputBlur( Ill::Core::EventArgs& e );

            // The application window has received mouse focus
            virtual void OnMouseFocus( Ill::Core::EventArgs& e );
            // The application window has lost mouse focus
            virtual void OnMouseBlur( Ill::Core::EventArgs& e );

            // The application window has been minimized
            virtual void OnMinimize( Ill::Core::EventArgs& e );
            // The application window has been restored
            virtual void OnRestore( Ill::Core::EventArgs& e );

            // A keyboard key was pressed
            virtual void OnKeyPressed( KeyEventArgs& e );
            // A keyboard key was released
            virtual void OnKeyReleased( KeyEventArgs& e );
            // The mouse was moved
            virtual void OnMouseMoved( MouseMotionEventArgs& e );
            // A button on the mouse was pressed
            virtual void OnMouseButtonPressed( MouseButtonEventArgs& e );
            // A button on the mouse was released
            virtual void OnMouseButtonReleased( MouseButtonEventArgs& e );

            // The application window has be resized
            virtual void OnResize( Ill::Core::ResizeEventArgs& e );
            // The window contents should be repainted
            virtual void OnExpose( Ill::Core::EventArgs& e );

            // The user requested to exit the application
            virtual void OnExit( Ill::Core::EventArgs& e );

            // A user event was generated in the SDL message queue.
            virtual void OnUserEvent( Ill::Core::UserEventArgs& e );

        private:
            bool m_bIsRunning;

            // Accumulated timer for application time.
            float           m_fTotalTime;
       };
    }
}

#endif // ILL_GAME_GAMEAPPLICATION_HPP