#ifndef ILL_CORE_EVENTS_HPP
#define ILL_CORE_EVENTS_HPP

#include <Ill/Core/Object.fwd.hpp>

namespace Ill
{
    namespace Core
    {
        // Event template class for encapsulating event callback functions.
        template< class ArgumentType >
        class Delegate
        {
        public:
            typedef boost::function< void ( ArgumentType& ) > FunctionType;
            //typedef boost::signal< void ( typename ArgumentType& ) > FunctionType;
            typedef boost::signals::connection ConnectionType;

            // Add a callback to the the list
            // Returns the connection object that can be used to disconnect the 
            // subscriber from the signal.
            ConnectionType operator += ( typename const FunctionType& callback ) const
            {
                return m_Callbacks.connect( callback );
            }

            // Remove a callback from the list
            void operator -= ( typename const FunctionType& callback ) const
            {
                assert(false);
                // TODO: This isn't working yet.. Getting a compiler error:
                // Error	1	error C2666: 'boost::operator ==' : 4 overloads have similar conversions signal_template.hpp
                // WORKAROUND: Use the connection object returned when the subscriber was initially connected
                // to disconnect the subscriber.
                m_Callbacks.disconnect( callback );
            }

            void operator -= ( ConnectionType& con )
            {
                m_Callbacks.disconnect( con ); // This doesn't seem to work either!?
                if ( con.connected() )
                {
                    con.disconnect(); // This is stupid, then all connections disconnected in this way even if it was never registered with the signal!
                }
            }

            // Invoke this event with the argument
            void operator()( typename ArgumentType& argument )
            {
                m_Callbacks( argument );
            }

        private:
            typedef boost::signal< void (ArgumentType&) > Callbacks;
            mutable Callbacks   m_Callbacks;
        };

        // Base class for all event args
        class EventArgs
        {
        public:
            EventArgs( const Object& caller )
                : Caller(caller)
            {}

            // The object that invoked the event
            const Object& Caller;
        };
        // Standard event type
        typedef Delegate<EventArgs> Event;

        class ResizeEventArgs : public EventArgs
        {
        public:
            typedef EventArgs base;
            ResizeEventArgs( const Object& caller, int width, int height )
                : base( caller )
                , Dimensions( width, height )
            {}

            // The new dimensions of the window
            glm::ivec2 Dimensions;

        };
        typedef Delegate<ResizeEventArgs> ResizeEvent;

        class UpdateEventArgs : public EventArgs
        {
        public:
            typedef EventArgs base;
            UpdateEventArgs( const Object& caller, float fDeltaTime, float fTotalTime )
                : base( caller )
                , ElapsedTime( fDeltaTime )
                , TotalTime( fTotalTime )
            {}

            float ElapsedTime;
            float TotalTime;
        };
        typedef Delegate<UpdateEventArgs> UpdateEvent;

        class RenderEventArgs : public EventArgs
        {
        public:
            typedef EventArgs base;
            RenderEventArgs( const Object& caller, float fDeltaTime, float fTotalTime )
                : base( caller )
                , ElapsedTime( fDeltaTime )
                , TotalTime( fTotalTime )
            {}

            float ElapsedTime;
            float TotalTime;
        };
        typedef Delegate<RenderEventArgs> RenderEvent;

        class UserEventArgs : public EventArgs
        {
        public:
            typedef EventArgs base;
            UserEventArgs( const Object& caller, int code, void* data1, void* data2 )
                : base( caller )
                , Code( code )
                , Data1( data1 )
                , Data2( data2 )
            {}

            int     Code;
            void*   Data1;
            void*   Data2;
        };
        typedef Delegate<UserEventArgs> UserEvent;

    } // namespace Core
} // namespace Ill

#endif // ILL_CORE_EVENTS_HPP