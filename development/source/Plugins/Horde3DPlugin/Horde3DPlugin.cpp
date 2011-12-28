#include <Plugins/Horde3DPlugin/Horde3DPluginPCH.hpp>
#include <Plugins/Horde3DPlugin/Horde3DPlugin.h>

Ill::Plugins::Horde3D::Horde3DPluginPtr g_pHorde3DPlugin;

Ill::Core::PluginPtr CreatePlugin(void)
{
    g_pHorde3DPlugin = boost::make_shared<Ill::Plugins::Horde3D::Horde3DPlugin>();
    return g_pHorde3DPlugin;
}

void DestroyPlugin(void)
{
    g_pHorde3DPlugin.reset();
}

NAMESPACE_H3D_BEGIN

void InstantiateTypes()
{
    Horde3DPlugin();
}

Horde3DPlugin::Horde3DPlugin()
{

}

bool Horde3DPlugin::Initialize()
{
    
    return Super::Initialize();
}

void Horde3DPlugin::Terminiate()
{
    Super::Initialize();
}

NAMESPACE_H3D_END
