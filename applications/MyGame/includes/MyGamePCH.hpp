#ifndef MYGAME_PCH_HPP
#define MYGAME_PCH_HPP

// STL
#include <iostream>
#include <string>
#include <algorithm>

// SDL
#include <SDL.h>

// Boost includes
#include <Ill/Core/BoostInclude.hpp>
// GLM
#include <Ill/Core/GlmInclude.hpp>

#include <Ill/Core/Core.hpp>

// Undefine the CreateWindow macro from the Windows headers
// so I can declare a member function in the GraphicsWindow class called CreateWindow.
#ifdef CreateWindow
#undef CreateWindow
#endif

#include <Ill/Graphics/Graphics.hpp>
#include <Ill/Game/Game.hpp>

#endif // MYGAME_PCH_HPP