namespace Ill
{
	namespace Core
	{
		template<class T>
		boost::weak_ptr<T> Application::GetSubsystem()
		{
			// Find a subsystem that matches the template type
			// Type should be reflective (defines the CLASS(..) macro in the class definition.
			const Class& typeClass = T::getClassStatic();

            SubsystemList::iterator iter = m_Subsystems.begin();
			while ( iter != m_Subsystems.end() )
			{
                SubsystemPtr subsystem = (*iter);
				const Class& subsystemClass = subsystem->getClass();
				if ( subsystemClass.isSame(typeClass) /*|| subsystemClass.isSuper(typeClass) */ )
				{
                    return boost::shared_dynamic_cast<T>( subsystem );
				}
				++iter;
			}
			// Return an invalid ptr object
			return boost::weak_ptr<T>();

		}
	}
}