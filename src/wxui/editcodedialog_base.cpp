///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#include <wx/button.h>
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/sizer.h>

#include "editcodedialog_base.h"

bool EditCodeDialogBase::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, pos, size, style, name))
        return false;

    auto* parent_sizer = new wxBoxSizer(wxVERTICAL);

    m_stc = new wxStyledTextCtrl(this);
    {
        m_stc->SetLexer(wxSTC_LEX_CPP);
        m_stc->SetEOLMode(wxSTC_EOL_LF);
        m_stc->SetWrapMode(wxSTC_WRAP_WORD);
        m_stc->SetWrapVisualFlags(wxSTC_WRAPVISUALFLAG_END);
        m_stc->SetWrapIndentMode(wxSTC_WRAPINDENT_INDENT);
        m_stc->SetMultipleSelection(wxSTC_MULTIPASTE_EACH);
        m_stc->SetMultiPaste(wxSTC_MULTIPASTE_EACH);
        m_stc->SetAdditionalSelectionTyping(true);
        m_stc->SetAdditionalCaretsBlink(true);
        m_stc->SetMarginLeft(wxSizerFlags::GetDefaultBorder());
        m_stc->SetMarginRight(wxSizerFlags::GetDefaultBorder());
        m_stc->SetMarginWidth(1, 0);
        m_stc->SetMarginWidth(0, 16);
        m_stc->SetMarginType(0, wxSTC_MARGIN_SYMBOL);
        m_stc->SetMarginMask(0, ~wxSTC_MASK_FOLDERS);
        m_stc->SetMarginSensitive(0, false);
        m_stc->SetIndentationGuides(wxSTC_IV_LOOKFORWARD);
        m_stc->SetUseTabs(false);
        m_stc->SetBackSpaceUnIndents(true);
    }
    parent_sizer->Add(m_stc, wxSizerFlags(1).Expand().DoubleBorder(wxALL));

    auto* stdBtn_2 = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    parent_sizer->Add(CreateSeparatedSizer(stdBtn_2), wxSizerFlags().Expand().Border(wxALL));

    if (pos != wxDefaultPosition)
    {
        SetPosition(FromDIP(pos));
    }
    if (size == wxDefaultSize)
    {
        SetSizerAndFit(parent_sizer);
    }
    else
    {
        SetSizer(parent_sizer);
        if (size.x == wxDefaultCoord || size.y == wxDefaultCoord)
        {
            Fit();
        }
        SetSize(FromDIP(size));
        Layout();
    }
    Centre(wxBOTH);

    wxPersistentRegisterAndRestore(this, "EditCodeDialogBase");

    // Event handlers
    Bind(wxEVT_BUTTON, &EditCodeDialogBase::OnOK, this, wxID_OK);
    Bind(wxEVT_INIT_DIALOG, &EditCodeDialogBase::OnInit, this);
    m_stc->Bind(wxEVT_STC_CHANGE, &EditCodeDialogBase::OnChange, this);

    return true;
}

// ************* End of generated code ***********
// DO NOT EDIT THIS COMMENT BLOCK!
//
// Code below this comment block will be preserved
// if the code for this class is re-generated.
//
// clang-format on
// ***********************************************
