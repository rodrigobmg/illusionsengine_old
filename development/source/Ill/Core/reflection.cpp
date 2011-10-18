/*
    AGM::LibReflection is a C++ reflection library.
    Version 0.8.
    Copyright (C) 2004 Achilleas Margaritis

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <Ill/Core/CorePCH.hpp>

#ifdef _MSC_VER
#pragma warning ( push )
#pragma warning (disable: 4003 4290 4786)
#endif

#include <Ill/Core/reflection.hpp>
#include <iostream>
#include <sstream>

#if __GNUC__ > 3 || \
    ( __GNUC__ == 3 && __GNUC_MINOR__ > 0 )
#define GCC_USEDEMANGLE
#endif

#ifdef GCC_USEDEMANGLE
#include <cstdlib>
#include <cxxabi.h>
#endif


namespace agm { namespace reflection {


std::string unmangle(const char * mangledName)
{
#ifdef GCC_USEDEMANGLE
    /*  for whatever reason, the ABI::CXA in gcc doesn't do the demangle if it is 
	single char name
      v void
      c char
      h unsigned char
      a signed char
      i int
      j unsigned int
      i signed int
      s short
      l long
      x long long
      f float
      d double
      e long double
    */
    if (mangledName[0] != '\0' && mangledName[1] == '\0') {
	switch (mangledName[0]) {
	    case 'v': return "void";
	    case 'c': return "char";
	    case 'h': return "unsigned char";
	    case 'a': return "signed char";
	    case 'i': return "int";
	    case 'j': return "unsigned int";
		//	    case 'i': return "signed int";
	    case 's': return "short";
	    case 'l': return "long";
	    case 'x': return "long long";
	    case 'f': return "float";
	    case 'd': return "double";
	    case 'e': return "long double";
	    case 'b': return "bool";
	    default:
		break;
	}
    }

    std::string result;
    int status;
    char* unmangled = abi::__cxa_demangle(mangledName, 0, 0, &status);
    if(status == 0)
    {
        result = std::string(unmangled);
        free(unmangled);
    }
    else
    {
        // Keep mangled name if result is not 0
        result = std::string(mangledName);
    }
    return result;
#else
    return std::string(mangledName);
#endif
}


MemberBase::MemberBase(const Class *pclass, ACCESS_TYPE access, const char *type, const char *name) :
        m_class(pclass),
        m_access(access),
        m_type(type), 
	m_name(name)
{
}

    /**assignment operator
     */
MemberBase& MemberBase::operator = (const MemberBase& other) {
    m_class = other.m_class;
    m_access = other.m_access;
    m_type = other.m_type;
    m_name = other.m_name;
    return *this;
}

MemberBase::MemberBase(const MemberBase & other)
: m_class(other.m_class),
      m_access(other.m_access),
      m_type(other.m_type), 
      m_name(other.m_name)
{
}



//default constructor
Field::Field(unsigned long offset, const std::type_info &typeinfo, const Class *pclass, ACCESS_TYPE access, const char *type, const char *name) :
MemberBase(pclass,access,type,name),
    m_typeinfo(typeinfo),
    m_offset(offset) {
}



    //default constructor
StaticField::StaticField(void *address, const std::type_info &typeinfo, const Class *pclass, ACCESS_TYPE access, const char *type, const char *name) :
    MemberBase(pclass,access,type,name), 
        m_typeinfo(typeinfo),
	m_address(address) {
    }


    /** retrieve argument parameter information
	@return argument parameters
    */
const MethodBase::ArgumentTypeList & MethodBase::getArgsTypes() const {
    if (m_callable == 0) throw InvalidStateError(std::string(getName()) +  " not initialized");
    return m_callable->get_args();
}

int MethodBase::getArgsCount() const {
    if (m_callable == 0) throw InvalidStateError(std::string(getName()) +  " not initialized");
    return m_callable->get_args_count();
}

const std::type_info& MethodBase::getReturnType() const {
    if (m_callable == 0) throw InvalidStateError(std::string(getName()) +  " not initialized");
    return m_callable->get_ret_type();
}


MethodBase& MethodBase::operator = (const MethodBase& other) {
    this->MemberBase::operator = (other);
    m_callable = other.m_callable;
    m_id = other.m_id;
    m_args = other.m_args;
    m_long_id = other.m_long_id;
    m_own_cb = false; /* no ownership */
    return *this;
}

