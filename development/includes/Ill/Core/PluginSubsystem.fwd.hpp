#ifndef ILL_CORE_PLUGINSUBSYSTEM_FWD_H
#define ILL_CORE_PLUGINSUBSYSTEM_FWD_H
/**
 * PluginSubsystem forward declarations.
 */

namespace Ill
{
    namespace Core
    {
        class PluginSubsystem;
        //DECLARE_PTR( PluginSubsystem );
        typedef boost::shared_ptr<PluginSubsystem> PluginSubsystemPtr;
        typedef boost::weak_ptr<PluginSubsystem> PluginSubsystemWeakPtr;
    }
}

#endif // ILL_CORE_PLUGINSUBSYSTEM_FWD_H