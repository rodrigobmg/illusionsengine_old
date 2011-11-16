/**
 * @file
 */

#ifndef ILL_CORE_PRECOMPILED_HEADER_HPP
#define ILL_CORE_PRECOMPILED_HEADER_HPP

// STL
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

// GLM math library.
#include <Ill/Core/GlmInclude.hpp>

// Boost specific headers should go in BoostInclude.h
#include <Ill/Core/BoostInclude.hpp>

#include <Ill/Core/CorePlatform.hpp>
#include <Ill/Core/CoreUtils.hpp>

#endif // ILL_CORE_PRECOMPILED_HEADER_HPP
