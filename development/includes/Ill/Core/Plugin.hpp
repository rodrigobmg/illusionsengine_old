#ifndef ILL_CORE_PLUGIN_HPP
#define ILL_CORE_PLUGIN_HPP

#include <Ill/Core/Object.hpp>
#include <Ill/Core/Plugin.fwd.hpp>

namespace Ill
{
    namespace Core
    {
        class CORE_DLL Plugin : public Object
        {
        public:
            CLASS( Plugin, Object );
            CONSTRUCTOR( CORE_DLL, public, Plugin, () );

            /**
             * Default destructor
             */
            ~Plugin();

            /**
             * Initialize the plug-in including registering types
             * with the class registry, registering subsystems, and 
             * performing any other initialization steps required by the plug-in.
             */
            VIRTUAL_METHOD( CORE_DLL, public, bool, Initialize, () );

            /**
             * Terminate the plug-in including unregistering subsystems that 
             * were initialized in the Initialize() method.
             */
            VIRTUAL_METHOD( CORE_DLL, public, void, Terminiate, () );

        protected:

        private:
        };
    }
}

#endif // ILL_CORE_PLUGIN_HPP