///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#include <wx/button.h>
#include <wx/collpane.h>
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/sizer.h>
#include <wx/valgen.h>

#include <wx/filedlg.h>

#include "sys_header_dlg.h"

#include "node.h"
#include "node_prop.h"
#include "project_handler.h"

bool SysHeaderDlg::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, wxWindow::FromDIP(pos), wxWindow::FromDIP(size), style, name))
        return false;

    auto* dlg_sizer = new wxBoxSizer(wxVERTICAL);

    auto* box_sizer2 = new wxBoxSizer(wxHORIZONTAL);

    auto* collapsible_pane = new wxCollapsiblePane(this, wxID_ANY, "Description");
    collapsible_pane->Collapse();
    box_sizer2->Add(collapsible_pane, wxSizerFlags().Expand().Border(wxALL));

    auto* box_sizer = new wxBoxSizer(wxHORIZONTAL);

    m_text_ctrl = new wxTextCtrl(collapsible_pane->GetPane(), wxID_ANY,
        "Start by selecting or adding a root directory. This should either be a directory in your $INCLUDE environment, or one that is passed to the compiler using -I. Header files will then be displayed automatically relative to this directory. Check the ones you want to add.",
        wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_NO_VSCROLL|wxBORDER_NONE);
    m_text_ctrl->SetMinSize(FromDIP(wxSize(400, -1)));
    m_text_ctrl->SetBackgroundColour(wxColour("#F0F0F0"));
    box_sizer->Add(m_text_ctrl, wxSizerFlags(1).Expand().Border(wxALL));
    collapsible_pane->GetPane()->SetSizerAndFit(box_sizer);

    dlg_sizer->Add(box_sizer2, wxSizerFlags().Border(wxALL));

    auto* box_sizer4 = new wxBoxSizer(wxHORIZONTAL);

    m_static_text = new wxStaticText(this, wxID_ANY, "&Include Directory Root:");
    box_sizer4->Add(m_static_text, wxSizerFlags().Border(wxALL));

    dlg_sizer->Add(box_sizer4, wxSizerFlags().Border(wxLEFT|wxRIGHT|wxTOP, wxSizerFlags::GetDefaultBorder()));

    auto* box_sizer3 = new wxBoxSizer(wxHORIZONTAL);

    m_combo_root = new wxComboBox(this, wxID_ANY);
    m_combo_root->SetToolTip("The directory you pass to the C++ compiler");
    box_sizer3->Add(m_combo_root, wxSizerFlags(1).Border(wxALL));

    auto* btn = new wxButton(this, wxID_ANY, "Directory...");
    box_sizer3->Add(btn, wxSizerFlags().Border(wxALL));

    dlg_sizer->Add(box_sizer3, wxSizerFlags().Expand().Border(wxLEFT|wxRIGHT|wxBOTTOM, wxSizerFlags::GetDefaultBorder()));

    auto* box_sizer6 = new wxBoxSizer(wxVERTICAL);

    m_static_text3 = new wxStaticText(this, wxID_ANY, "Header File(s)");
    box_sizer6->Add(m_static_text3, wxSizerFlags().Border(wxALL));

    m_check_list_files = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_MULTIPLE|
        wxLB_SORT);
    m_check_list_files->SetValidator(wxGenericValidator(&m_file_indexes));
    m_check_list_files->SetMinSize(FromDIP(wxSize(-1, 225)));
    box_sizer6->Add(m_check_list_files, wxSizerFlags(1).Expand().Border(wxALL));

    dlg_sizer->Add(box_sizer6, wxSizerFlags(1).Expand().Border(wxALL));

    auto* stdBtn = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    dlg_sizer->Add(CreateSeparatedSizer(stdBtn), wxSizerFlags().Expand().Border(wxALL));


    SetMinSize(FromDIP(wxSize(800, -1)));
    SetSizerAndFit(dlg_sizer);
    Centre(wxBOTH);

    wxPersistentRegisterAndRestore(this, "SysHeaderDlg");

    // Event handlers
    Bind(wxEVT_BUTTON, &SysHeaderDlg::OnOK, this, wxID_OK);
    btn->Bind(wxEVT_BUTTON, &SysHeaderDlg::OnDirectory, this);
    m_combo_root->Bind(wxEVT_COMBOBOX, &SysHeaderDlg::OnRootSelected, this);
    Bind(wxEVT_INIT_DIALOG, &SysHeaderDlg::OnInit, this);

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

