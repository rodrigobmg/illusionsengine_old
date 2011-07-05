namespace Ill
{
	namespace Core
	{
		template<class T>
		boost::intrusive_ptr<T> Application::GetSubsystem()
		{
			// Find a subsystem that matches the template type
			// Type should be reflective (defines the CLASS(..) macro in the class definition.
			const Class& typeClass = T::getClassStatic();

			iterator iter = m_Subsystems.begin();
			while ( iter != m_Subsystems.end() )
			{
				Subsystem* subsystem = (*iter);
				const Class& subsystemClass = subsystem->getClass();
				if ( subsystemClass.isSame(typeClass) || subsystemClass.isBase(typeClass) )
				{
					return boost::intrusive_ptr<T>( static_cast<T*>(subsystem) );
				}
				++iter;
			}
			// Return an invalid ptr object
			return boost::intrusive_ptr<T>();

		}
	}
}