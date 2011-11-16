#ifndef ILL_GAME_ELAPSEDTIME_HPP
#define ILL_GAME_ELAPSEDTIME_HPP

namespace Ill
{
    namespace Game
    {
    class ElapsedTime
    {
    public:
        ElapsedTime( float maxTimeStep = 0.03333f );
        float GetElapsedTime() const;

    private:
        float m_fMaxTimeStep;
        mutable float m_fPrevious;
    };

    }
}

#endif // ILL_GAME_ELAPSEDTIME_HPP