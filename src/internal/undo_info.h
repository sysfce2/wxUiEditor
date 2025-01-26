///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#pragma once

#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/stattext.h>

class UndoInfo : public wxDialog
{
public:
    UndoInfo() {}
    UndoInfo(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Undo/Redo stack information",
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr)
    {
        Create(parent, id, title, pos, size, style, name);
    }
    bool Create(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Undo/Redo stack information",
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr);

protected:

    // Event handlers

    void OnInit(wxInitDialogEvent& event);

private:

    // Class member variables

    wxStaticText* m_txt_redo_items;
    wxStaticText* m_txt_redo_memory;
    wxStaticText* m_txt_undo_items;
    wxStaticText* m_txt_undo_memory;
};

// ************* End of generated code ***********
// DO NOT EDIT THIS COMMENT BLOCK!
//
// Code below this comment block will be preserved
// if the code for this class is re-generated.
//
// clang-format on
// ***********************************************
