/**
* @file		Frame.cpp
* @date 	Apr 16, 2009
* @author 	Jeremiah van Oosten
* 
* @brief 	The main editor frame.
*/
#include <Ill/Editor/EditorPCH.hpp>
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
		: wxFrame( NULL, wxID_ANY, title, pos, size )
		{
            m_AUImanager.SetManagedWindow( this );

            wxTextCtrl* text1 = new wxTextCtrl( this, -1, wxT("Pane 1 - Sample Text"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTE_MULTILINE );
            wxTextCtrl* text2 = new wxTextCtrl( this, -1, wxT("Pane 2 - Sample Text"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTE_MULTILINE );
            wxTextCtrl* text3 = new wxTextCtrl( this, -1, wxT("Pane 3 - Sample Text"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTE_MULTILINE );

            m_AUImanager.AddPane( text1, wxLEFT, wxT("Pane Number One") );
            m_AUImanager.AddPane( text2, wxBOTTOM, wxT("Pane Number Two") );
            m_AUImanager.AddPane( text3, wxCENTER );

            m_AUImanager.Update();

			wxMenuBar* menuBar = CreateMenuBar();
			wxASSERT_MSG( menuBar != NULL, wxT("MenuBar is NULL\n") );

			SetMenuBar( menuBar );

			CreateStatusBar();

			SetStatusText( wxT("Illusions Engine Editor (c) 2011") );
		}

        Frame::~Frame()
        {
            m_AUImanager.UnInit();
        }

		wxMenuBar* Frame::CreateMenuBar()
		{
			wxMenu* menuFile = new wxMenu;
            wxMenu* menuHelp = new wxMenu;

            menuFile->Append( ECID_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program") );
			menuHelp->Append( ECID_About, wxT("&About...\tF1"), wxT("Show about dialog") );

			wxMenuBar *menuBar = new wxMenuBar;
			menuBar->Append( menuFile, wxT("&File") );
            menuBar->Append( menuHelp, wxT("&Help") );

			return menuBar;
		}

		void Frame::OnQuit(wxCommandEvent& WXUNUSED(event) )
		{
			Close( true );
		}

		void Frame::OnAbout(wxCommandEvent& WXUNUSED(event) )
		{
			wxMessageBox( TEXT("Illusions Engine Editor (c) 2011"),
				TEXT("Illusions Engine Editor"), wxOK | wxICON_INFORMATION );

		}

	}
}