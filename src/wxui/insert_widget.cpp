///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#include <wx/artprov.h>
#include <wx/icon.h>
#include <wx/stattext.h>

#include "insert_widget.h"

bool InsertWidget::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, pos, size, style, name))
        return false;
    SetIcon(wxArtProvider::GetBitmapBundle(wxART_EDIT, wxART_MENU).GetIconFor(this));

    auto* box_sizer = new wxBoxSizer(wxVERTICAL);
    box_sizer->SetMinSize(300, 400);

    auto* box_sizer_2 = new wxBoxSizer(wxHORIZONTAL);

    auto* staticText = new wxStaticText(this, wxID_ANY, "&Name:");
    box_sizer_2->Add(staticText, wxSizerFlags().Center().Border(wxALL));

    m_text_name = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    m_text_name->SetHint("type a portion of the name to filter the list");
    m_text_name->SetToolTip("Use Up/Down arrows to change list selection");
    box_sizer_2->Add(m_text_name, wxSizerFlags(1).Border(wxALL));

    box_sizer->Add(box_sizer_2, wxSizerFlags().Expand().Border(wxALL));

    auto* box_sizer_4 = new wxBoxSizer(wxHORIZONTAL);

    auto* staticText_2 = new wxStaticText(this, wxID_ANY,
        "Only widgets that can be a child of the currently selected widget are shown. If the list is empty, no children can be added.");
    staticText_2->Wrap(300);
    box_sizer_4->Add(staticText_2, wxSizerFlags().Border(wxALL));

    box_sizer->Add(box_sizer_4, wxSizerFlags().Border(wxALL));

    auto* box_sizer_3 = new wxBoxSizer(wxHORIZONTAL);

    m_listbox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 300), 0, nullptr, wxLB_SINGLE|wxLB_SORT);
    box_sizer_3->Add(m_listbox, wxSizerFlags(1).Expand().Border(wxALL));

    box_sizer->Add(box_sizer_3, wxSizerFlags(1).Expand().Border(wxALL));

    m_stdBtn = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    box_sizer->Add(CreateSeparatedSizer(m_stdBtn), wxSizerFlags().Expand().Border(wxALL));

    SetSizerAndFit(box_sizer);
    Centre(wxBOTH);

    // Event handlers
    Bind(wxEVT_BUTTON, &InsertWidget::OnOK, this, wxID_OK);
    Bind(wxEVT_INIT_DIALOG, &InsertWidget::OnInit, this);
    m_text_name->Bind(wxEVT_KEY_DOWN, &InsertWidget::OnKeyDown, this);
    m_listbox->Bind(wxEVT_LISTBOX,
        [this](wxCommandEvent&)
        {
            m_stdBtn->GetAffirmativeButton()->Enable();
        });
    m_listbox->Bind(wxEVT_LISTBOX_DCLICK, &InsertWidget::OnListBoxDblClick, this);
    m_text_name->Bind(wxEVT_TEXT, &InsertWidget::OnNameText, this);

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
// Purpose:   Dialog to lookup and insert a widget
// Author:    Ralph Walden
// Copyright: Copyright (c) 2021-2022 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "mainframe.h"     // MainFrame -- Main window frame
#include "node.h"          // Node class
#include "node_creator.h"  // NodeCreator -- Class used to create nodes

void MainFrame::OnInsertWidget(wxCommandEvent&)
{
    InsertWidget dlg(this);
    if (dlg.ShowModal() == wxID_OK)
    {
        if (auto result = rmap_GenNames.find(dlg.GetWidget()); result != rmap_GenNames.end())
        {
            return createToolNode(result->second);
        }
        FAIL_MSG(tt_string() << "No property enum type exists for dlg.GetWidget()! This should be impossible...")
    }
}

#if defined(_DEBUG) || defined(INTERNAL_TESTING)

Node* FindChildNode(Node* node, GenEnum::GenName name)
{
    for (const auto& child: node->getChildNodePtrs())
    {
        if (child->isGen(name))
        {
            return child.get();
        }
        else if (child->getChildCount() > 0)
        {
            if (auto child_node = FindChildNode(child.get(), name); child_node)
            {
                return child_node;
            }
        }
    }
    return nullptr;
}

#endif  // defined(_DEBUG) || defined(INTERNAL_TESTING)

void InsertWidget::OnInit(wxInitDialogEvent& WXUNUSED(event))
{
    m_stdBtn->GetAffirmativeButton()->Disable();
    m_text_name->SetFocus();
    wxCommandEvent dummy;
    OnNameText(dummy);
}

void InsertWidget::OnNameText(wxCommandEvent& WXUNUSED(event))
{
    tt_string name = m_text_name->GetValue().utf8_string();
    m_listbox->Clear();
    auto node = wxGetFrame().getSelectedNode();

    for (auto iter: NodeCreation.getNodeDeclarationArray())
    {
        if (!iter)
        {
            // This will happen if there is an enumerated value but no generator for it
            continue;
        }

        if (!node || !node->isChildAllowed(iter))
        {
            continue;
        }

        if (name.empty() || iter->declName().contains(name, tt::CASE::either))
        {
            m_listbox->AppendString(iter->declName().make_wxString());
        }
    }

    if (m_listbox->GetCount() > 0)
    {
        m_listbox->Select(0);
        m_stdBtn->GetAffirmativeButton()->Enable();
    }
    else
    {
        m_stdBtn->GetAffirmativeButton()->Disable();
    }
}

void InsertWidget::OnListBoxDblClick(wxCommandEvent& WXUNUSED(event))
{
    wxCommandEvent event(wxEVT_BUTTON, m_stdBtn->GetAffirmativeButton()->GetId());
    ProcessEvent(event);
}

void InsertWidget::OnOK(wxCommandEvent& event)
{
    m_widget << m_listbox->GetStringSelection().utf8_string();
    event.Skip();
}

void InsertWidget::OnKeyDown(wxKeyEvent& event)
{
    auto keycode = event.GetKeyCode();
    if (keycode == WXK_DOWN || keycode == WXK_NUMPAD_DOWN)
    {
        auto sel = m_listbox->GetSelection() + 1;
        if (sel < static_cast<int>(m_listbox->GetCount()))
            m_listbox->SetSelection(sel);
    }
    else if (keycode == WXK_UP || keycode == WXK_NUMPAD_UP)
    {
        auto sel = m_listbox->GetSelection() - 1;
        if (sel >= 0)
            m_listbox->SetSelection(sel);
    }
    else
    {
        event.Skip();
    }
}
