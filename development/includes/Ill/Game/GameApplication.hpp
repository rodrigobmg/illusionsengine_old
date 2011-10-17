/**
 * @file: GameApplication.h
 * @date: September 22, 2009
 *
 * The game application base class.
 */

#ifndef ILL_GAME_GAMEAPPLICATION_HPP
#define ILL_GAME_GAMEAPPLICATION_HPP

#include <Ill/Core/Application.hpp>
#include <Ill/Game/GameApplication.fwd.hpp>

namespace Ill
{
    namespace Game
    {
		class GAME_DLL GameApplication : public Ill::Core::Application
        {
        public:
            CLASS( GameApplication, Ill::Core::Application );
            CONSTRUCTOR( GAME_DLL, public, GameApplication, () );  
       };
    }
}

#endif // ILL_GAME_GAMEAPPLICATION_HPP