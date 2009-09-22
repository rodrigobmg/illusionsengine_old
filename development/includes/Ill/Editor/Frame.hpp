/**
* @file		Frame.hpp
* @date 	Apr 16, 2009
* @author 	Jeremiah van Oosten
* 
* @brief	A window frame that can be used to show menu items, tool bars, status
* bars, and other GUI controls.
*/

#include <Ill/Editor/EditorCommands.hpp>

namespace Ill
{
	namespace Editor
	{
		class Frame : public wxFrame
		{
		public:
			Frame( const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize );

			virtual wxMenuBar* CreateMenuBar();

			/**
			 * Event handler for the quit command.
			 */
			void OnQuit(wxCommandEvent& event);
			/**
			 * Event handler for the about command.
			 */
			void OnAbout(wxCommandEvent& event);

		private:
			DECLARE_EVENT_TABLE();

		};
	}
}