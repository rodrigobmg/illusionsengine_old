#include <Ill/Graphics/GraphicsPCH.hpp>
#include "GraphicsWindowImpl.hpp"

namespace Ill
{
    namespace Graphics
    {
        GraphicsWindowImpl::GraphicsWindowImpl()
            : m_bIsInitialized(false)
            , m_pSurface(NULL)
            , m_pIconImage(NULL)
        {}

        bool GraphicsWindowImpl::Initialize()
        {
            if ( !m_bIsInitialized && SDL_Init(SDL_INIT_VIDEO) < 0 )
            {
                std::cerr << "GraphicsWindowImpl::Initialize: SDL_Init failed (is the video subsystem already initialized?)" << std::endl;
                const char* sdlError = SDL_GetError();
                std::cerr << "SDL ERROR: " << sdlError << std::endl;

                return false;
            }

            m_bIsInitialized = true;
            return true;
        }

        void GraphicsWindowImpl::SetIcon( const std::string& iconImage )
        {
            assert( m_bIsInitialized && "The window is not initialized. First call GraphicsWindowImpl::Initialize()." );

            m_pIconImage = SDL_LoadBMP( iconImage.c_str() );
            if ( m_pIconImage != NULL )
            {
                Uint32 colorKey;

                // TODO: Allow the user to specify the color for the transparency of the window icon.
                // For now use Magenta as the transparency color.
                colorKey = SDL_MapRGB(m_pIconImage->format, 255, 0, 255 );
                SDL_SetColorKey( m_pIconImage, SDL_SRCCOLORKEY, colorKey );

                SDL_WM_SetIcon( m_pIconImage, NULL );
            }
            else
            {
                std::cerr << "Failed to set window icon with image: \"" << iconImage << "\"" << std::endl;
                const char* errorString = SDL_GetError();
                std::cerr << "SDL ERROR: " << errorString << std::endl;
            }
        }

        void GraphicsWindowImpl::SetCaption( const std::string& windowTitle, const std::string& iconifiedWindowTitle )
        {
            assert( m_bIsInitialized && "The window is not initialized. First call GraphicsWindowImpl::Initialize()." );

            m_WindowTitle = windowTitle;
            m_IconifiedWindowTitle = iconifiedWindowTitle;

            SDL_WM_SetCaption( windowTitle.c_str(), iconifiedWindowTitle.c_str() );
        }

