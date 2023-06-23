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

#include "node_search_dlg.h"

#include "../panels/nav_panel.h"
#include "mainframe.h"
#include "node.h"
#include "project_handler.h"
#include "unused_gen_dlg.h"

bool NodeSearchDlg::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, pos, size, style, name))
        return false;

    auto* dlg_sizer = new wxBoxSizer(wxVERTICAL);

    auto* box_sizer_3 = new wxBoxSizer(wxHORIZONTAL);
    box_sizer_3->SetMinSize(250, -1);

    m_radioBtn = new wxRadioButton(this, wxID_ANY, "&Generators", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    m_radioBtn->SetValue(true);
    m_radioBtn->SetValidator(wxGenericValidator(&m_search_generators));
    box_sizer_3->Add(m_radioBtn, wxSizerFlags().Border(wxALL));

    m_radio_variables = new wxRadioButton(this, wxID_ANY, "&Variables");
    m_radio_variables->SetValidator(wxGenericValidator(&m_search_varnames));
    box_sizer_3->Add(m_radio_variables, wxSizerFlags().Border(wxALL));

    m_radioBtn_3 = new wxRadioButton(this, wxID_ANY, "&Labels");
    m_radioBtn_3->SetValidator(wxGenericValidator(&m_search_labels));
    box_sizer_3->Add(m_radioBtn_3, wxSizerFlags().Border(wxALL));

    auto* btn = new wxButton(this, wxID_ANY, "Unused...");
    box_sizer_3->Add(btn, wxSizerFlags().Border(wxLEFT|wxRIGHT|wxBOTTOM, wxSizerFlags::GetDefaultBorder()));

    dlg_sizer->Add(box_sizer_3, wxSizerFlags().Expand().Border(wxALL));

    auto* box_sizer_4 = new wxBoxSizer(wxHORIZONTAL);
    box_sizer_4->SetMinSize(250, -1);

    auto* box_sizer_5 = new wxBoxSizer(wxVERTICAL);

    auto* staticText = new wxStaticText(this, wxID_ANY, "&Located:");
    box_sizer_5->Add(staticText, wxSizerFlags().Border(wxLEFT|wxRIGHT|wxTOP, wxSizerFlags::GetDefaultBorder()));

    m_listbox = new wxListBox(this, wxID_ANY);
    m_listbox->SetMinSize(ConvertDialogToPixels(wxSize(120, 100)));
    box_sizer_5->Add(m_listbox, wxSizerFlags().Expand().Border(wxALL));

    box_sizer_4->Add(box_sizer_5, wxSizerFlags(1).Expand().Border(wxALL));

    auto* box_sizer_6 = new wxBoxSizer(wxVERTICAL);

    auto* staticText_2 = new wxStaticText(this, wxID_ANY, "&Forms:");
    box_sizer_6->Add(staticText_2, wxSizerFlags().Border(wxLEFT|wxRIGHT|wxTOP, wxSizerFlags::GetDefaultBorder()));

    m_listbox_forms = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_SINGLE|wxLB_SORT);
    m_listbox_forms->SetMinSize(ConvertDialogToPixels(wxSize(-1, 100)));
    box_sizer_6->Add(m_listbox_forms, wxSizerFlags().Expand().Border(wxALL));

    box_sizer_4->Add(box_sizer_6, wxSizerFlags(1).Expand().Border(wxALL));

    dlg_sizer->Add(box_sizer_4,
    wxSizerFlags().Expand().Border(wxLEFT|wxRIGHT|wxBOTTOM, wxSizerFlags::GetDefaultBorder()));

    auto* stdBtn = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    dlg_sizer->Add(CreateSeparatedSizer(stdBtn), wxSizerFlags().Expand().Border(wxALL));

    SetSizerAndFit(dlg_sizer);
    Centre(wxBOTH);

    // Event handlers
    Bind(wxEVT_BUTTON, &NodeSearchDlg::OnOK, this, wxID_OK);
    btn->Bind(wxEVT_BUTTON, &NodeSearchDlg::OnUnused, this);
    Bind(wxEVT_INIT_DIALOG, &NodeSearchDlg::OnInit, this);
    m_listbox->Bind(wxEVT_LISTBOX, &NodeSearchDlg::OnSelectLocated, this);
    m_radioBtn->Bind(wxEVT_RADIOBUTTON, &NodeSearchDlg::OnGenerators, this);
    m_radio_variables->Bind(wxEVT_RADIOBUTTON, &NodeSearchDlg::OnVariables, this);
    m_radioBtn_3->Bind(wxEVT_RADIOBUTTON, &NodeSearchDlg::OnLabels, this);

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
// Copyright: Copyright (c) 2022-2023 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

Node* FindNodeByClassName(Node* node_start, const std::string& classname)
{
    for (const auto& child_form: node_start->GetChildNodePtrs())
    {
        if (child_form->isGen(gen_Images))
            continue;

        if (child_form->HasValue(prop_class_name) && child_form->as_string(prop_class_name) == classname)
            return child_form.get();

        if (child_form->isGen(gen_folder) || child_form->isGen(gen_sub_folder))
        {
            if (auto result = FindNodeByClassName(child_form.get(), classname); result)
            {
                return result;
            }
        }
    }

    return nullptr;
}

