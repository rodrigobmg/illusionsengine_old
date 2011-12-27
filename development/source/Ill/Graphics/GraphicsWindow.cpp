#include <Ill/Graphics/GraphicsPCH.hpp>

#include <Ill/Graphics/GraphicsWindow.hpp>
#include "GraphicsWindowImpl.hpp"

namespace Ill
{
    namespace Graphics
    {
        GraphicsWindow::GraphicsWindow()
            : m_pImplementation( new GraphicsWindowImpl() )
        {
            // Connect the events from the graphics window implementation
            // with the event handlers for this window object.
            m_pImplementation->InputFocus += boost::bind( &GraphicsWindow::OnInputFocus, this, _1 );
            m_pImplementation->InputBlur += boost::bind( &GraphicsWindow::OnInputBlur, this, _1 );
            m_pImplementation->MouseFocus += boost::bind( &GraphicsWindow::OnMouseFocus, this, _1 );
            m_pImplementation->MouseBlur += boost::bind( &GraphicsWindow::OnMouseBlur, this, _1 );
            m_pImplementation->Minimize += boost::bind( &GraphicsWindow::OnMinimize, this, _1 );
            m_pImplementation->Restore += boost::bind( &GraphicsWindow::OnRestore, this, _1 );
            m_pImplementation->Resize += boost::bind( &GraphicsWindow::OnResize, this, _1 );
            m_pImplementation->Expose += boost::bind( &GraphicsWindow::OnExpose, this, _1 );
            m_pImplementation->Exit += boost::bind( &GraphicsWindow::OnExit, this, _1 );

            // Keyboard events
            m_pImplementation->KeyPressed += boost::bind( &GraphicsWindow::OnKeyPressed, this, _1 );
            m_pImplementation->KeyReleased += boost::bind( &GraphicsWindow::OnKeyReleased, this, _1 );

            // Mouse events
            m_pImplementation->MouseMoved += boost::bind( &GraphicsWindow::OnMouseMoved, this, _1 );
            m_pImplementation->MouseButtonPressed += boost::bind( &GraphicsWindow::OnMouseButtonPressed, this, _1 );
            m_pImplementation->MouseButtonReleased += boost::bind( &GraphicsWindow::OnMouseButtonReleased, this, _1 );

            // User events
            m_pImplementation->UserEvent += boost::bind( &GraphicsWindow::OnUserEvent, this, _1 );
        }

        bool GraphicsWindow::Initialize()
        {
            return m_pImplementation->Initialize();
        }

        bool GraphicsWindow::IsInitialized()
        {
            return m_pImplementation->IsInitialized();
        }

        void GraphicsWindow::Terminate()
        {
            m_pImplementation->Terminate();
        }

        void GraphicsWindow::SetIcon( const std::string& iconImage )
        {
            return m_pImplementation->SetIcon( iconImage );
        }

        void GraphicsWindow::SetCaption( const std::string& windowTitle, const std::string& iconifiedWindowTitle )
        {
            m_pImplementation->SetCaption( windowTitle, iconifiedWindowTitle );
        }

        bool GraphicsWindow::CreateWindow(const WindowDescription& windowDescription )
        {
            return m_pImplementation->CreateWindow( windowDescription );
        }

        void GraphicsWindow::CloseWindow()
        {
            m_pImplementation->CloseWindow();
        }

        bool GraphicsWindow::ToggleFullScreen()
        {
            return m_pImplementation->ToggleFullScreen();
        }

        void GraphicsWindow::ProcessEvents()
        {
            m_pImplementation->ProcessEvents();
        }

        void GraphicsWindow::DestroyWindow()
        {
            m_pImplementation->DestroyWindow();
        }

        uint32 GraphicsWindow::GetWindowWidth()
        {
            return m_pImplementation->GetWindowWidth();
        }

        uint32 GraphicsWindow::GetWindowHeight()
        {
            return m_pImplementation->GetWindowHeight();
        }