        bool GraphicsWindowImpl::CreateWindow( const GraphicsWindow::WindowDescription& desc )
        {
            assert( m_bIsInitialized && "The window is not initialized. First call GraphicsWindowImpl::Initialize()." );

            // If the window was already created, do nothing.
            if ( m_pSurface != NULL ) return true;

            m_WindowDescription = desc;

            Uint32 windowFlags = SDL_HWSURFACE | SDL_OPENGL;
            windowFlags |= ( desc.Fullscreen ? SDL_FULLSCREEN : 0 );

            // TODO: Check for supported window sizes
            // @see SDL_GetVideoInfo and SDL_ListModes

            // Set the OpenGL Attributes before we create a context
            // TODO: These should be passed to the app in some parameters struct or somethings
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            desc.NumRedBits );
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          desc.NumGreenBits );
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           desc.NumBlueBits );
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          desc.NumAlphaBits );
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          desc.NumDepthBits );
            SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         desc.NumBufferBits );

            SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,      desc.NumAccumRedBits );
            SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    desc.NumAccumGreenBits );
            SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,     desc.NumAccumBlueBits );
            SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    desc.NumAccumAlphaBits );

            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  desc.NumMultiSampleBuffers );
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  desc.NumMultiSamples );

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,        1);
            SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL,       0 );

            // Create the OpenGL surface for the graphics renderer
            m_pSurface = SDL_SetVideoMode( desc.Width, desc.Height, 0, windowFlags );
            if ( m_pSurface == NULL )
            {
                std::cerr << "Unable to create surface for OpenGL context." << std::endl;
                const char* sdlError = SDL_GetError();
                std::cerr << "SDL ERROR: " << sdlError << std::endl;
                return false;
            }

            return true;
        }

        bool GraphicsWindowImpl::ToggleFullScreen()
        {
            bool success = false;
            if ( m_bIsInitialized && m_pSurface != NULL )
            {
                // TODO: Do I have to destroy the current window first?
                Uint32 windowFlags = m_pSurface->flags;
                m_pSurface = SDL_SetVideoMode(0, 0, 0, windowFlags ^ SDL_FULLSCREEN );

                if ( m_pSurface == NULL )
                {
                    std::cerr << "Could not toggle full-screen mode." << std::endl;
                    // Try to set to original display mode
                    m_pSurface = SDL_SetVideoMode(0, 0, 0, windowFlags );
                    if ( m_pSurface == NULL )
                    {
                        std::cerr << "Could not create SDL window with original flags! Epic fail!" << std::endl;
                        const char* sdlError = SDL_GetError();
                        std::cerr << "SDL ERROR: " << sdlError << std::endl;
                    }
                }
                else
                {
                    success = true;
                }
            }
            return success;
        }

        void GraphicsWindowImpl::CloseWindow()
        {
            // Push a quit event on to the event queue to ensure
            // events are processed in the correct order.
            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
        }

        void GraphicsWindowImpl::DestroyWindow()
        {
            if ( m_pSurface != NULL )
            {
                SDL_FreeSurface( m_pSurface );
                m_pSurface = NULL;
            }
        }

        void GraphicsWindowImpl::Terminate()
        {
            if ( m_pIconImage != NULL )
            {
                SDL_FreeSurface( m_pIconImage );
                m_pIconImage = NULL;
            }

            if ( m_bIsInitialized )
            {
                SDL_Quit();
                m_bIsInitialized = false;
            }
        }

        void GraphicsWindowImpl::ProcessEvents()
        {
            SDL_Event event;
            while( SDL_PollEvent(&event) )
            {
                EventHandler(event);
            }
        }

        bool GraphicsWindowImpl::IsInitialized() const
        {
            return m_bIsInitialized;
        }

        void GraphicsWindowImpl::EventHandler( SDL_Event& event )
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
            // TODO: Joystick events
        }

        // The  window has received focus.
        void GraphicsWindowImpl::OnInputFocus( Ill::Core::EventArgs& e )
        {
            InputFocus( e );
        }

        // The window has lost focus
        void GraphicsWindowImpl::OnInputBlur( Ill::Core::EventArgs& e )
        {
            InputBlur( e );
        }

        // The window has received mouse focus.
        void GraphicsWindowImpl::OnMouseFocus( Ill::Core::EventArgs& e )
        {
            MouseFocus( e );
        }

        // The window has lost mouse focus.
        void GraphicsWindowImpl::OnMouseBlur( Ill::Core::EventArgs& e )
        {
            MouseBlur( e );
        }

        // The window has been minimized.
        void GraphicsWindowImpl::OnMinimize( Ill::Core::EventArgs& e )
        {
            Minimize( e );
        }

        // The application window has been restored.
        void GraphicsWindowImpl::OnRestore( Ill::Core::EventArgs& e )
        {
            Restore( e );
        }

        // A keyboard key was pressed.
        void GraphicsWindowImpl::OnKeyPressed( KeyEventArgs& e )
        {
            KeyPressed( e );
        }

        // A keyboard key was released.
        void GraphicsWindowImpl::OnKeyReleased( KeyEventArgs& e )
        {
            KeyReleased( e );
        }

        // The mouse was moved.
        void GraphicsWindowImpl::OnMouseMoved( MouseMotionEventArgs& e )
        {
            MouseMoved( e );
        }

        // A button on the mouse was pressed.
        void GraphicsWindowImpl::OnMouseButtonPressed( MouseButtonEventArgs& e )
        {
            MouseButtonPressed( e );
        }

        // A button on the mouse was released.
        void GraphicsWindowImpl::OnMouseButtonReleased( MouseButtonEventArgs& e )
        {
            MouseButtonReleased( e );
        }   

        // The window has been resized.
        void GraphicsWindowImpl::OnResize( Ill::Core::ResizeEventArgs& e )
        {
            Resize( e );
        }

        // The window contents should be repainted.
        void GraphicsWindowImpl::OnExpose( Ill::Core::EventArgs& e )
        {
            Expose( e );
        }

        // The user requested to exit the application.
        void GraphicsWindowImpl::OnExit( Ill::Core::EventArgs& e )
        {
            Exit( e );
        }

        void GraphicsWindowImpl::OnUserEvent( Ill::Core::UserEventArgs& e )
        {
            UserEvent( e );
        }

        int GraphicsWindowImpl::GetWindowWidth() const
        {
            return ( m_pSurface == NULL ? 0 : m_pSurface->w );
        }

        int GraphicsWindowImpl::GetWindowHeight() const
        {
            return ( m_pSurface == NULL ? 0 : m_pSurface->h );
        }

    }
}