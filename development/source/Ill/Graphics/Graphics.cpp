#include <Ill/System/Graphics/PrecompiledHeader.hpp>
#include <Ill/System/Graphics/Graphics.hpp>

namespace Ill
{
    namespace System
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
}