MethodBase::MethodBase(const Class *pclass, ACCESS_TYPE access, const char *type, const char *name, const char *args) :
    MemberBase(pclass,access,type,name),
        m_callable(0),
	m_id(name),
	m_args(args),
	m_long_id(name),
	m_own_cb(false)
        {
        m_id += args;
	}


MethodBase::MethodBase(const MethodBase& other)
: MemberBase(other),
      m_callable(other.m_callable),
      m_id(other.m_id),
      m_args(other.m_args),
      m_long_id(other.m_long_id),
      m_own_cb(false) /* explicit set to false; no ownership of cb pointer */
{
}

void MethodBase::set_callable(__callable__ *cb) {
	typedef __callable__::arg_list_type arglist;
	if (m_own_cb) delete m_callable;
	m_callable = cb;
	if (cb) {
	    m_id = getName();
	    m_long_id = getPrefix(cb->get_ret_type());
	    m_long_id += '(';
	    if (cb->get_args_count() == 0) {
		m_id += "__";
		m_id += typeid(void).name();
	    } else {
		const arglist& list = cb->get_args();
		arglist::const_iterator i = list.begin();
		bool notfirst = false;
		while (i != list.end()) {
		    const std::type_info* ti = *i++;
		    m_id += "__";
		    m_id += ti->name();
		    if (notfirst) m_long_id += ", ";
		    m_long_id += unmangle(ti->name());
		    notfirst = true;
		}
	    }
	    m_long_id += ')';
	}
	m_own_cb = true;
    }


Method::~Method() {
}


    //default constructor
Method::Method(const Class *pclass, ACCESS_TYPE access, const char *type, const char *name, const char *args, bool virt) :
MethodBase(pclass,access,type,name,args),
    m_virtual(virt)
{
}


    //default constructor
StaticMethod::StaticMethod(const Class *pclass, ACCESS_TYPE access, const char *type, const char *name, const char *args) :
MethodBase(pclass,access,type,name,args)
{
}



    //default constructor
ConstructorMethod::ConstructorMethod(const Class *pclass, ACCESS_TYPE access, const char *type, const char *name, const char *args) :
StaticMethod(pclass,access,type,name,args)
{
}

    ///destructor
Property::~Property() {
    if (m_handler) delete m_handler;
}

    //default constructor
Property::Property(const Class *pclass, const char *type, const char *name, const std::type_info & typeinfo) :
MemberBase(pclass, ACCESS_PUBLIC, type, name),
    m_handler(0),
    m_typeinfo(typeinfo)
{
}


    //the default constructor
Class::Class(const char *name, const Class *super, size_t s, _new_instance_fun fun, _super_cast_fun super_case, _super_cast_const_fun super_cast_const, const std::type_info & tid, const std::type_info &ctid, const std::type_info &ptid, const std::type_info &cptid) 
:   m_name(name),
    m_super(super),
    m_new(fun),
    m_size(s),
    m_class_typeinfo(tid),
    m_class_ptr_typeinfo(ptid),
    m_class_const_typeinfo(ctid),
    m_class_const_ptr_typeinfo(cptid),
    m_fullname(unmangle(tid.name())),
    m_supercast(super_case),
    m_supercastconst(super_cast_const)
{
    getClassList().push_back(this);
    registerClassMap(MAP_CLASSFULLNAME, m_fullname);
    registerClassMap(MAP_CLASSNAME, m_class_typeinfo.name() );
    registerClassMap(MAP_CLASSNAME_CONST, m_class_const_typeinfo.name() );
    registerClassMap(MAP_CLASSNAME_PTR, m_class_ptr_typeinfo.name() );
    registerClassMap(MAP_CLASSNAME_PTR_CONST, m_class_const_ptr_typeinfo.name() );

}

Class::~Class()
{
    getClassList().remove(this);
    unregisterClassMap(MAP_CLASSFULLNAME, m_fullname);
    unregisterClassMap(MAP_CLASSNAME, m_class_typeinfo.name() );
    unregisterClassMap(MAP_CLASSNAME_CONST, m_class_const_typeinfo.name() );
    unregisterClassMap(MAP_CLASSNAME_PTR, m_class_ptr_typeinfo.name() );
    unregisterClassMap(MAP_CLASSNAME_PTR_CONST, m_class_const_ptr_typeinfo.name() );
}


