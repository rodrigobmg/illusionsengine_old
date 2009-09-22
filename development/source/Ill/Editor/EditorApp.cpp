#include <Ill/Editor/PrecompiledHeader.hpp>
#include <Ill/Editor/EditorApp.hpp>

namespace Ill
{
	namespace Editor
	{
		EditorApp::EditorApp()
		{

		}

		bool EditorApp::OnInit()
		{
			// TODO: Save the position and size of the frame when it was closed so we 
			// can restore it when we open the editor again.
			// TODO: The game name should be stored somewhere (property bag?)
			m_pFrame = new Frame( TEXT("GameNameEditor"), wxPoint(50,50),wxSize(450,350) );
			BOOST_ASSERT( m_pFrame != NULL );

			m_pFrame->Show();
			SetTopWindow( m_pFrame );

			return true;
		}
	}
}