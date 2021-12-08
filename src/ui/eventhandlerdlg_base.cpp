////////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor -- see https://github.com/KeyWorksRW/wxUiEditor/
//
// DO NOT EDIT THIS FILE! Your changes will be lost if it is re-generated!
////////////////////////////////////////////////////////////////////////////////

#include <wx/button.h>

#include "eventhandlerdlg_base.h"

bool EventHandlerDlgBase::Create(wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint&pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, pos, size, style, name))
        return false;

    auto parent_sizer = new wxBoxSizer(wxVERTICAL);

    auto box_sizer = new wxBoxSizer(wxVERTICAL);
    parent_sizer->Add(box_sizer, wxSizerFlags().Expand().Border(wxALL));

    m_static_bind_text = new wxStaticText(this, wxID_ANY, "...");
    m_static_bind_text->Wrap(400);
    box_sizer->Add(m_static_bind_text, wxSizerFlags().Border(wxALL));

    box_sizer->AddSpacer(10 + wxSizerFlags::GetDefaultBorder());

    m_radio_use_function = new wxRadioButton(this, wxID_ANY, "Use function");
    m_function_box = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, m_radio_use_function), wxVERTICAL);
    box_sizer->Add(m_function_box, wxSizerFlags().Expand().Border(wxALL));

    m_text_function = new wxTextCtrl(m_function_box->GetStaticBox(), wxID_ANY, wxEmptyString);
    m_function_box->Add(m_text_function, wxSizerFlags().Expand().Border(wxALL));

    box_sizer->AddSpacer(10 + wxSizerFlags::GetDefaultBorder());

    m_radio_use_lambda = new wxRadioButton(this, wxID_ANY, "Use lambda");
    m_lambda_box = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, m_radio_use_lambda), wxVERTICAL);
    box_sizer->Add(m_lambda_box, wxSizerFlags().Expand().Border(wxALL));

    auto box_sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    m_lambda_box->Add(box_sizer_2, wxSizerFlags().Border(wxALL));

    m_check_capture_this = new wxCheckBox(m_lambda_box->GetStaticBox(), wxID_ANY, "&Capture this");
    box_sizer_2->Add(m_check_capture_this, wxSizerFlags().Border(wxALL));

    m_check_include_event = new wxCheckBox(m_lambda_box->GetStaticBox(), wxID_ANY, "&Include event parameter");
    box_sizer_2->Add(m_check_include_event, wxSizerFlags().Border(wxALL));

    auto staticText = new wxStaticText(m_lambda_box->GetStaticBox(), wxID_ANY, "Lambda body:");
    m_lambda_box->Add(staticText, wxSizerFlags().Border(wxALL));

    m_stc = new wxStyledTextCtrl(m_lambda_box->GetStaticBox(), wxID_ANY);
    {
        m_stc->SetProperty("fold", "1");
        m_stc->SetMarginType(1, wxSTC_MARGIN_SYMBOL);
        m_stc->SetMarginMask(1, wxSTC_MASK_FOLDERS);
        m_stc->SetMarginWidth(1, 16);
        m_stc->SetMarginSensitive(1, true);
        m_stc->SetFoldFlags(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);
        m_stc->SetMarginWidth(0, 0);
        m_stc->SetUseTabs(false);
        m_stc->SetTabWidth(4);
        m_stc->SetBackSpaceUnIndents(true);
    }
    m_stc->SetInitialSize(ConvertPixelsToDialog(
        wxSize(600 > GetBestSize().x ? 600 : -1, 400 > GetBestSize().y ? 400 : -1)));
    m_lambda_box->Add(m_stc, wxSizerFlags().DoubleBorder(wxALL));

    parent_sizer->AddSpacer(10 + wxSizerFlags::GetDefaultBorder());

    auto stdBtn = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    parent_sizer->Add(CreateSeparatedSizer(stdBtn), wxSizerFlags().Expand().Border(wxALL));

    SetSizerAndFit(parent_sizer);
    Centre(wxBOTH);

    // Event handlers
    Bind(wxEVT_INIT_DIALOG, &EventHandlerDlgBase::OnInit, this);
    m_radio_use_function->Bind(wxEVT_RADIOBUTTON, &EventHandlerDlgBase::OnUseFunction, this);
    m_text_function->Bind(wxEVT_TEXT, &EventHandlerDlgBase::OnFunctionText, this);
    m_radio_use_lambda->Bind(wxEVT_RADIOBUTTON, &EventHandlerDlgBase::OnUseLambda, this);
    m_check_capture_this->Bind(wxEVT_CHECKBOX, &EventHandlerDlgBase::OnCapture, this);
    m_check_include_event->Bind(wxEVT_CHECKBOX, &EventHandlerDlgBase::OnIncludeEvent, this);
    m_stc->Bind(wxEVT_STC_CHANGE, &EventHandlerDlgBase::OnChange, this);
    Bind(wxEVT_BUTTON, &EventHandlerDlgBase::OnOK, this, wxID_OK);

    return true;
}