#include <wx/arrstr.h>  // wxArrayString
#include <wx/config.h>  // wxConfig
#include <wx/dir.h>     // wxDir
#include <wx/dirdlg.h>  // wxDirDialog

#include <filesystem>
namespace fs = std::filesystem;

#include "project_handler.h"  // Project

void SysHeaderDlg::Initialize(NodeProperty* prop)
{
    m_prop = prop;
}

void SysHeaderDlg::OnInit(wxInitDialogEvent& WXUNUSED(event))
{
    auto config = wxConfig::Get();
    config->SetPath("/preferences/sys_header_dlg");
    m_FileHistory.Load(*config);
    for (size_t idx = 0; idx < m_FileHistory.GetCount(); ++idx)
    {
        m_combo_root->AppendString(m_FileHistory.GetHistoryFile(idx));
    }

    if (m_combo_root->GetCount() < 9)
    {
        wxString wxwin_path;
        if (wxGetEnv("WXWIN", &wxwin_path))
        {
            tt_string path = wxwin_path.utf8_string();
            if (!path.contains("include"))
            {
                path.append_filename("include");
            }
            m_combo_root->AppendString(path);
        }
    }
    if (m_combo_root->GetCount() < 9)
    {
        m_combo_root->AppendString(Project.getProjectPath());
    }
    m_combo_root->SetSelection(0);
    wxCommandEvent dummy;
    OnRootSelected(dummy);
}

void SysHeaderDlg::OnRootSelected(wxCommandEvent& WXUNUSED(event))
{
    m_check_list_files->Clear();
    tt_string root_path = m_combo_root->GetStringSelection().utf8_string();
    if (root_path.empty())
        return;

    // Fill wxCheckListBox with filenames containing .h, .hh, .hpp, or .hxx
    for (const auto& entry: std::filesystem::recursive_directory_iterator(root_path.make_path()))
    {
        if (entry.is_regular_file())
        {
            tt_string file = entry.path().string();
            auto hdr_ext = file.extension();
            if (hdr_ext == ".h" || hdr_ext == ".hh" || hdr_ext == ".hpp" || hdr_ext == ".hxx")
            {
                file.make_relative(root_path);
                m_check_list_files->Append(file);
            }
        }
    }
}

// Called to add a path to the list of root directories
void SysHeaderDlg::OnDirectory(wxCommandEvent& WXUNUSED(event))
{
    wxDirDialog dlg(this, "Choose directory", wxEmptyString, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    dlg.SetPath(Project.getProjectPath());
    if (dlg.ShowModal() != wxID_OK)
        return;

    m_FileHistory.AddFileToHistory(dlg.GetPath());
    auto config = wxConfig::Get();
    config->SetPath("/preferences/sys_header_dlg");
    m_FileHistory.Save(*config);

    m_combo_root->AppendString(dlg.GetPath());
    wxCommandEvent dummy;
    OnRootSelected(dummy);
}

void SysHeaderDlg::OnOK(wxCommandEvent& event)
{
    // TransferDataFromWindow will set the checked files in m_file_indexes
    if (!Validate() || !TransferDataFromWindow())
        return;

    // Assume that the user has specified the root directory in their build system, passing
    // that path to the compiler via /Ipath -- if there is a folder specified other than '.'
    // then prefix the filename with that folder.

    tt_string root_path = m_combo_root->GetStringSelection().utf8_string();
    m_value.clear();
    for (size_t idx = 0; idx < m_file_indexes.GetCount(); ++idx)
    {
        if (m_value.size())
            m_value << ";";
#if defined(_WIN32)
        tt_string file = m_check_list_files->GetString(m_file_indexes[idx]).utf8_string();
        file.backslashestoforward();
        m_value << file;
#else
        m_value << m_check_list_files->GetString(m_file_indexes[idx]).utf8_string();
#endif
    }

    EndModal(wxID_OK);

    event.Skip();  // This must be called for wxPersistenceManager to work
}
