#include <Ill/Graphics/GraphicsPCH.hpp>
#include <Ill/Graphics/GraphicsWindow.hpp>

namespace Ill
{
    namespace Graphics
    {
        GraphicsWindow::GraphicsWindow()
        {
        }

        bool GraphicsWindow::Initialize()
        {
            return false;
        }

        bool GraphicsWindow::IsInitialized()
        {
            return false;
        }

        void GraphicsWindow::Terminate()
        {
        }

        void GraphicsWindow::SetIcon( const std::string& iconImage )
        {
        }

        void GraphicsWindow::SetCaption( const std::string& windowTitle, const std::string& iconifiedWindowTitle )
        {
        }

        bool GraphicsWindow::CreateWindow(const WindowDescription& )
        {
            return false;
        }

        void GraphicsWindow::CloseWindow()
        {
        }

        bool GraphicsWindow::ToggleFullScreen()
        {
            return false;
        }

        void GraphicsWindow::ProcessEvents()
        {
        }

        void GraphicsWindow::DestroyWindow()
        {
        }

        uint32 GraphicsWindow::GetWindowWidth()
        {
            return 0;
        }

        uint32 GraphicsWindow::GetWindowHeight()
        {
            return 0;
        }

        // The  window has received focus.
        void GraphicsWindow::OnInputFocus( Ill::Core::EventArgs& e )
        {
            InputFocus( e );
        }

        // The window has lost focus
        void GraphicsWindow::OnInputBlur( Ill::Core::EventArgs& e )
        {
            InputBlur( e );
        }

        // The window has received mouse focus.
        void GraphicsWindow::OnMouseFocus( Ill::Core::EventArgs& e )
        {
            MouseFocus( e );
        }

        // The window has lost mouse focus.
        void GraphicsWindow::OnMouseBlur( Ill::Core::EventArgs& e )
        {
            MouseBlur( e );
        }

        // The window has been minimized.
        void GraphicsWindow::OnMinimize( Ill::Core::EventArgs& e )
        {
            Minimize( e );
        }

        // The application window has been restored.
        void GraphicsWindow::OnRestore( Ill::Core::EventArgs& e )
        {
            Restore( e );
        }

        // A keyboard key was pressed.
        void GraphicsWindow::OnKeyPressed( KeyEventArgs& e )
        {
            KeyPressed( e );
        }

        // A keyboard key was released.
        void GraphicsWindow::OnKeyReleased( KeyEventArgs& e )
        {
            KeyReleased( e );
        }

        // The mouse was moved.
        void GraphicsWindow::OnMouseMoved( MouseMotionEventArgs& e )
        {
            MouseMoved( e );
        }

        // A button on the mouse was pressed.
        void GraphicsWindow::OnMouseButtonPressed( MouseButtonEventArgs& e )
        {
            MouseButtonPressed( e );
        }

        // A button on the mouse was released.
        void GraphicsWindow::OnMouseButtonReleased( MouseButtonEventArgs& e )
        {
            MouseButtonReleased( e );
        }   

        // The window has been resized.
        void GraphicsWindow::OnResize( Ill::Core::ResizeEventArgs& e )
        {
            Resize( e );
        }

        // The window contents should be repainted.
        void GraphicsWindow::OnExpose( Ill::Core::EventArgs& e )
        {
            Expose( e );
        }

        // The user requested to exit the application.
        void GraphicsWindow::OnExit( Ill::Core::EventArgs& e )
        {
            Exit( e );
        }

        void GraphicsWindow::OnUserEvent( Ill::Core::UserEventArgs& e )
        {
            UserEvent( e );
        }
    }
}