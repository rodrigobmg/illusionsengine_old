#ifndef ILL_PLUGINS_HORDE3DPLUGIN_FWD_HPP
#define ILL_PLUGINS_HORDE3DPLUGIN_FWD_HPP

namespace Ill
{
    namespace Plugins
    {
        namespace Horde3D
        {
//            DECLARE_PTR( Horde3DPlugin );
            class Horde3DPlugin;
            typedef boost::shared_ptr<Horde3DPlugin> Horde3DPluginPtr;
            typedef boost::weak_ptr<Horde3DPlugin> Horde3DPluginWeakPtr;
        }
    }
}

#endif // ILL_PLUGINS_HORDE3DPLUGIN_FWD_HPP