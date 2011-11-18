#ifndef ILL_GRAPHICS_WINDOWEVENTS_HPP
#define ILL_GRAPHICS_WINDOWEVENTS_HPP

#include <Ill/Core/Events.hpp>

namespace Ill
{
    namespace Graphics
    {
        // SDL specific events.
        class KeyEventArgs : public Ill::Core::EventArgs
        {
        public:
            enum KeyState
            {
                KS_Released = 0,
                KS_Pressed = 1
            };

            typedef Ill::Core::EventArgs base;
            KeyEventArgs( const Ill::Core::Object& caller, SDLKey key, SDLMod mod, Uint8 state, Uint16 unicode )
                : base( caller )
                , Key(key)
                , Modifier(mod)
                , State((KeyState)state)
                , Unicode(unicode)
            {}

            SDLKey      Key;
            SDLMod      Modifier;
            KeyState    State;
            Uint16      Unicode;
        };
        typedef Ill::Core::Delegate<KeyEventArgs> KeyboardEvent;

        class MouseMotionEventArgs : public Ill::Core::EventArgs
        {
        public:
            typedef Ill::Core::EventArgs base;
            MouseMotionEventArgs( const Ill::Core::Object& caller, Uint8 buttonState, Uint16 absX, Uint16 absY, Sint16 relX, Sint16 relY )
                : base( caller )
                , ButtonState( buttonState )
                , AbsPosition( absX, absY )
                , RelPosition( relX, relY )
            {}

            // The current state of the mouse buttons
            Uint8      ButtonState;

            // The absolute position of the mouse in screen coordinates?
            glm::ivec2 AbsPosition;
            // The relative position of the mouse (delta since last measurement).
            glm::ivec2 RelPosition;

        };
        typedef Ill::Core::Delegate<MouseMotionEventArgs> MouseMotionEvent;

        class MouseButtonEventArgs : public Ill::Core::EventArgs
        {
        public:
            enum ButtonState
            {
                BS_Released = 0,
                BS_Pressed = 1
            };

            typedef Ill::Core::EventArgs base;
            MouseButtonEventArgs( const Ill::Core::Object& caller, Uint8 buttonID, Uint8 state, Uint16 absX, Uint16 absY )
                : base( caller )
                , ButtonID( buttonID )
                , State( (ButtonState)state )
                , AbsPosition( absX, absY )
            {}

            // The ID of the button the triggered the event
            Uint8       ButtonID;
            // The state (Released, Pressed)
            ButtonState State;
            // The absolute position of the mouse when the event was triggered
            glm::ivec2  AbsPosition;
        };
        typedef Ill::Core::Delegate<MouseButtonEventArgs> MouseButtonEvent;

        // TODO: Joystick events

    }
}

#endif // ILL_GRAPHICS_WINDOWEVENTS_HPP