///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/valgen.h>

#include "preview_settings.h"

bool PreviewSettings::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, wxWindow::FromDIP(pos), wxWindow::FromDIP(size), style, name))
        return false;

    auto* dlg_sizer = new wxBoxSizer(wxVERTICAL);

    m_staticText = new wxStaticText(this, wxID_ANY, "Choose what you want to use to display the form.");
    dlg_sizer->Add(m_staticText, wxSizerFlags().Border(wxALL));

    auto* box_sizer = new wxBoxSizer(wxHORIZONTAL);

    auto* radio_XRC = new wxRadioButton(this, wxID_ANY, "XRC", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    radio_XRC->SetValidator(wxGenericValidator(&type_xrc));
    box_sizer->Add(radio_XRC, wxSizerFlags().Border(wxALL));

    m_radio_XRC_CPP = new wxRadioButton(this, wxID_ANY, "XRC and C++");
    m_radio_XRC_CPP->SetValidator(wxGenericValidator(&type_xrc_cpp));
    box_sizer->Add(m_radio_XRC_CPP, wxSizerFlags().Border(wxALL));

    auto* radio_CPP = new wxRadioButton(this, wxID_ANY, "C++");
    radio_CPP->SetValidator(wxGenericValidator(&type_cpp));
    box_sizer->Add(radio_CPP, wxSizerFlags().Border(wxALL));

    dlg_sizer->Add(box_sizer, wxSizerFlags().Border(wxALL));

    auto* stdBtn = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    dlg_sizer->Add(CreateSeparatedSizer(stdBtn), wxSizerFlags().Expand().Border(wxALL));

    SetSizerAndFit(dlg_sizer);
    Centre(wxBOTH);

    // Event handlers
    Bind(wxEVT_INIT_DIALOG, &PreviewSettings::OnInit, this);

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

/////////////////////////////////////////////////////////////////////////////
// Author:    Ralph Walden
// Copyright: Copyright (c) 2022-2023 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "mainframe.h"  // MainFrame -- Main application window
#include "node.h"       // Node class

void PreviewSettings::OnInit(wxInitDialogEvent& event)
{
    auto* form_node = wxGetMainFrame()->getSelectedNode();
    if (!form_node->isForm())
    {
        if (form_node->isGen(gen_Project) && form_node->getChildCount())
        {
            form_node = form_node->getChild(0);
        }
        else
        {
            form_node = form_node->getForm();
        }
    }

    if (!form_node->isGen(gen_wxDialog) && !form_node->isGen(gen_PanelForm))
    {
        if (is_type_both())
        {
            set_type_both(false);
            set_type_cpp(true);
        }
        m_radio_XRC_CPP->Hide();
        Refresh();
    }

    event.Skip();
}
