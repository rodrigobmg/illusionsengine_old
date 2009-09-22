/**
* @file		EditorApp.hpp
* @date 	Apr 16, 2009
* @author 	Jeremiah van Oosten
* 
* @brief 	The main editor application.
*/
#ifndef __Ill_Editor_EditorApp_h__
#define __Ill_Editor_EditorApp_h__

#include <Ill/System/Application.hpp>
#include <Ill/Editor/Frame.hpp>

namespace Ill
{
	namespace Editor
	{
		class EditorApp : public System::Application, public wxApp
		{
		public:
			CLASS(EditorApp,System::Application);
			CONSTRUCTOR(public,EditorApp,());

			/**
			 * wxApp interface
			 */
			virtual bool OnInit();

		private:
			// The main frame window for the Editor application
			Frame*		m_pFrame;

		};
	}
}

#endif // __Ill_Editor_EditorApp_h__