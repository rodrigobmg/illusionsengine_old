#include <Ill/Core/CorePCH.hpp>
#include <Ill/Core/Subsystem.hpp>

namespace Ill
{
	namespace Core
	{
		Subsystem::Subsystem()
		{}

        ApplicationWeakPtr Subsystem::get_App() const
        {
            return m_pApplication;
        }

        void Subsystem::set_App( ApplicationWeakPtr application )
        {
            m_pApplication = application;
        }

        bool Subsystem::Startup( const boost::property_tree::ptree& statupOptions )
		{
			return true;
		}

		bool Subsystem::Shutdown()
		{
			return true;
		}
	}
}