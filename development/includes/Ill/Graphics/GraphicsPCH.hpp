/**
 * @file
 */

#ifndef ILL_GRAPHICS_PCH_HPP
#define ILL_GRAPHICS_PCH_HPP

#pragma warning( push )
#pragma warning( disable : 4244 ) // Argument conversion - possible loss of data.

#include <iostream>
#include <iomanip>
#include <string>
#include <locale>
#include <vector>
#include <map>
#include <algorithm>

#pragma warning( pop )

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// Boost includes
#include <Ill/Core/BoostInclude.hpp>
// GLM
#include <Ill/Core/GlmInclude.hpp>

#include <Ill/Core/CorePlatform.hpp>
#include <Ill/Graphics/GraphicsExports.hpp>

#endif // ILL_GRAPHICS_PCH_HPP
