#ifndef ILL_CORE_PLUGIN_FWD_HPP
#define ILL_CORE_PLUGIN_FWD_HPP
/**
 * Forward declaration for plugin type.
 */

namespace Ill
{
    namespace Core
    {
        class Plugin;
        //DECLARE_PTR( Plugin );
        typedef boost::shared_ptr<Plugin> PluginPtr;
        typedef boost::weak_ptr<Plugin> PluginWeakPtr;
    }
}

#endif