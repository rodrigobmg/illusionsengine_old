#include <Plugins/Horde3DPlugin/Horde3DPluginPCH.hpp>
#include <Plugins/Horde3DPlugin/Horde3DPlugin.h>

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
