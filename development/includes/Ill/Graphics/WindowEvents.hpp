#ifndef ILL_GRAPHICS_WINDOWEVENTS_HPP
#define ILL_GRAPHICS_WINDOWEVENTS_HPP

#include <Ill/Core/KeyboardKeys.hpp>
#include <Ill/Core/MouseDefines.hpp>
#include <Ill/Core/Events.hpp>

namespace Ill
{
    namespace Graphics
    {
        // SDL specific events.
        class KeyEventArgs : public Ill::Core::EventArgs
        {
        public:

            typedef Ill::Core::EventArgs base;
            KeyEventArgs( const Ill::Core::Object& caller, Ill::Core::Keyboard::Key key, Ill::Core::Keyboard::Modifier mod, Ill::Core::Keyboard::KeyState state, uint16 unicode )
                : base( caller )
                , Key(key)
                , Modifier(mod)
                , State(state)
                , Unicode(unicode)
            {}

            Ill::Core::Keyboard::Key        Key;
            Ill::Core::Keyboard::Modifier   Modifier;
            Ill::Core::Keyboard::KeyState   State;
            uint16                          Unicode;
        };
        typedef Ill::Core::Delegate<KeyEventArgs> KeyboardEvent;

        class MouseMotionEventArgs : public Ill::Core::EventArgs
        {
        public:
            typedef Ill::Core::EventArgs base;
            MouseMotionEventArgs( const Ill::Core::Object& caller, Ill::Core::Mouse::ButtonState buttonState, uint16 absX, uint16 absY, int16 relX, int16 relY )
                : base( caller )
                , ButtonState( buttonState )
                , AbsPosition( absX, absY )
                , RelPosition( relX, relY )
            {}

            // The current state of the mouse buttons
            Ill::Core::Mouse::ButtonState ButtonState;

            // The absolute position of the mouse in screen coordinates?
            glm::ivec2 AbsPosition;
            // The relative position of the mouse (delta since last measurement).
            glm::ivec2 RelPosition;

        };
        typedef Ill::Core::Delegate<MouseMotionEventArgs> MouseMotionEvent;

        class MouseButtonEventArgs : public Ill::Core::EventArgs
        {
        public:
            typedef Ill::Core::EventArgs base;
            MouseButtonEventArgs( const Ill::Core::Object& caller, uint8 buttonID, Ill::Core::Mouse::ButtonState state, uint16 absX, uint16 absY )
                : base( caller )
                , ButtonID( buttonID )
                , State( state )
                , AbsPosition( absX, absY )
            {}

            // The ID of the button the triggered the event
            uint8       ButtonID;
            // The state (Released, Pressed)
            Ill::Core::Mouse::ButtonState State;
            // The absolute position of the mouse when the event was triggered
            glm::ivec2  AbsPosition;
        };
        typedef Ill::Core::Delegate<MouseButtonEventArgs> MouseButtonEvent;

        // TODO: Joystick events

    }
}

#endif // ILL_GRAPHICS_WINDOWEVENTS_HPP