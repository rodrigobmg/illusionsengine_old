#ifndef ILL_PLUGINS_HORDE3DWINDOW_FWD_HPP
#define ILL_PLUGINS_HORDE3DWINDOW_FWD_HPP

#include <Plugins/Horde3DPlugin/Horde3DPluginDefines.hpp>

NAMESPACE_H3D_BEGIN

// DECLARE_PTR( Horde3DWindow );
class Horde3DWindow;
typedef boost::shared_ptr<Horde3DWindow> Horde3DWindowPtr;
typedef boost::weak_ptr<Horde3DWindow> Horde3DWindowWeakPtr;

NAMESPACE_H3D_END

#endif // ILL_PLUGINS_HORDE3DWINDOW_FWD_HPP