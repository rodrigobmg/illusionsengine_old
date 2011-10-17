/**
* @file		EditorCommands.hpp
* @date 	Apr 16, 2009
* @author 	Jeremiah van Oosten
* 
* @brief 	The event IDs used in the editor must be unique.  Define unique event 
* ID's in this file.
*/
#ifndef ILL_EDITOR_EDITORCOMMANDS_HPP
#define ILL_EDITOR_EDITORCOMMANDS_HPP

namespace Ill
{
	namespace Editor
	{
		enum EditorCommands
		{
			  ECID_Quit = 1
			, ECID_About
		};
	}
}

#endif