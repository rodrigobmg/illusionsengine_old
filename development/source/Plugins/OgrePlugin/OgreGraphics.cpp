#include <Ill/OgreGraphics/PrecompiledHeader.hpp>
#include <Ill/OgreGraphics/OgreGraphics.hpp>

void TestReflection()
{
    std::cout << "Class List: " << std::endl;

    const Class::ClassList& classes  = Class::getClasses();
    Class::ClassList::const_iterator iter = classes.begin();
    int i = 0;
    while( iter != classes.end() )
    {
        Class* pClass = (*iter);
        std::cout << "[" << i << "] " << pClass->getFullName() << std::endl;

        ++i;
        ++iter;
    }
}

// The main entry point for our DLL
BOOL WINAPI DllMain(HINSTANCE hinstDLL,  // handle to DLL module
                    DWORD fdwReason,     // reason for calling function
                    LPVOID lpReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
    case DLL_PROCESS_ATTACH:
        Ill::OgreGraphics::InstantiateTypes();
        TestReflection();
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

namespace Ill
{
    namespace OgreGraphics
    {
        void InstantiateTypes()
        {
            OgreRenderer();
        }
    }
}