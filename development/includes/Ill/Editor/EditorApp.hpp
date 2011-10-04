/**
* @file		EditorApp.hpp
* @date 	Apr 16, 2009
* @author 	Jeremiah van Oosten
* 
* @brief 	The main editor application.
*/
#ifndef __Ill_Editor_EditorApp_h__
#define __Ill_Editor_EditorApp_h__

#include <Ill/Core/reflection.hpp>
#include <Ill/Core/Application.fwd.hpp>

using namespace agm::reflection;

namespace Ill
{
	namespace Editor
	{
        class Frame;

		class EditorApp : public wxApp
		{
		public:
			CLASS(EditorApp,NullClass);
			CONSTRUCTOR(public,EditorApp,());

			/**
			 * wxApp interface
			 */
			virtual bool OnInit();
            virtual int  OnExit();

		private:
			// The main frame window for the Editor application
			Frame*		m_pFrame;
            Ill::Core::ApplicationPtr m_App;
		};
	}
}

DECLARE_APP(Ill::Editor::EditorApp);

#endif // __Ill_Editor_EditorApp_h__