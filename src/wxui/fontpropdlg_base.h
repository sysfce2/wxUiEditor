///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#pragma once

#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/statbox.h>
#include <wx/stattext.h>

class FontPropDlgBase : public wxDialog
{
public:
    FontPropDlgBase() {}
    FontPropDlgBase(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Font Property",
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr)
    {
        Create(parent, id, title, pos, size, style, name);
    }
    bool Create(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Font Property", const wxPoint& pos =
        wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr);

protected:

    // Virtual event handlers -- override them in your derived class

    virtual void OnCustomRadio(wxCommandEvent& event) { event.Skip(); }
    virtual void OnEditPointSize(wxCommandEvent& event) { event.Skip(); }
    virtual void OnFacename(wxCommandEvent& event) { event.Skip(); }
    virtual void OnFamily(wxCommandEvent& event) { event.Skip(); }
    virtual void OnInit(wxInitDialogEvent& event) { event.Skip(); }
    virtual void OnOK(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPointSize(wxSpinDoubleEvent& event) { event.Skip(); }
    virtual void OnStrikeThrough(wxCommandEvent& event) { event.Skip(); }
    virtual void OnStyle(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSymbolSize(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSystemRadio(wxCommandEvent& event) { event.Skip(); }
    virtual void OnUnderlined(wxCommandEvent& event) { event.Skip(); }
    virtual void OnWeight(wxCommandEvent& event) { event.Skip(); }

    // Class member variables

    wxCheckBox* m_checkCustomStrikeThrough;
    wxCheckBox* m_checkCustomUnderlined;
    wxCheckBox* m_checkSystemStrikeThrough;
    wxCheckBox* m_checkSystemUnderlined;
    wxChoice* m_comboCustomStyles;
    wxChoice* m_comboCustomWeight;
    wxChoice* m_comboFamily;
    wxChoice* m_comboSymbolSize;
    wxChoice* m_comboSystemStyles;
    wxChoice* m_comboSystemWeight;
    wxComboBox* m_comboFacenames;
    wxRadioButton* m_radioCustom;
    wxStaticBoxSizer* m_custom_box;
    wxRadioButton* m_radioSystem;
    wxStaticBoxSizer* m_system_box;
    wxSpinCtrlDouble* m_spinCustomPointSize;
    wxStaticText* m_staticCustomSample;
    wxStaticText* m_staticSystemSample;
};

// ************* End of generated code ***********
// DO NOT EDIT THIS COMMENT BLOCK!
//
// Code below this comment block will be preserved
// if the code for this class is re-generated.
//
// clang-format on
// ***********************************************