bool Class::isBase(const Class &cl) const {
    for(const Class *c = cl.m_super; c; c = c->m_super) {
	if (c == this) return true;
    }
    return false;
}

void * Class::newInstance() const throw (UnknownMethodError) {
    if (m_new != 0) 
	return (*m_new)();
	
    const ConstructorMethod & c = getDefaultConstructor();
    typedef const __static_callable0__<void*> CallableType;
    CallableType *cb = (CallableType *)(c.m_callable); /* WARN: Dangerous casting  to void *(*)() */
    return cb->invoke();
}

bool Class::isRelative(const Class &cl) const {
        return isSame(cl) || isBase(cl) || cl.isBase(*this);
}

const Field &Class::getField(const char *name, bool searchSuper) const throw (UnknownFieldError) {
    _FieldMap::const_iterator it = m_fieldMap.find(name);
    if (it == m_fieldMap.end()) {
	if (searchSuper && m_super) return m_super->getField(name, true);
	throw UnknownFieldError(name);
    }
    return *it->second;
}

const StaticField &Class::getStaticField(const char *name, bool searchSuper) const throw (UnknownFieldError) {
    _StaticFieldMap::const_iterator it = m_staticFieldMap.find(name);
    if (it == m_staticFieldMap.end()) {
	if (searchSuper && m_super) return m_super->getStaticField(name, true);
	throw UnknownFieldError(name);
    }
    return *it->second;
}

const Method &Class::getMethod(const char *name, bool searchSuper) const throw (UnknownMethodError) {
    _MethodMap::const_iterator it = m_methodMap.find(name);
    if (it == m_methodMap.end()) {
	if (searchSuper && m_super) return m_super->getMethod(name, true);
	throw UnknownMethodError(name);
    }
    return *it->second;
}


Class::MethodVector Class::getAllMethods(const char *name, bool searchSuper) const throw (UnknownMethodError) {
    _MethodMap::const_iterator it = m_methodMap.find(name);
    const _MethodMap::const_iterator& end = m_methodMap.end();
    if (it == end) {
	if (searchSuper && m_super) return m_super->getAllMethods(name, true);
	throw UnknownMethodError(name);
    } else {
	MethodVector mlist;
	while (it != end && it->first == name) {
	    mlist.push_back(it->second);
	    ++it;
	}
	return mlist;
    }
}

const StaticMethod &Class::getStaticMethod(const char *name, bool searchSuper) const throw (UnknownMethodError) {
    _StaticMethodMap::const_iterator it = m_staticMethodMap.find(name);
    if (it == m_staticMethodMap.end()) {
	if (searchSuper && m_super) return m_super->getStaticMethod(name, true);
	throw UnknownMethodError(name);
    }
    return *it->second;
}

Class::StaticMethodVector Class::getAllStaticMethods(const char *name, bool searchSuper) const throw (UnknownMethodError) {
    _StaticMethodMap::const_iterator it = m_staticMethodMap.find(name);
    const _StaticMethodMap::const_iterator& end =m_staticMethodMap.end(); 
    if (it == end) {
	if (searchSuper && m_super) return m_super->getAllStaticMethods(name, true);
	throw UnknownMethodError(name);
    } else {
	StaticMethodVector mlist;
	while (it != end && it->first == name) {
	    mlist.push_back(it->second);
	    ++it;
	}
	return mlist;
    }
}

const ConstructorMethod &Class::getDefaultConstructor() const throw (UnknownMethodError) {
    const ConstructorMethod * m = defaultConstructor();
    if (m != 0) return *m;
    throw UnknownMethodError("Default Constructor");
}

const Property &Class::getProperty(const char *name, bool searchSuper) const throw (UnknownPropertyError) {
    _PropertyMap::const_iterator it = m_propertyMap.find(name);
    if (it == m_propertyMap.end()) {
	if (searchSuper && m_super) return m_super->getProperty(name, true);
	throw UnknownPropertyError(name);
    }
    return *it->second;
}


const Class * Class::forName(const std::string& name) {
    return findClassMap(MAP_CLASSFULLNAME,name);
}

const Class::ClassList &Class::getClasses() {
    return getClassList();
}

