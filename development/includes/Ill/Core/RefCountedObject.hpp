#ifndef ILL_CORE_REFCOUNTEDOBJECT_HPP
#define ILL_CORE_REFCOUNTEDOBJECT_HPP

#include <boost/intrusive_ptr.hpp>
#include <Ill/Core/NoCopyObject.hpp>

template< class T >
inline void intrusive_ptr_add_ref( T* p )
{
	p->AddRef();
}

template< class T >
inline void intrusive_ptr_release( T* p )
{
	p->Release();
	if ( p->GetRefCount() == 0 )
	{
		delete p;
	}
}

namespace Ill
{
	namespace Core
	{
		class _IllExport RefCountedObject : public NoCopyObject
		{
		public:
			CLASS(RefCountedObject,NoCopyObject);

			CONSTRUCTOR(public,RefCountedObject,())
				: m_iRefCount( 0 ) 
			{}

			virtual ~RefCountedObject() 
			{
				BOOST_ASSERT( m_iRefCount == 0 );
			}

			void AddRef()
			{
				++m_iRefCount;  // To make this thread safe, access to the RefCount member should be guarded!
			}

			void Release()
			{
				--m_iRefCount;  // To make this thread safe, access to the RefCount member should be guarded!
			}

			int GetRefCount() const
			{
				return m_iRefCount;
			}

		private:
			int m_iRefCount;
		};

		typedef boost::intrusive_ptr<RefCountedObject> RefCountedObjectPtr;
	}
}

#endif // ILL_CORE_REFCOUNTEDOBJECT_HPP