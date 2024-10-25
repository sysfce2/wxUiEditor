///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/valgen.h>

#include "code_preference_dlg.h"

bool CodePreferenceDlg::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, pos, size, style, name))
        return false;

    auto* dlg_sizer = new wxBoxSizer(wxVERTICAL);

    auto* staticText = new wxStaticText(this, wxID_ANY,
        "Choose the code you prefer to generate. This will set the project\'s initial code preference property (which you can change at any time).");
    staticText->Wrap(350);
    dlg_sizer->Add(staticText, wxSizerFlags().Border(wxALL));

    auto* grid_sizer = new wxGridSizer(3, 0, 0);

    m_radioBtn_CPP = new wxRadioButton(this, wxID_ANY, "&C++", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    m_radioBtn_CPP->SetValue(true);
    m_radioBtn_CPP->SetValidator(wxGenericValidator(&m_gen_cpp_code));
    grid_sizer->Add(m_radioBtn_CPP, wxSizerFlags().Border(wxALL));

    m_radioBtn_Python = new wxRadioButton(this, wxID_ANY, "&Python");
    m_radioBtn_Python->SetValidator(wxGenericValidator(&m_gen_python_code));
    grid_sizer->Add(m_radioBtn_Python, wxSizerFlags().Border(wxALL));

    auto* m_radioBtn_Ruby = new wxRadioButton(this, wxID_ANY, "&Ruby");
    m_radioBtn_Ruby->SetValidator(wxGenericValidator(&m_gen_ruby_code));
    grid_sizer->Add(m_radioBtn_Ruby, wxSizerFlags().Border(wxALL));

    m_radioBtn_Fortran = new wxRadioButton(this, wxID_ANY, "&Fortran");
    m_radioBtn_Fortran->SetValidator(wxGenericValidator(&m_gen_fortran_code));
    grid_sizer->Add(m_radioBtn_Fortran, wxSizerFlags().Border(wxALL));

    m_radioBtn_Haskell = new wxRadioButton(this, wxID_ANY, "&Haskell");
    m_radioBtn_Haskell->SetValidator(wxGenericValidator(&m_gen_haskell_code));
    grid_sizer->Add(m_radioBtn_Haskell, wxSizerFlags().Border(wxALL));

    m_radioBtn_Lua = new wxRadioButton(this, wxID_ANY, "&Lua");
    m_radioBtn_Lua->SetValidator(wxGenericValidator(&m_gen_lua_code));
    grid_sizer->Add(m_radioBtn_Lua, wxSizerFlags().Border(wxALL));

    m_radioBtn_Perl = new wxRadioButton(this, wxID_ANY, "P&erl");
    m_radioBtn_Perl->SetValidator(wxGenericValidator(&m_gen_perl_code));
    grid_sizer->Add(m_radioBtn_Perl, wxSizerFlags().Border(wxALL));

    m_radioBtn_Rust = new wxRadioButton(this, wxID_ANY, "R&ust");
    m_radioBtn_Rust->SetValidator(wxGenericValidator(&m_gen_rust_code));
    grid_sizer->Add(m_radioBtn_Rust, wxSizerFlags().Border(wxALL));

    m_radioBtn_XRC = new wxRadioButton(this, wxID_ANY, "&XRC");
    m_radioBtn_XRC->SetValidator(wxGenericValidator(&m_gen_xrc_code));
    grid_sizer->Add(m_radioBtn_XRC, wxSizerFlags().Border(wxALL));

    dlg_sizer->Add(grid_sizer, wxSizerFlags().Center().Border(wxALL));

    auto* stdBtn = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    dlg_sizer->Add(CreateSeparatedSizer(stdBtn), wxSizerFlags().Expand().Border(wxALL));

    if (pos != wxDefaultPosition)
    {
        SetPosition(FromDIP(pos));
    }
    if (size == wxDefaultSize)
    {
        SetSizerAndFit(dlg_sizer);
    }
    else
    {
        SetSizer(dlg_sizer);
        if (size.x == wxDefaultCoord || size.y == wxDefaultCoord)
        {
            Fit();
        }
        SetSize(FromDIP(size));
        Layout();
    }
    Centre(wxBOTH);

    // Event handlers
    Bind(wxEVT_INIT_DIALOG, &CodePreferenceDlg::OnInit, this);

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

/////////////////// Non-generated Copyright/License Info ////////////////////
// Author:    Ralph Walden
// Copyright: Copyright (c) 2024 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "mainapp.h"  // Main application header

void CodePreferenceDlg::OnInit(wxInitDialogEvent& event)
{
    if (!wxGetApp().isTestingSwitch())
    {
        m_radioBtn_Fortran->Hide();
        m_radioBtn_Haskell->Hide();
        m_radioBtn_Lua->Hide();
        m_radioBtn_Perl->Hide();
        m_radioBtn_Rust->Hide();
        m_radioBtn_XRC->Hide();

        Layout();
    }

    event.Skip();
}
