////////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor -- see https://github.com/KeyWorksRW/wxUiEditor/
//
// DO NOT EDIT THIS FILE! Your changes will be lost if it is re-generated!
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/bitmap.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/listbox.h>

class DbgCodeDiffBase : public wxDialog
{
public:
    DbgCodeDiffBase(wxWindow* parent);

protected:

    // Class member variables

    wxButton* m_btn;
    wxListBox* m_list_changes;

    // Virtual event handlers -- override them in your derived class

    virtual void OnInit(wxInitDialogEvent& event) { event.Skip(); }
    virtual void OnWinMerge(wxCommandEvent& event) { event.Skip(); }
};