bool Class::dynamicCastableFromSuper(void *super_ptr, const Class *super) const {
    if (this == super) return true;
    return (m_super != 0) && m_super->dynamicCastableFromSuper(super_ptr, super) && dynamicCastFromSuper(super_ptr) == super_ptr;
}

bool Class::dynamicCastableFromSuper(const void *super_ptr, const Class *super) const {
    if (this == super) return true;
    return (m_super != 0) && m_super->dynamicCastableFromSuper(super_ptr, super) && dynamicCastFromSuperConst(super_ptr) == super_ptr;
}

const ConstructorMethod *Class::defaultConstructor() const {
    ConstructorList::const_iterator i = m_constructorMethods.begin();
    while (i != m_constructorMethods.end()) {
	const ConstructorMethod& c = *i;

	if (c.m_callable != 0 && c.m_callable->get_args_count() == 0) {
	    return &c;
	}
	++i;
    }
    return 0;
}
    

bool Class::registerClassMap(Class::MAP_TYPE t, const std::string& name) {
    std::pair<ClassMap::iterator, bool> result = getClassMap(t).insert(std::make_pair(name,this));
    if (! result.second) {
	std::cerr << "ERROR: Class " << m_name << " already registered";
	throw ClassRegistrationError(m_name);
    }
    return result.second;
}

void Class::unregisterClassMap(Class::MAP_TYPE t, const std::string& name )
{
    ClassMap& classMap = getClassMap(t);
    ClassMap::iterator iter = classMap.find(name);
    if ( iter != classMap.end() )
    {
        classMap.erase(iter);
    }
}

const Class * Class::findClassMap(Class::MAP_TYPE t, const std::string& name) {
    const ClassMap & cmap = getClassMap(t);
    ClassMap::const_iterator p=cmap.find(name);
    return (p == cmap.end())?0:p->second;
}


Class::ClassMap& Class::getClassMap(MAP_TYPE t) {
    static ClassMap all_class[MAP_SIZE];
    return all_class[t];
}

Class::ClassList& Class::getClassList() {
    static ClassList all_class;
    return all_class;
}


void Class::_addField(const Field &field) {
    m_fields.push_back(field);
    m_fieldMap.insert(std::make_pair<std::string,const Field *>(field.getName(),&m_fields.back()));
}

void Class::_addStaticField(const StaticField &field) {
    m_staticFields.push_back(field);
    m_staticFieldMap.insert(std::make_pair<std::string,const StaticField *>(field.getName(), &m_staticFields.back()));
}

void Class::_addMethod(const Method &method, __callable__ *cb) {
    m_methods.push_back(method);
    Method &m = m_methods.back();  /* holding a reference to an element in a container; need to make sure it won't invalidate */
    m.set_callable( cb);
    m_methodMap.insert(std::make_pair<std::string, const Method*>(method.getName(),&m));
}

void Class::_addStaticMethod(const StaticMethod &method, __callable__ *cb) {
    m_staticMethods.push_back(method);
    StaticMethod &m = m_staticMethods.back();
    m.set_callable( cb );
    m_staticMethodMap.insert(std::make_pair<std::string, const StaticMethod*>(method.getName(),&m));
}

void Class::_addConstructorMethod(const ConstructorMethod &method, __callable__ *cb) {
    m_constructorMethods.push_back(method);
    ConstructorMethod &m = m_constructorMethods.back();
    m.set_callable (cb);
}

void Class::_addProperty(const Property &prop, __property_base__ *handler) {
    m_properties.push_back(prop);
    Property &p = m_properties.back();
    p.m_handler = handler;
    m_propertyMap.insert(std::make_pair<std::string, const Property *>(prop.getName(),&p));
}

__register_field__::__register_field__(unsigned long offset, const std::type_info &typeinfo, const Class *pclass, enum ACCESS_TYPE access, const char *type, const char *name) {
    Field field(offset, typeinfo, pclass, access, type, name);
    ((Class *)pclass)->_addField(field);
}


__register_static_field__::__register_static_field__(void *address, const std::type_info &typeinfo, const Class *pclass, enum ACCESS_TYPE access, const char *type, const char *name) {
        StaticField field(address, typeinfo, pclass, access, type, name);
        ((Class *)pclass)->_addStaticField(field);
    }


