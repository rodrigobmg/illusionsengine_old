#include <Ill/Game/GamePCH.hpp>
#include <Ill/Game/ElapsedTime.hpp>


namespace Ill
{
    namespace Game
    {

        ElapsedTime::ElapsedTime( float maxTimeStep /* = 0.03333f */ )
            : m_fMaxTimeStep( maxTimeStep )
            , m_fPrevious ( std::clock() / (float)CLOCKS_PER_SEC )
        {}

        float ElapsedTime::GetElapsedTime() const
        {
            float fCurrentTime = std::clock() / (float)CLOCKS_PER_SEC;
            float fDeltaTime = fCurrentTime - m_fPrevious;
            m_fPrevious = fCurrentTime;

            // Clamp to the max time step
            fDeltaTime = min( fDeltaTime, m_fMaxTimeStep );

            return fDeltaTime;
        }

    }
}
