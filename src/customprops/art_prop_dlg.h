///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#pragma once

#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/listctrl.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>

#include "img_props.h"

class ArtBrowserDialog : public wxDialog
{
public:
    ArtBrowserDialog() {}
    ArtBrowserDialog(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Art Provider Image",
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr)
    {
        Create(parent, id, title, pos, size, style, name);
    }
    bool Create(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Art Provider Image",
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr);

protected:

    // Event handlers

    void OnChooseClient(wxCommandEvent& event);
    void OnInit(wxInitDialogEvent& event);
    void OnSelectItem(wxListEvent& event);

private:

    // Class member variables

    wxChoice* m_choice_client;
    wxListView* m_list;
    wxStaticBitmap* m_canvas;
    wxStaticText* m_text;

// ************* End of generated code ***********
// DO NOT EDIT THIS COMMENT BLOCK!
//
// Code below this comment block will be preserved
// if the code for this class is re-generated.
//
// ***********************************************

public:
    ArtBrowserDialog(wxWindow* parent, const ImageProperties& img_props);

    wxString GetResults();

protected:
    void ChangeClient();

private:
    wxString m_client;
    tt_string m_org_id;
    const char* m_id;
};
