/**
* @file		Frame.cpp
* @date 	Apr 16, 2009
* @author 	Jeremiah van Oosten
* 
* @brief 	The main editor frame.
*/
#include <Ill/Editor/PrecompiledHeader.hpp>
#include <Ill/Editor/Frame.hpp>

namespace Ill
{
	namespace Editor
	{
		BEGIN_EVENT_TABLE(Frame, wxFrame)
			EVT_MENU(ECID_Quit,  Frame::OnQuit)
			EVT_MENU(ECID_About, Frame::OnAbout)
		END_EVENT_TABLE()

		Frame::Frame( const wxString& title, const wxPoint& pos, const wxSize& size )
		: wxFrame( NULL, -1, title, pos, size )
		{
			wxMenuBar* menuBar = CreateMenuBar();
			wxASSERT_MSG( menuBar != NULL, TEXT("MenuBar is NULL\n") );

			SetMenuBar( menuBar );

			CreateStatusBar();

			SetStatusText( TEXT("Illusions Engine Editor (c) 2009") );
		}

		wxMenuBar* Frame::CreateMenuBar()
		{
			wxMenu *menuFile = new wxMenu;

			menuFile->Append( ECID_About, TEXT("&About...") );
			menuFile->AppendSeparator();
			menuFile->Append( ECID_Quit, TEXT("E&xit") );

			wxMenuBar *menuBar = new wxMenuBar;
			menuBar->Append( menuFile, TEXT("&File") );

			return menuBar;
		}

		void Frame::OnQuit(wxCommandEvent& WXUNUSED(event) )
		{
			Close( true );
		}

		void Frame::OnAbout(wxCommandEvent& WXUNUSED(event) )
		{
			wxMessageBox( TEXT("Illusions Engine Editor (c) 2009"),
				TEXT("Illusions Engine Editor"), wxOK | wxICON_INFORMATION );

		}

	}
}