        // The  window has received focus.
        void GraphicsWindow::OnInputFocus( Ill::Core::EventArgs& e )
        {
            Ill::Core::EventArgs eventArgs(*this);
            InputFocus( eventArgs );
        }

        // The window has lost focus
        void GraphicsWindow::OnInputBlur( Ill::Core::EventArgs& e )
        {
            Ill::Core::EventArgs eventArgs(*this);
            InputBlur( eventArgs );
        }

        // The window has received mouse focus.
        void GraphicsWindow::OnMouseFocus( Ill::Core::EventArgs& e )
        {
            Ill::Core::EventArgs eventArgs(*this);
            MouseFocus( eventArgs );
        }

        // The window has lost mouse focus.
        void GraphicsWindow::OnMouseBlur( Ill::Core::EventArgs& e )
        {
            Ill::Core::EventArgs eventArgs(*this);
            MouseBlur( eventArgs );
        }

        // The window has been minimized.
        void GraphicsWindow::OnMinimize( Ill::Core::EventArgs& e )
        {
            Ill::Core::EventArgs eventArgs(*this);
            Minimize( eventArgs );
        }

        // The application window has been restored.
        void GraphicsWindow::OnRestore( Ill::Core::EventArgs& e )
        {
            Ill::Core::EventArgs eventArgs(*this);
            Restore( eventArgs );
        }

        // A keyboard key was pressed.
        void GraphicsWindow::OnKeyPressed( KeyEventArgs& e )
        {
            KeyEventArgs keyEventArgs( *this, e.Key, e.Modifier, e.State, e.Unicode );
            KeyPressed( keyEventArgs );
        }

        // A keyboard key was released.
        void GraphicsWindow::OnKeyReleased( KeyEventArgs& e )
        {
            KeyEventArgs keyEventArgs( *this, e.Key, e.Modifier, e.State, e.Unicode );
            KeyReleased( keyEventArgs );
        }

        // The mouse was moved.
        void GraphicsWindow::OnMouseMoved( MouseMotionEventArgs& e )
        {
            MouseMotionEventArgs mouseMotionEventArgs( *this, e.ButtonState, e.AbsPosition.x, e.AbsPosition.y, e.RelPosition.x, e.RelPosition.y );
            MouseMoved( mouseMotionEventArgs );
        }

        // A button on the mouse was pressed.
        void GraphicsWindow::OnMouseButtonPressed( MouseButtonEventArgs& e )
        {
            MouseButtonEventArgs mouseButtonEventArgs( *this, e.ButtonID, e.State, e.AbsPosition.x, e.AbsPosition.y );
            MouseButtonPressed( mouseButtonEventArgs );
        }

        // A button on the mouse was released.
        void GraphicsWindow::OnMouseButtonReleased( MouseButtonEventArgs& e )
        {
            MouseButtonEventArgs mouseButtonEventArgs( *this, e.ButtonID, e.State, e.AbsPosition.x, e.AbsPosition.y );
            MouseButtonReleased( mouseButtonEventArgs );
        }   

        // The window has been resized.
        void GraphicsWindow::OnResize( Ill::Core::ResizeEventArgs& e )
        {
            Ill::Core::ResizeEventArgs resizeEventArgs( *this, e.Dimensions.x, e.Dimensions.y );
            Resize( resizeEventArgs );
        }

        // The window contents should be repainted.
        void GraphicsWindow::OnExpose( Ill::Core::EventArgs& e )
        {
            Ill::Core::EventArgs eventArgs( *this );
            Expose( eventArgs );
        }

        // The user requested to exit the application.
        void GraphicsWindow::OnExit( Ill::Core::EventArgs& e )
        {
            Ill::Core::EventArgs eventArgs( *this );
            Exit( eventArgs );
        }

        void GraphicsWindow::OnUserEvent( Ill::Core::UserEventArgs& e )
        {
            Ill::Core::UserEventArgs userEventArgs( *this, e.Code, e.Data1, e.Data2 );
            UserEvent( userEventArgs );
        }
    }
}