#ifndef ILL_GRAPHICS_GRAPHICSWINDOW_HPP
#define ILL_GRAPHICS_GRAPHICSWINDOW_HPP

#include <Ill/Core/Object.hpp>
#include <Ill/Graphics/WindowEvents.hpp>
#include <Ill/Graphics/GraphicsWindow.fwd.hpp>

// The windows CreateWindow macro causes issues for my own 
// CreateWindow function (even though the scopes are different..)
#ifdef CreateWindow
#undef CreateWindow
#endif

namespace Ill
{
    namespace Graphics
    {
        class GraphicsWindowImpl;

        class GRAPHICS_DLL GraphicsWindow : public Ill::Core::Object
        {
        public:

            class WindowDescription
            {
            public:
                int     Width;
                int     Height;
                bool    Fullscreen;

                // Color buffer settings
                int     NumRedBits;
                int     NumGreenBits;
                int     NumBlueBits;
                int     NumAlphaBits;

                // Frame buffer settings
                int     NumDepthBits;
                int     NumBufferBits;

                // Accumulation buffer settings
                int     NumAccumRedBits;
                int     NumAccumGreenBits;
                int     NumAccumBlueBits;
                int     NumAccumAlphaBits;

                // Multisample anti-aliasing settings
                int     NumMultiSampleBuffers;
                int     NumMultiSamples;

                WindowDescription()
                    : Width( 1280 )
                    , Height( 720 )
                    , Fullscreen( false )
                    , NumRedBits( 8 )
                    , NumGreenBits( 8 )
                    , NumBlueBits( 8 )
                    , NumAlphaBits( 8 )
                    , NumDepthBits( 16 )
                    , NumBufferBits( 32 )
                    , NumAccumRedBits( 8 )
                    , NumAccumGreenBits( 8 )
                    , NumAccumBlueBits( 8 )
                    , NumAccumAlphaBits( 8 )
                    , NumMultiSampleBuffers( 1 )
                    , NumMultiSamples( 2 )
                {}
            };

            CLASS( GraphicsWindow, Ill::Core::Object );
            CONSTRUCTOR( GRAPHICS_DLL, public, GraphicsWindow, () );
        
            /**
             * Initialize the window subsystem.  This must be called before a 
             * window can be created.
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, bool, Initialize, () );

            /**
             * Terminate the window subsystem.
             *
             * @precondition The window system has previous been initialized.
             * @postcondition The window system is shut down.
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, void, Terminate, () );

            /**
             * Set an icon for the window.  This should be called 
             * before the window is created.  The window will be created
             * with the specified icon.
             * By default, the magenta (red:255, green:0, blue:255) pixels of the icon
             * will be made transparent.
             * On Windows, you can best use 32x32 size icons.
             *
             * @param iconImage The file path to the image icon to load.
             * On windows, the icon image should be a 32x32 bitmap image.
             *
             * @precondition The video subsystem is initialized. @see(Initialize).
             * @postcondition The specified window icon will be used when the window
             * is created @see(CreateWindow).
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, void, SetIcon, ( const std::string& iconImage ) );

                        /**
             * Set the text that appears in the window title and the iconified window title.
             * This should be called before the window is created.  The window will be created 
             * with the specified window and iconified window titles. @see(CreateWindow).
             * 
             * @param windowTitle The title text (the text that appears on the top of the window).
             * @param iconifiedWindowTitle The inconified window title (the text that appears in the
             * task bar when the window is minimized).
             *
             * @precondition The video subsystem is initialized @see(Initialize).
             * @postcondition The caption for
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, void, SetCaption, ( const std::string& windowTitle, const std::string& iconifiedWindowTitle ) );

            /**
             * Create a window that can be used to display OpenGL graphics onto.
             * Currently, it is not possible to create multiple windows.  Multi-window
             * support might become available when SDL 1.3 gets stable enough to 
             * use.
             * 
             * @param windowDescription A structure that defines the window attributes.
             *
             * @precondition GraphicsWindowImpl::IsInitialized returns true.
             * @postcondition A window is created and displayed to the user
             *
             * @see(WindowDescription)
             * @see(Initialize)
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, bool, CreateWindow, (const WindowDescription& windowDescription) );

            /**
             * Close the window that was created with @see(CreateWindow).  Calling this method
             * will cause a quite event to be added to the event queue.  This allows the message
             * procesor to continue to process events until it is convienient to close the window.
             *
             * @precondition A window was created with @see(CreateWindow)
             * @postcondition An event will be put on the event queue that will cause the 
             * application to exit.
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, void, CloseWindow, () );

            /**
             * Attempt to toggle the window from windowed to full screen mode.
             * This function is currently not supported on all platforms.
             *
             * @precondition The window must have already been created.
             * @postcondition The window will switch from windowed to full-screen
             * or full-screen to windowed mode.
             *
             * @returns true if the window was toggled fullscreen. False if the
             * fullscreen mode could not be modified.
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, bool, ToggleFullScreen, () );

            /**
             * Process all of the events in the event queue. 
             * Classes should register for the events that it 
             * is interested in handling - The window class does not handle 
             * events directly.
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, void, ProcessEvents, () );

            /**
             * Destroy the window that was created with CreateWindow.
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, void, DestroyWindow, () );

            // Getters & Setters
            METHOD( GRAPHICS_DLL, public, bool, IsInitialized, () );
            METHOD( GRAPHICS_DLL, public, uint32, GetWindowWidth, () );
            METHOD( GRAPHICS_DLL, public, uint32, GetWindowHeight, () );

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
            Ill::Core::UserEvent            UserEvent;


        protected:

            // The  window has received focus.
            virtual void OnInputFocus( Ill::Core::EventArgs& e );
            // The window has lost focus
            virtual void OnInputBlur( Ill::Core::EventArgs& e );

            // The window has received mouse focus.
            virtual void OnMouseFocus( Ill::Core::EventArgs& e );
            // The window has lost mouse focus.
            virtual void OnMouseBlur( Ill::Core::EventArgs& e );

            // The window has been minimized.
            virtual void OnMinimize( Ill::Core::EventArgs& e );
            // The application window has been restored.
            virtual void OnRestore( Ill::Core::EventArgs& e );

            // A keyboard key was pressed.
            virtual void OnKeyPressed( KeyEventArgs& e );
            // A keyboard key was released.
            virtual void OnKeyReleased( KeyEventArgs& e );
            // The mouse was moved.
            virtual void OnMouseMoved( MouseMotionEventArgs& e );
            // A button on the mouse was pressed.
            virtual void OnMouseButtonPressed( MouseButtonEventArgs& e );
            // A button on the mouse was released.
            virtual void OnMouseButtonReleased( MouseButtonEventArgs& e );

            // The window has been resized.
            virtual void OnResize( Ill::Core::ResizeEventArgs& e );
            // The window contents should be repainted.
            virtual void OnExpose( Ill::Core::EventArgs& e );

            // The user requested to exit the application.
            virtual void OnExit( Ill::Core::EventArgs& e );

            // User event was added to the event queue.
            virtual void OnUserEvent( Ill::Core::UserEventArgs& e );

        private:
            boost::shared_ptr< GraphicsWindowImpl > m_pImplementation;
        };
    }
}

#endif // ILL_GRAPHICS_GRAPHICSWINDOW_HPP