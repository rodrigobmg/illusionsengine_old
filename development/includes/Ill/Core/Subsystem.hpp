/**
* @file Subsystem.h
* @date December 09, 2008
* @author Jeremiah van Oosten
* 
* @brief The subsystem definition.
* @description This class is the abstract base class for all subsystem components
* that can be registered and managed by the Application class.
*/

#ifndef ILL_CORE_SUBSYSTEM_HPP
#define ILL_CORE_SUBSYSTEM_HPP

#include <Ill/Core/PropertyMap.hpp>
#include <Ill/Core/Object.hpp>
#include <Ill/Core/Subsystem.fwd.hpp>
#include <Ill/Core/Application.fwd.hpp>

namespace Ill
{
	namespace Core
	{
		class CORE_DLL Subsystem : public Object
		{
		public:
			CLASS( Subsystem, Object );
			CONSTRUCTOR( CORE_DLL, public, Subsystem, () );

			/**
			* Startup
			*/
			VIRTUAL_METHOD( CORE_DLL, public, bool, Startup, ( const boost::property_tree::ptree& startupOptions ) );

			/**
			* Shutdown
			*/
			VIRTUAL_METHOD( CORE_DLL, public, bool, Shutdown, () );

        protected:
            ApplicationWeakPtr get_App() const;
            void set_App( ApplicationWeakPtr application );

        private:
            // Only store a weak pointer to the application to avoid creating
            // circular references.
            ApplicationWeakPtr m_pApplication;

        public:
            PROPERTY( CORE_DLL, ApplicationWeakPtr, App );
		};
	}
}

#endif // ILL_CORE_SUBSYSTEM_HPP