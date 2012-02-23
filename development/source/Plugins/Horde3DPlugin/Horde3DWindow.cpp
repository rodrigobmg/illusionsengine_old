#include <Plugins/Horde3DPlugin/Horde3DPluginPCH.hpp>
#include <Plugins/Horde3DPlugin/Horde3dWindow.hpp>

using namespace Ill::Graphics;

NAMESPACE_H3D_BEGIN
        Horde3DWindow::Horde3DWindow()
            : m_bIsInitialized(false)
            , m_pSurface(NULL)
            , m_pIconImage(NULL)
        {}

        void Horde3DWindow::Initialize()
        {
            if ( !m_bIsInitialized && SDL_Init(SDL_INIT_VIDEO) < 0 )
            {
                std::cerr << "Horde3DWindow::Initialize: SDL_Init failed (is the video subsystem already initialized?)" << std::endl;
                const char* sdlError = SDL_GetError();
                std::cerr << "SDL ERROR: " << sdlError << std::endl;
            }

            m_bIsInitialized = true;
        }

        void Horde3DWindow::SetIcon( const std::string& iconImage )
        {
            assert( m_bIsInitialized && "The window is not initialized. First call Horde3DWindow::Initialize()." );

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

        void Horde3DWindow::SetCaption( const std::string& windowTitle, const std::string& iconifiedWindowTitle )
        {
            assert( m_bIsInitialized && "The window is not initialized. First call Horde3DWindow::Initialize()." );

            m_WindowTitle = windowTitle;
            m_IconifiedWindowTitle = iconifiedWindowTitle;

            SDL_WM_SetCaption( windowTitle.c_str(), iconifiedWindowTitle.c_str() );
        }

        bool Horde3DWindow::CreateWindow( const GraphicsWindow::WindowDescription& desc )
        {
            assert( m_bIsInitialized && "The window is not initialized. First call Horde3DWindow::Initialize()." );

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

        bool Horde3DWindow::ToggleFullScreen()
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

        void Horde3DWindow::CloseWindow()
        {
            // Push a quit event on to the event queue to ensure
            // events are processed in the correct order.
            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
        }

        void Horde3DWindow::DestroyWindow()
        {
            if ( m_pSurface != NULL )
            {
                SDL_FreeSurface( m_pSurface );
                m_pSurface = NULL;
            }
        }

        void Horde3DWindow::Terminate()
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

        void Horde3DWindow::ProcessEvents()
        {
            SDL_Event event;
            while( SDL_PollEvent(&event) )
            {
                EventHandler(event);
            }
        }

        bool Horde3DWindow::IsInitialized() const
        {
            return m_bIsInitialized;
        }

        void Horde3DWindow::EventHandler( SDL_Event& event )
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
                    KeyEventArgs keyEventArgs( *this, (Ill::Core::Keyboard::Key)event.key.keysym.sym, (Ill::Core::Keyboard::Modifier)event.key.keysym.mod, (Ill::Core::Keyboard::KeyState)event.key.state, event.key.keysym.unicode );
                    OnKeyPressed( keyEventArgs );
                }
                break;
            case SDL_KEYUP:
                {
                    KeyEventArgs keyEventArgs( *this, (Ill::Core::Keyboard::Key)event.key.keysym.sym, (Ill::Core::Keyboard::Modifier)event.key.keysym.mod, (Ill::Core::Keyboard::KeyState)event.key.state, event.key.keysym.unicode );
                    OnKeyReleased( keyEventArgs );
                }
                break;
            case SDL_MOUSEMOTION:
                {
                    MouseMotionEventArgs mouseMotionEventArgs( *this, (Ill::Core::Mouse::ButtonState)event.motion.state, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel );
                    OnMouseMoved( mouseMotionEventArgs );
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    MouseButtonEventArgs mouseButtonEventArgs( *this, event.button.button, (Ill::Core::Mouse::ButtonState)event.button.state, event.button.x, event.button.y );
                    OnMouseButtonPressed( mouseButtonEventArgs );
                }
                break;
            case SDL_MOUSEBUTTONUP:
                {
                    MouseButtonEventArgs mouseButtonEventArgs( *this, event.button.button, (Ill::Core::Mouse::ButtonState)event.button.state, event.button.x, event.button.y );
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
        void Horde3DWindow::OnInputFocus( Ill::Core::EventArgs& e )
        {
            Super::OnInputFocus(e);
        }

        // The window has lost focus
        void Horde3DWindow::OnInputBlur( Ill::Core::EventArgs& e )
        {
            Super::OnInputBlur( e );
        }

        // The window has received mouse focus.
        void Horde3DWindow::OnMouseFocus( Ill::Core::EventArgs& e )
        {
            Super::OnMouseFocus( e );
        }

        // The window has lost mouse focus.
        void Horde3DWindow::OnMouseBlur( Ill::Core::EventArgs& e )
        {
            Super::OnMouseBlur( e );
        }

        // The window has been minimized.
        void Horde3DWindow::OnMinimize( Ill::Core::EventArgs& e )
        {
            Super::OnMinimize( e );
        }

        // The application window has been restored.
        void Horde3DWindow::OnRestore( Ill::Core::EventArgs& e )
        {
            Super::OnRestore( e );
        }

        // A keyboard key was pressed.
        void Horde3DWindow::OnKeyPressed( KeyEventArgs& e )
        {
            Super::OnKeyPressed( e );
        }

        // A keyboard key was released.
        void Horde3DWindow::OnKeyReleased( KeyEventArgs& e )
        {
            Super::OnKeyReleased( e );
        }

        // The mouse was moved.
        void Horde3DWindow::OnMouseMoved( MouseMotionEventArgs& e )
        {
            Super::OnMouseMoved( e );
        }

        // A button on the mouse was pressed.
        void Horde3DWindow::OnMouseButtonPressed( MouseButtonEventArgs& e )
        {
            Super::OnMouseButtonPressed( e );
        }

        // A button on the mouse was released.
        void Horde3DWindow::OnMouseButtonReleased( MouseButtonEventArgs& e )
        {
            Super::OnMouseButtonReleased( e );
        }   

        // The window has been resized.
        void Horde3DWindow::OnResize( Ill::Core::ResizeEventArgs& e )
        {
            Super::OnResize( e );
        }

        // The window contents should be repainted.
        void Horde3DWindow::OnExpose( Ill::Core::EventArgs& e )
        {
            Super::OnExpose( e );
        }

        // The user requested to exit the application.
        void Horde3DWindow::OnExit( Ill::Core::EventArgs& e )
        {
            Super::OnExit( e );
        }

        void Horde3DWindow::OnUserEvent( Ill::Core::UserEventArgs& e )
        {
            Super::OnUserEvent( e );
        }

        int Horde3DWindow::GetWindowWidth() const
        {
            return ( m_pSurface == NULL ? 0 : m_pSurface->w );
        }

        int Horde3DWindow::GetWindowHeight() const
        {
            return ( m_pSurface == NULL ? 0 : m_pSurface->h );
        }

NAMESPACE_H3D_END