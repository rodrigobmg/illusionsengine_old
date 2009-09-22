#include <Ill/System/PrecompiledHeader.hpp>
#include <Ill/System/PropertyMap.hpp>

namespace Ill
{
	namespace System
	{
		PropertyMap::PropertyMap()
		{}

		PropertyMap::~PropertyMap()
		{
			Clear();
		}

        bool PropertyMap::GetValue( const std::string& key, boost::any& value ) const
        {
            const_iterator iter = m_Properties.find( key );
            if ( iter != m_Properties.end() )
            {
                value = iter->second;
                return true;
            }

            return false;
        }

		void PropertyMap::Clear()
		{
			m_Properties.clear();
		}
	}
}