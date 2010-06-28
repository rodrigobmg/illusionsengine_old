namespace Ill
{
	namespace System
	{
		template <typename T>
		void PropertyMap::AddValue( const std::string& key, const T& value )
		{
			iterator iter = m_Properties.find( key );
			if ( iter != m_Properties.end() )
			{	// Replace the current value
				boost::any& any = iter->second;
				any = boost::any(value);
			}
			else
			{
				m_Properties.insert( map::value_type(key, boost::any(value) ) );
			}
		}

		template <typename T>
		bool PropertyMap::GetValue( const std::string& key, T& value ) const
		{
			const_iterator iter = m_Properties.find( key );
			if ( iter != m_Properties.end() )
			{
				const boost::any& any = iter->second;
				try 
				{
					value = boost::any_cast<T>(any);
					return true;
				}
				catch ( const boost::bad_any_cast& )
				{
					std::cerr << "Could not convert value with key \"" << key << "\" from type <" << any.type().name() << "> to type <" << typeid(T).name() << ">\n";
					return false;
				}
			}
			else
			{
				std::cerr << "Could not find key: \"" << key << "\"\n";
			}

			return false;
		}
	}
}