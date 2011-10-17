#ifndef ILL_OGREPLUGIN_PCH_HPP
#define ILL_OGREPLUGIN_PCH_HPP

// STL includes
#include <iostream>

// Try to disable the plethora of warnings that Ogre produces.
#pragma warning( push )
#pragma warning( disable : 4100 4127 4245 )
// #include <Ogre.h>
#pragma warning( pop )

#include <Ill/Core/BoostInclude.hpp>
#include <Ill/Core/CorePlatform.hpp>
#include <Ill/Graphics/GraphicsExports.hpp>

#include <Plugins/OgrePlugin/OgrePluginExports.hpp>

#endif // ILL_OGREPLUGIN_PCH_HPP
