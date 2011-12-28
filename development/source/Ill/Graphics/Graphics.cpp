#include <Ill/Graphics/GraphicsPCH.hpp>
#include <Ill/Graphics/Graphics.hpp>

namespace Ill
{
    namespace Graphics
    {
        void InstantiateTypes()
        {
            // GrapicsSubsystem(); // This class is abstract and cannot be instantiated.
            // GraphicsRenderer(); // This class is abstract and cannot be instantiated.
            GraphicsWindow();
        }
    }
}