__register_method__::__register_method__(__callable__ *cb, const Class *pclass, enum ACCESS_TYPE access, const char *type, const char *name, const char *args, const char *virt) {
        Method method(pclass, access, type, name, args, virt[0] == 'v' ? true : false);
        ((Class *)pclass)->_addMethod(method, cb);
    }


__register_static_method__::__register_static_method__(__callable__ *cb, const Class *pclass, enum ACCESS_TYPE access, const char *type, const char *name, const char *args) {
        StaticMethod method(pclass, access, type, name, args);
        ((Class *)pclass)->_addStaticMethod(method, cb);
    }


__register_constructor_method__::__register_constructor_method__(__callable__ *cb, const Class *pclass, enum ACCESS_TYPE access, const char *type, const char *name, const char *args) {
        ConstructorMethod method(pclass, access, type, name, args);
        ((Class *)pclass)->_addConstructorMethod(method, cb);
    }



__register_property__::__register_property__(__property_base__ *handler, const Class *pclass, const char *type, const char *name, const std::type_info& typeinfo) {
        Property property(pclass, type, name,typeinfo);
        ((Class *)pclass)->_addProperty(property, handler);
    }

std::string MethodBase::getPrefix(const std::type_info &ret_type) const {
	return unmangle(ret_type.name()) + ' ' + getClass().getFullName() + "::" + getName();
    }

std::string StaticMethod::getPrefix(const std::type_info &ret_type) const {
    return std::string("static ") + this->MethodBase::getPrefix(ret_type);
    }

std::string ConstructorMethod::getPrefix(const std::type_info &ret_type) const {
	return getClass().getFullName() + "::" + getName();
    }


bool isCastable(const std::type_info &from_cls, const std::type_info &to_cls, void *objptr )
{
    if (from_cls == to_cls) return true;

    if (from_cls == typeid(void*)) {
	return to_cls == typeid(const void*);
    }

    std::string from_str = from_cls.name();
    std::string to_str = to_cls.name();

    const Class* fc;
    const Class* tc;

    if ((fc = Class::findClassMap(Class::MAP_CLASSNAME, from_str)) != 0) {
    /* test case:
       from is a Class or referrence to Class,
       then
       to must be either a superClass or const superClass
    */
	if ((tc = Class::findClassMap(Class::MAP_CLASSNAME, to_str)) != 0) return tc->isSame(*fc) || tc->isBase(*fc);
	else if ((tc = Class::findClassMap(Class::MAP_CLASSNAME_CONST, to_str)) != 0) return tc->isSame(*fc) || tc->isBase(*fc);
    } else if ((fc = Class::findClassMap(Class::MAP_CLASSNAME_CONST, from_str)) != 0) {
    /* test case:
       from is a const Class,
       then
       to must be either a const superClass
    */
	if ((tc = Class::findClassMap(Class::MAP_CLASSNAME_CONST, to_str)) != 0) return tc->isSame(*fc) || tc->isBase(*fc);
    } else if ((fc = Class::findClassMap(Class::MAP_CLASSNAME_PTR, from_str)) != 0) {
    /* test case:
       from is a Class *,
       then
       to must be either a void*, const void*, superClass *, or const superClass*
    */
	if (to_cls == typeid(void *) || to_cls == typeid(const void *)) return true;
	if ((tc = Class::findClassMap(Class::MAP_CLASSNAME_PTR, to_str)) != 0 || (tc = Class::findClassMap(Class::MAP_CLASSNAME_PTR_CONST, to_str)) != 0) {
	    if (tc->isSame(*fc) || tc->isBase(*fc)) return true;
	    if (objptr != 0) {
		/* now we need to try doing dynamicCasting */
		/* since we know this is a pointer type, so we can cast the parameter to void ** */
		void ** objptrptr = static_cast<void **> (objptr);
		return tc->dynamicCastableFromSuper(*objptrptr, fc);
	    }
	}
    } else if ((fc = Class::findClassMap(Class::MAP_CLASSNAME_PTR_CONST, from_str)) != 0) {
    /* test case:
       from is a const Class *,
       then
       to must be either a const void*, or const superClass*
    */
	if (to_cls == typeid(const void *)) return true;
	if ((tc = Class::findClassMap(Class::MAP_CLASSNAME_PTR_CONST, to_str)) != 0) {
	    if (tc->isSame(*fc) || tc->isBase(*fc)) return true;
	    if (objptr != 0) {
		/* now we know that the type is const CLASS *, type objptr is of type const void ** */
		const void **objptrptr = static_cast<const void **> (objptr);
		return tc->dynamicCastableFromSuper(*objptrptr, fc);
	    }
	}
    }
    return false;
}




