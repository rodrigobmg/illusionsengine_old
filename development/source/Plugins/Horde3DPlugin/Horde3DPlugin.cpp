#include <Plugins/Horde3DPlugin/Horde3DPluginPCH.hpp>
#include <Plugins/Horde3DPlugin/Horde3DPlugin.h>
#include <Plugins/Horde3DPlugin/Horde3DGraphicsRenderer.hpp>
#include <Plugins/Horde3DPlugin/Horde3DPluginSubsystem.hpp>
#include <Plugins/Horde3DPlugin/Horde3dWindow.hpp>

using namespace Ill::Plugins::Horde3D;

Horde3DPluginPtr g_pHorde3DPlugin;

extern "C" Ill::Core::PluginPtr CreatePlugin(void)
{
    g_pHorde3DPlugin = boost::make_shared<Horde3DPlugin>();
    return g_pHorde3DPlugin;
}

extern "C" void DestroyPlugin(void)
{
    g_pHorde3DPlugin.reset();
}

extern "C" void InstantiateTypes()
{
    Horde3DPlugin();
    Horde3DPluginSubsystem();
    Horde3DGraphicsRenderer();
    Horde3DWindow();
}

Horde3DPlugin::Horde3DPlugin()
{

}

bool Horde3DPlugin::Initialize()
{
    InstantiateTypes();
    return Super::Initialize();
}

void Horde3DPlugin::Terminiate()
{
    Super::Initialize();
}
