#ifndef ILL_CORE_APPLICATION_FWD_HPP
#define ILL_CORE_APPLICATION_FWD_HPP
/**
 * Forward declarations for the Application type.
 */

namespace Ill
{
    namespace Core
    {
        class CORE_DLL Application;
//        DECLARE_PTR( Application );
        typedef boost::shared_ptr<Application> ApplicationPtr;
        typedef boost::weak_ptr<Application> ApplicationWeakPtr;
    }
}

#endif