/** operator that outputs the access type to the given stream
    @param str stream to output the access to
    @param access access type to output
    @return the given stream
    @exception std::range_error thrown if the access value is invalid
 */
std::ostream &operator << (std::ostream &str, agm::reflection::ACCESS_TYPE access)
{
    switch (access) {
        case agm::reflection::ACCESS_PUBLIC:
            str << "public";
            break;

        case agm::reflection::ACCESS_PROTECTED:
            str << "protected";
            break;

        case agm::reflection::ACCESS_PRIVATE:
            str << "private";
            break;

        default:
            throw std::range_error("access");
    }

    return str;
}

/** operator to print out class information
    @param str stream to output the access to
    @param access access type to output
    @return the given stream
    @exception std::range_error thrown if the access value is invalid
 */
std::ostream &operator << (std::ostream &out, const agm::reflection::Class& pclass) {
	out << "class name = " << pclass.getName() << std::endl;
	out << "full name = " << pclass.getFullName() << std::endl;

	out << "superclass = ";
	if (pclass.hasSuper()) out << pclass.getSuper().getFullName();
	else out << "none";
	out << std::endl;
	
	out << "newInstace " << (pclass.hasNewInstance()?"true":"false") << std::endl;
	out << "object size: " << pclass.getSize() << std::endl;

	out << "constructor:\n";
	const Class::ConstructorList & clist = pclass.getConstructors();
	for (Class::ConstructorList::const_iterator i=clist.begin(); i != clist.end(); i++) {
	    const ConstructorMethod &method = *i;
	    out << "    " << method.getAccess();
	    out << " " << pclass.getName() << method.getArgs()
		<< "     ( " << method.getId() << " )" <<
		std::endl;
	    out << " { Signature: " << method.getSignature() << "}" << std::endl;
	}

	out << "fields:\n";
	for(Class::FieldList::const_iterator itField = pclass.getFields().begin();
	    itField != pclass.getFields().end();
	    ++itField)
	{
	    const Field &field = *itField;
	    out << "    " << field.getAccess() << " " << field.getType() << " " << field.getName() << std::endl;
	}

	out << "static fields:\n";
	for(Class::StaticFieldList::const_iterator itStaticField = pclass.getStaticFields().begin();
	    itStaticField != pclass.getStaticFields().end();
	    ++itStaticField)
	{
	    const StaticField &field = *itStaticField;
	    out << "    " << field.getAccess() << " " << field.getType() << " " << field.getName() << std::endl;
	}

	out << "static methods:\n";
	for(Class::StaticMethodList::const_iterator itMethod = pclass.getStaticMethods().begin();
	    itMethod != pclass.getStaticMethods().end();
	    ++itMethod)
	{
	    const StaticMethod &method = *itMethod;
	    out << "    " << method.getAccess();
	    out << " " << method.getType() << " " << method.getName() << method.getArgs()
		<< "     ( " << method.getId() << " )" <<
		std::endl;
	    out << " { Signature: " << method.getSignature() << "}" << std::endl;
	}

	out << "methods:\n";
	for(Class::MethodList::const_iterator itMethod = pclass.getMethods().begin();
	    itMethod != pclass.getMethods().end();
	    ++itMethod)
	{
	    const Method &method = *itMethod;
	    out << "    " << method.getAccess();
	    if (method.isVirtual()) out << " " << "virtual";
	    out << " " << method.getType() << " " << method.getName() << method.getArgs() 
		<< "     ( " << method.getId() << " )" <<
		std::endl;
	    out << " { Signature: " << method.getSignature() << "}" << std::endl;
	}

	out << "properties:\n";
	for(Class::PropertyList::const_iterator itProperty = pclass.getProperties().begin();
	    itProperty != pclass.getProperties().end();
	    ++itProperty)
	{
	    const Property &property = *itProperty;
	    out << "    " << property.getType() << " " << property.getName() << std::endl;
	}

	out << "\n-----------------------------------------------------------\n";
	return out;
    }



}}

#ifdef _MSC_VER
#pragma warning ( pop )
#endif