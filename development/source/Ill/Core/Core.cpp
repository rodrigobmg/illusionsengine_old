#include <Ill/Core/CorePCH.hpp>
#if ILL_COMPILER == ILL_COMPILER_MSVC
// Turn off warnings generated by the singleton implementation
#pragma  warning( push )
#   pragma warning( disable : 4661 )
#endif

#include <Ill/Core/Core.hpp>

namespace Ill
{
	namespace Core
	{
		void InstantiateTypes()
		{
			NoCopyObject();
			RefCountedObject();
			Object();
            Configuration();
            GameObject();
			Component();
			Subsystem();
			DynamicLibSubsystem();
			Application();
		}

        boost::uuids::random_generator uuid_generator;
	}
}

#if ILL_COMPILER == ILL_COMPILER_MSVC
// Turn off warnings generated by the singleton implementation
#pragma  warning ( pop )
#endif