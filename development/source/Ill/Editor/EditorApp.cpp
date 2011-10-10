#include <Ill/Editor/EditorPCH.hpp>
#include <Ill/Editor/Frame.hpp>
#include <Ill/Core/Application.hpp>
#include <Ill/Editor/EditorApp.hpp>

namespace Ill
{
	namespace Editor
	{
		EditorApp::EditorApp()
		{
            // This seems to be the only place I can call this since wxWidgets doesn't really expose
            // an entry point.
            // NOTE: It does, but for the sake of platform-independence, I will just all wxWidgets
            // to define the entry point.
           
            // Instantiate the core types to allow the reflection system to register the class types.
            Ill::Core::InstantiateTypes();
		}

		bool EditorApp::OnInit()
		{
            m_App = Ill::Core::ApplicationPtr( new Ill::Core::Application() );
            m_App->Initialize();
            // TODO: Read configuration data from a file.
            m_App->StartUp( Ill::Core::PropertyMap() );

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
            m_App->Terminiate();
            m_App.reset();
            return wxApp::OnExit();
        }
	}
}