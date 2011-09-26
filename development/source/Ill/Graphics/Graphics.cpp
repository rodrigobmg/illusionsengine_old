#include <Ill/Graphics/GraphicsPCH.hpp>
#include <Ill/Graphics/Graphics.hpp>

namespace Ill
{
    namespace Graphics
    {
        void InstantiateTypes()
        {
            GrapicsSubsystem();
            // GraphicsRenderer(); // This class is abstract and cannot be instantiated.
        }
    }
}