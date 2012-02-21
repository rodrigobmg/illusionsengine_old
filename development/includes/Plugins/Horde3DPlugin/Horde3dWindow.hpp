#ifndef ILL_GRAPHICS_GRAPHICSWINDOWIMPL_HPP
#define ILL_GRAPHICS_GRAPHICSWINDOWIMPL_HPP

#include <Ill/Core/Object.hpp>
#include <Ill/Core/Events.hpp>
#include <Ill/Graphics/WindowEvents.hpp>
#include <Ill/Graphics/GraphicsWindow.hpp>
#include <Plugins/Horde3DPlugin/Horde3DPluginDefines.hpp>
#include <Plugins/Horde3DPlugin/Horde3dWindow.fwd.hpp>

NAMESPACE_H3D_BEGIN

class HORDE3DPLUGIN_DLL Horde3DWindow : public Ill::Graphics::GraphicsWindow
{
public:
    CLASS(Horde3DWindow, Ill::Graphics::GraphicsWindow);
    CONSTRUCTOR(HORDE3DPLUGIN_DLL, public, Horde3DWindow, () );

    /**
    * Initialize the SDL video subsystem.
    * This is required before we can create a window that 
    * is used to render OpenGL graphics into.
    *
    * @return true if the window subsystem was successfully initialized.
    */
    bool Initialize();

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
    void SetIcon( const std::string& iconImage );

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
    * @postcondition The title for window will be used on the newly created window.
    */
    void SetCaption( const std::string& windowTitle, const std::string& iconifiedWindowTitle );

    /**
    * Create a window that can be used to display OpenGL graphics onto.
    * Currently, it is not possible to create multiple windows.  Multi-window
    * support might become available when SDL 1.3 gets stable enough to 
    * use.
    * 
    * @param windowDescription A structure that defines the window attributes.
    *
    * @precondition Horde3DWindow::IsInitialized returns true.
    * @postcondition A window is created and displayed to the user
    */
    bool CreateWindow( const Ill::Graphics::GraphicsWindow::WindowDescription& windowDescription );

    /**
    * Attempt to toggle the window from windowed to full screen mode.
    * This function is currently not supported on all platforms.
    *
    * @precondition The window must have already been created.
    * @postcondition The window will switch from windowed to full-screen
    * or full-screen to windowed mode.
    */
    bool ToggleFullScreen();


    /**
    * Enqueue an event on the event queue that will cause the window to close
    * in a timely fashion.
    *
    * @precondition A window has been created with Horde3DWindow::CreateWindow.
    * @postcondition An event to close the window will be added to the event queue.
    */
    void CloseWindow();

    /**
    * Destroy the window surface.
    * This should not be called directly.  Use @see(Horde3DWindow::CloseWindow).
    */
    void DestroyWindow();

    /**
    * Terminate the SDL video subsystem.
    *
    * @precondition The video subsystem has been initialized.
    * @postcondition The video subsystem has been shutdown.
    */
    void Terminate();

    /**
    * Process all events in the event queue. Appropriate events
    * will be invoked for the listeners to react to input events.
    *
    */
    void ProcessEvents();

    // Getters & Setters
    bool IsInitialized() const;

    int GetWindowWidth() const;
    int GetWindowHeight() const;

protected: 

    // Dispatch events to the appropriate event handlers.
    virtual void EventHandler( SDL_Event& event );

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
    virtual void OnKeyPressed( Ill::Graphics::KeyEventArgs& e );
    // A keyboard key was released.
    virtual void OnKeyReleased( Ill::Graphics::KeyEventArgs& e );
    // The mouse was moved.
    virtual void OnMouseMoved( Ill::Graphics::MouseMotionEventArgs& e );
    // A button on the mouse was pressed.
    virtual void OnMouseButtonPressed( Ill::Graphics::MouseButtonEventArgs& e );
    // A button on the mouse was released.
    virtual void OnMouseButtonReleased( Ill::Graphics::MouseButtonEventArgs& e );

    // The window has been resized.
    virtual void OnResize( Ill::Core::ResizeEventArgs& e );
    // The window contents should be repainted.
    virtual void OnExpose( Ill::Core::EventArgs& e );

    // The user requested to exit the application.
    virtual void OnExit( Ill::Core::EventArgs& e );

    // User event was added to the event queue.
    virtual void OnUserEvent( Ill::Core::UserEventArgs& e );

private:
    bool m_bIsInitialized;
    SDL_Surface* m_pSurface;
    SDL_Surface* m_pIconImage;

    Ill::Graphics::GraphicsWindow::WindowDescription m_WindowDescription;

    std::string m_WindowTitle;
    std::string m_IconifiedWindowTitle;
};

NAMESPACE_H3D_END

#endif // ILL_GRAPHICS_GRAPHICSWINDOWIMPL_HPP