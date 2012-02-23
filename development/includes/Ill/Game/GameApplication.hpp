/**
 * @file: GameApplication.h
 * @date: September 22, 2009
 *
 * The game application base class.
 */

#ifndef ILL_GAME_GAMEAPPLICATION_HPP
#define ILL_GAME_GAMEAPPLICATION_HPP

#include <Ill/Core/Application.hpp>
#include <Ill/Graphics/GraphicsWindow.fwd.hpp>
#include <Ill/Graphics/WindowEvents.hpp>

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
			 * Run the application with the options specified application 
			 * options specified in StartUp.
			 */
			VIRTUAL_METHOD( GAME_DLL, public, int, Run, () );

            /**
             * Request that the application should stop running.
             * This will add an event on the event queue that will invoke
             * the Exit event from the GraphicsWindow. We can handle the @see(OnExit)
             * method to set the running flag to false to break out of the Run loop.
             *
             * @see(OnExit)
             */
            VIRTUAL_METHOD( GAME_DLL, public, void, Stop, () );

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
            // Application specific events
            Ill::Core::UpdateEvent      Update;
            Ill::Core::RenderEvent      Render;

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

            // Keyboard events
            Ill::Graphics::KeyboardEvent    KeyPressed;
            Ill::Graphics::KeyboardEvent    KeyReleased;

            // Mouse events
            Ill::Graphics::MouseMotionEvent MouseMoved;
            Ill::Graphics::MouseButtonEvent MouseButtonPressed;
            Ill::Graphics::MouseButtonEvent MouseButtonReleased;

            // User events
            Ill::Core::UserEvent        UserEvent;

        protected:

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
            virtual void OnKeyPressed( Ill::Graphics::KeyEventArgs& e );
            // A keyboard key was released
            virtual void OnKeyReleased( Ill::Graphics::KeyEventArgs& e );
            // The mouse was moved
            virtual void OnMouseMoved( Ill::Graphics::MouseMotionEventArgs& e );
            // A button on the mouse was pressed
            virtual void OnMouseButtonPressed( Ill::Graphics::MouseButtonEventArgs& e );
            // A button on the mouse was released
            virtual void OnMouseButtonReleased( Ill::Graphics::MouseButtonEventArgs& e );

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

            // A handle to the window that will be rendered to..
            Ill::Graphics::GraphicsWindowPtr m_pRenderWindow;
       };
    }
}

#endif // ILL_GAME_GAMEAPPLICATION_HPP