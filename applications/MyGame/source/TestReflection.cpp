#include <MyGamePCH.hpp>
#include <TestReflection.h>

using namespace agm::reflection;

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