Node* FindNodeByGenerator(Node* node, GenEnum::GenName gen_name)
{
    if (node->isGen(gen_name))
        return node;

    for (auto& child: node->GetChildNodePtrs())
    {
        auto result = FindNodeByGenerator(child.get(), gen_name);
        if (result)
            return result;
    }

    return nullptr;
}

Node* FindNodeByVarName(Node* node, const std::string& var_name)
{
    if (node->HasValue(prop_var_name) && node->as_string(prop_var_name) == var_name)
        return node;

    for (auto& child: node->GetChildNodePtrs())
    {
        auto result = FindNodeByVarName(child.get(), var_name);
        if (result)
            return result;
    }

    return nullptr;
}

Node* FindNodeByLabel(Node* node, const std::string& label_name)
{
    if (node->HasValue(prop_label) && node->as_string(prop_label) == label_name)
        return node;

    for (auto& child: node->GetChildNodePtrs())
    {
        auto result = FindNodeByLabel(child.get(), label_name);
        if (result)
            return result;
    }

    return nullptr;
}

void MainFrame::OnFindWidget(wxCommandEvent& WXUNUSED(event))
{
    NodeSearchDlg dlg(this);
    if (dlg.ShowModal() == wxID_OK && dlg.GetForm())
    {
        if (dlg.isSearchGenerators())
        {
            auto* node = FindNodeByGenerator(dlg.GetForm(), rmap_GenNames[dlg.GetNameChoice()]);
            if (node)
            {
                SelectNode(node);
                m_nav_panel->SetFocus();
            }
            else
            {
                wxMessageBox(wxString() << "Unable to find " << dlg.GetName());
            }
        }
        else if (dlg.isSearchVarnames())
        {
            auto* node = FindNodeByVarName(dlg.GetForm(), dlg.GetNameChoice());
            if (node)
            {
                SelectNode(node);
                m_nav_panel->SetFocus();
            }
            else
            {
                wxMessageBox(wxString() << "Unable to find " << dlg.GetName());
            }
        }
        else if (dlg.isSearchLabels())
        {
            auto node = FindNodeByLabel(dlg.GetForm(), dlg.GetNameChoice());
            if (node)
            {
                SelectNode(node);
                m_nav_panel->SetFocus();
            }
            else
            {
                wxMessageBox(wxString() << "Unable to find " << dlg.GetNameChoice());
            }
        }
        else
        {
            wxMessageBox("No selected node, or search criteria selected");
        }
    }
}

void NodeSearchDlg::FindGenerators(Node* node)
{
    if (node->isGen(gen_Images))
        return;

    if (!node->isGen(gen_folder) && !node->isGen(gen_sub_folder) && !node->isGen(gen_Images))
    {
        if (!m_map_found.contains(map_GenNames[node->gen_name()]))
        {
            std::set<Node*> list;
            if (!node->IsForm())
            {
                list.emplace(node->get_form());
            }
            else
            {
                auto* parent = node->GetParent();
                if (parent->isGen(gen_folder) || parent->isGen(gen_sub_folder))
                {
                    list.emplace(node->get_form());
                }
                else
                {
                    list.emplace(Project.ProjectNode());
                }
            }
            m_map_found[map_GenNames[node->gen_name()]] = list;
        }
        else if (!node->IsForm())
        {
            auto& list = m_map_found.at(map_GenNames[node->gen_name()]);
            list.emplace(node->IsForm() ? node->GetParent() : node->get_form());
        }
    }

    if (node->GetChildCount())
    {
        for (auto& child: node->GetChildNodePtrs())
        {
            FindGenerators(child.get());
        }
    }
}

void NodeSearchDlg::FindVariables(Node* node)
{
    if (node->isGen(gen_Images))
        return;

    if (node->HasProp(prop_var_name) && node->HasValue(prop_var_name) && !node->isGen(gen_folder) &&
        !node->isGen(gen_sub_folder) && !node->isGen(gen_Images))
    {
        if (!m_map_found.contains(node->value(prop_var_name)))
        {
            std::set<Node*> form_list;
            if (!node->IsForm())
            {
                form_list.emplace(node->get_form());
            }
            else
            {
                auto* parent = node->GetParent();
                if (parent->isGen(gen_folder) || parent->isGen(gen_sub_folder))
                {
                    form_list.emplace(node->get_form());
                }
                else
                {
                    form_list.emplace(Project.ProjectNode());
                }
            }
            m_map_found[node->value(prop_var_name)] = form_list;
        }
        else if (!node->IsForm())
        {
            auto& form_list = m_map_found.at(node->value(prop_var_name));
            form_list.emplace(node->IsForm() ? node->GetParent() : node->get_form());
        }
    }

    if (node->GetChildCount())
    {
        for (auto& child: node->GetChildNodePtrs())
        {
            FindVariables(child.get());
        }
    }
}

