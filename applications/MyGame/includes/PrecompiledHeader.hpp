#ifndef MYGAME_PRECOMPILED_HEADER_HPP
#define MYGAME_PRECOMPILED_HEADER_HPP

#include <Ill/System/System.hpp>
#include <Ill/System/Graphics/Graphics.hpp>

#if ILL_PLATFORM == ILL_PLATFORM_WIN32
#  define WIN32_LEAN_AND_MEAN
#  define NOMINMAX // required to stop windows.h messing up std::min
#  include <windows.h>
#endif

// STL
#include <iostream>
#include <string>

#endif // MYGAME_PRECOMPILED_HEADER_HPP