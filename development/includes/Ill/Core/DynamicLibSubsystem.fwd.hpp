#ifndef ILL_CORE_DYNAMIDLIBSUBSYSTEM_FWD_HPP
#define ILL_CORE_DYNAMIDLIBSUBSYSTEM_FWD_HPP
/**
 * DynamicLibSubsystem forward declarations.
 */

namespace Ill
{
    namespace Core
    {
        class DynamicLibSubsystem;
        //DECLARE_PTR( DynamicLibSubsystem );
        typedef boost::shared_ptr<DynamicLibSubsystem> DynamicLibSubsystemPtr;
        typedef boost::weak_ptr<DynamicLibSubsystem> DynamicLibSubsystemWeakPtr;
    }
}

#endif // ILL_CORE_DYNAMIDLIBSUBSYSTEM_FWD_HPP