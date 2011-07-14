#include <Ill/Editor/EditorPCH.hpp>
#include <Ill/Editor/Frame.hpp>

#include <Ill/Editor/EditorApp.hpp>

namespace Ill
{
	namespace Editor
	{
		EditorApp::EditorApp()
		{
            // This seems to be the only place I can call this since wxWidgets doesn't really expose
            // an entry point.
            Ill::Core::InstantiateTypes();
		}

		bool EditorApp::OnInit()
		{
            Super::Initialize();
            Super::StartUp( Ill::Core::PropertyMap() );

			// TODO: Save the position and size of the frame when it was closed so we 
			// can restore it when we open the editor again.
			// TODO: The game name should be stored somewhere (property bag?)
			m_pFrame = new Frame( TEXT("GameNameEditor"), wxDefaultPosition, wxDefaultSize );
			BOOST_ASSERT( m_pFrame != NULL );

			m_pFrame->Show();
			SetTopWindow( m_pFrame );

			return true;
		}

        int EditorApp::OnExit()
        {
            Super::Terminiate();

            return wxApp::OnExit();
        }
	}
}