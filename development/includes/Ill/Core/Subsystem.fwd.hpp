#ifndef ILL_CORE_SUBSYSTEM_FWD_HPP
#define ILL_CORE_SUBSYSTEM_FWD_HPP
/**
 * Forward declarations for Subsystem types.
 */

namespace Ill
{
    namespace Core
    {
        class Subsystem;
//        DECLARE_PTR(Subsystem);
        typedef boost::shared_ptr<Subsystem> SubsystemPtr;
        typedef boost::weak_ptr<Subsystem> SubsystemWeakPtr;

    }
}

#endif ILL_CORE_SUBSYSTEM_FWD_HPP