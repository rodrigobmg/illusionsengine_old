/**
 * @file: GameApplication.h
 * @date: September 22, 2009
 *
 * The game application base class.
 */

#ifndef ILL_GAME_GAMEAPPLICATION_HEADER_HPP
#define ILL_GAME_GAMEAPPLICATION_HEADER_HPP

#include <Ill/System/Application.hpp>

namespace Ill
{
    namespace Game
    {
        class GameApplication : public Ill::System::Application
        {
        public:
            CLASS( GameApplication, Ill::System::Application );
            CONSTRUCTOR(public,GameApplication,());
            
       };

        typedef boost::intrusive_ptr<GameApplication> GameApplicationPtr;
    }
}

#endif // ILL_GAME_GAMEAPPLICATION_HEADER_HPP