#ifndef MYGAME_PRECOMPILED_HEADER_HPP
#define MYGAME_PRECOMPILED_HEADER_HPP

// STL
#include <iostream>
#include <string>

// Boost
#include <Ill/Core/BoostInclude.hpp>

#include <Ill/Core/Core.hpp>
#include <Ill/Graphics/Graphics.hpp>

#if ILL_PLATFORM == ILL_PLATFORM_WIN32
#  define WIN32_LEAN_AND_MEAN
#  define NOMINMAX // required to stop windows.h messing up std::min
#  include <windows.h>
#endif

#endif // MYGAME_PRECOMPILED_HEADER_HPP