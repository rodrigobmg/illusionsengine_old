#ifndef ILL_GAME_GAMEAPPLICATION_FWD_HPP
#define ILL_GAME_GAMEAPPLICATION_FWD_HPP
/**
 * Forward declarations for GameApplication types.
 */

namespace Ill
{
    namespace Game
    {
        class GameApplication;
        //DECLARE_PTR(GameApplication);
        typedef boost::shared_ptr<GameApplication> GameApplicationPtr;
        typedef boost::weak_ptr<GameApplication> GameApplicationWeakPtr;
    }
}

#endif // ILL_GAME_GAMEAPPLICATION_FWD_HPP