void NodeSearchDlg::FindLabels(Node* node)
{
    if (node->isGen(gen_Images))
        return;

    if (node->HasProp(prop_label) && node->HasValue(prop_label) && !node->isGen(gen_folder) &&
        !node->isGen(gen_sub_folder) && !node->isGen(gen_Images))
    {
        if (!m_map_found.contains(node->value(prop_label)))
        {
            std::set<Node*> form_list;
            if (!node->IsForm())
            {
                form_list.emplace(node->get_form());
            }
            else
            {
                auto* parent = node->GetParent();
                if (parent->isGen(gen_folder) || parent->isGen(gen_sub_folder))
                {
                    form_list.emplace(node->get_form());
                }
                else
                {
                    form_list.emplace(Project.ProjectNode());
                }
            }
            m_map_found[node->value(prop_label)] = form_list;
        }
        else if (!node->IsForm())
        {
            auto& form_list = m_map_found.at(node->value(prop_label));
            form_list.emplace(node->IsForm() ? node->GetParent() : node->get_form());
        }
    }

    if (node->GetChildCount())
    {
        for (auto& child: node->GetChildNodePtrs())
        {
            FindLabels(child.get());
        }
    }
}

void NodeSearchDlg::OnGenerators(wxCommandEvent& WXUNUSED(event))
{
    m_map_found.clear();
    m_listbox->Clear();
    m_listbox_forms->Clear();

    if (auto cur_sel = wxGetFrame().GetSelectedNode(); cur_sel)
    {
        if (cur_sel->isGen(gen_Project) || cur_sel->isGen(gen_folder) || cur_sel->isGen(gen_sub_folder))
        {
            for (auto& child: cur_sel->GetChildNodePtrs())
            {
                FindGenerators(child.get());
            }
        }
        else
        {
            FindGenerators(wxGetFrame().GetSelectedNode());
        }
        for (auto& iter: m_map_found)
        {
            m_listbox->Append(iter.first);
        }
    }
}

void NodeSearchDlg::OnVariables(wxCommandEvent& WXUNUSED(event))
{
    m_map_found.clear();
    m_listbox->Clear();
    m_listbox_forms->Clear();

    if (auto cur_sel = wxGetFrame().GetSelectedNode(); cur_sel)
    {
        if (cur_sel->isGen(gen_Project) || cur_sel->isGen(gen_folder) || cur_sel->isGen(gen_sub_folder))
        {
            for (auto& child: cur_sel->GetChildNodePtrs())
            {
                FindVariables(child.get());
            }
        }
        else
        {
            FindVariables(wxGetFrame().GetSelectedNode());
        }
        for (auto& iter: m_map_found)
        {
            m_listbox->Append(iter.first);
        }
    }
}

void NodeSearchDlg::OnLabels(wxCommandEvent& WXUNUSED(event))
{
    m_map_found.clear();
    m_listbox->Clear();
    m_listbox_forms->Clear();

    if (auto cur_sel = wxGetFrame().GetSelectedNode(); cur_sel)
    {
        if (cur_sel->isGen(gen_Project) || cur_sel->isGen(gen_folder) || cur_sel->isGen(gen_sub_folder))
        {
            for (auto& child: cur_sel->GetChildNodePtrs())
            {
                FindLabels(child.get());
            }
        }
        else
        {
            FindLabels(wxGetFrame().GetSelectedNode());
        }
        for (auto& iter: m_map_found)
        {
            m_listbox->Append(iter.first);
        }
    }
}

void NodeSearchDlg::OnInit(wxInitDialogEvent& event)
{
    wxCommandEvent dummy;
    OnGenerators(dummy);

    event.Skip();
}

void NodeSearchDlg::OnOK(wxCommandEvent& event)
{
    if (m_listbox->GetCount() > 0)
    {
        m_name = m_listbox->GetStringSelection().ToStdString();
        if (m_listbox_forms->GetCount() > 0)
        {
            if (auto class_name = m_listbox_forms->GetStringSelection().ToStdString(); class_name.size())
            {
                m_form = FindNodeByClassName(Project.ProjectNode(), class_name);
            }
            else
            {
                m_form = wxGetFrame().GetSelectedNode();
            }
        }
        else if (wxGetFrame().GetSelectedNode()->IsForm())
        {
            m_form = wxGetFrame().GetSelectedNode();
        }
        else
        {
            m_form = wxGetFrame().GetSelectedNode()->get_form();
        }
    }

    event.Skip();
}

void NodeSearchDlg::OnSelectLocated(wxCommandEvent& WXUNUSED(event))
{
    auto name = m_listbox->GetStringSelection().utf8_string();
    if (m_map_found.contains(name))
    {
        auto& list = m_map_found.at(name);
        m_listbox_forms->Clear();
        for (auto& iter: list)
        {
            m_listbox_forms->Append(iter->value(prop_class_name).make_wxString());
        }
        if (m_listbox_forms->GetCount() > 0)
        {
            m_listbox_forms->SetSelection(0);
        }
    }
}

void NodeSearchDlg::OnUnused(wxCommandEvent& WXUNUSED(event))
{
    UnusedGenerators dlg(this);
    dlg.ShowModal();
}
