///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#pragma once

#include <wx/bitmap.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/listbox.h>
#include <wx/radiobut.h>

class CodeCompare : public wxDialog
{
public:
    CodeCompare() {}
    CodeCompare(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Compare Code Generation",
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr)
    {
        Create(parent, id, title, pos, size, style, name);
    }
    bool Create(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Compare Code Generation",
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr);

    ~CodeCompare();

protected:

    // Event handlers

    void OnCPlusPlus(wxCommandEvent& event);
    void OnInit(wxInitDialogEvent& event);
    void OnPython(wxCommandEvent& event);
    void OnRuby(wxCommandEvent& event);
    void OnWinMerge(wxCommandEvent& event);

private:

    // Class member variables

    wxButton* m_btn;
    wxListBox* m_list_changes;
    wxRadioButton* m_radio_cplusplus;
    wxRadioButton* m_radio_python;
    wxRadioButton* m_radio_ruby;

    std::vector<tt_string> m_class_list;
};

// ************* End of generated code ***********
// DO NOT EDIT THIS COMMENT BLOCK!
//
// Code below this comment block will be preserved
// if the code for this class is re-generated.
//
// clang-format on
// ***********************************************
