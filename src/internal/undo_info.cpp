///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#include <wx/button.h>
#include <wx/sizer.h>

#include "undo_info.h"

bool UndoInfo::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, wxWindow::FromDIP(pos), wxWindow::FromDIP(size), style, name))
        return false;

    auto* dlg_sizer = new wxBoxSizer(wxVERTICAL);

    auto* flex_grid_sizer = new wxFlexGridSizer(2, 0, 0);

    auto* staticText_5 = new wxStaticText(this, wxID_ANY, "Number of Undo items:");
    flex_grid_sizer->Add(staticText_5, wxSizerFlags().Border(wxALL));

    m_txt_undo_items = new wxStaticText(this, wxID_ANY, "...");
    flex_grid_sizer->Add(m_txt_undo_items, wxSizerFlags().Border(wxALL));

    auto* staticText_6 = new wxStaticText(this, wxID_ANY, "Number of Redo items:");
    flex_grid_sizer->Add(staticText_6, wxSizerFlags().Border(wxALL));

    m_txt_redo_items = new wxStaticText(this, wxID_ANY, "...");
    flex_grid_sizer->Add(m_txt_redo_items, wxSizerFlags().Border(wxALL));

    dlg_sizer->Add(flex_grid_sizer, wxSizerFlags().Border(wxALL));

    auto* staticText = new wxStaticText(this, wxID_ANY,
        "The amount of memory used is determined by the reference count of the nodes. If the node is not orphaned, then it consumes no additional memory other than the shared_ptr itself.",
        wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    staticText->Wrap(300);
    dlg_sizer->Add(staticText, wxSizerFlags().Border(wxALL));

    auto* flex_grid_sizer_2 = new wxFlexGridSizer(2, 0, 0);

    auto* staticText_7 = new wxStaticText(this, wxID_ANY, "Undo Memory:");
    flex_grid_sizer_2->Add(staticText_7, wxSizerFlags().Border(wxALL));

    m_txt_undo_memory = new wxStaticText(this, wxID_ANY, "...");
    flex_grid_sizer_2->Add(m_txt_undo_memory, wxSizerFlags().Border(wxALL));

    auto* staticText_8 = new wxStaticText(this, wxID_ANY, "Redo Memory:");
    flex_grid_sizer_2->Add(staticText_8, wxSizerFlags().Border(wxALL));

    m_txt_redo_memory = new wxStaticText(this, wxID_ANY, "...");
    flex_grid_sizer_2->Add(m_txt_redo_memory, wxSizerFlags().Border(wxALL));

    dlg_sizer->Add(flex_grid_sizer_2, wxSizerFlags().Border(wxALL));

    auto* stdBtn = CreateStdDialogButtonSizer(wxCLOSE|wxNO_DEFAULT);
    dlg_sizer->Add(CreateSeparatedSizer(stdBtn), wxSizerFlags().Expand().Border(wxALL));

    SetSizerAndFit(dlg_sizer);
    Centre(wxBOTH);

    // Event handlers
    Bind(wxEVT_INIT_DIALOG, &UndoInfo::OnInit, this);

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
// Copyright: Copyright (c) 2023 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "mainframe.h"
#include "node.h"
#include "node_info.h"
#include "node_prop.h"
#include "undo_stack.h"

void UndoInfo::OnInit(wxInitDialogEvent& event)
{
    NodeInfo::NodeMemory node_memory;

    // The problem with getting the memory size is that it's a bit tricky to know what the
    // reference count needs to be under to indicate that a Node is only being held by the
    // UndoStack.

    // The auto&& CalcMemory and forced return type is so that we can recursively call this
    // lambda function.
    auto CalcMemory = [&node_memory](const NodeSharedPtr node, long ref_count, auto&& CalcMemory) -> void
    {
        ++node_memory.children;
        if (node.use_count() <= ref_count)
        {
            node_memory.size += node->getNodeSize();
        }

        for (const auto& iter: node->getChildNodePtrs())
        {
            // Assume that each child will have a shared ptr to the parent which will increase
            // it's reference count by 1.
            long add_ref_count = static_cast<long>(iter->getChildCount());

            // An orphaned node will have a ref count of 1 -- add one to pass this to the
            // CalcMemory function.
            CalcMemory(iter, add_ref_count + 2, CalcMemory);
        }
    };

    // This will iterate through the vector of actions, adding up the memory size (and possible
    // number of node children) for each action in the vector.
    auto ParseActions = [&](const std::vector<UndoActionPtr>& actions, wxStaticText* ptxt_items, wxStaticText* ptxt_memory)
    {
        node_memory.size = 0;
        node_memory.children = 0;

        for (const auto& iter: actions)
        {
            if (const auto& old_node = iter->GetOldNode(); old_node)
            {
                if (old_node->isGen(gen_Project))
                {
                    // Every form in the project will increase the project's ref count
                    CalcMemory(old_node, 9999, CalcMemory);
                }
                else
                {
                    // Assume that each child will have a shared ptr to the parent which will increase
                    // it's reference count by 1.
                    long add_ref_count = static_cast<long>(old_node->getChildCount());

                    CalcMemory(old_node, add_ref_count + 3, CalcMemory);
                }
                node_memory.size += iter->GetMemorySize();
            }
            else if (const auto& node = iter->getNode(); node)
            {
                // An orphaned node will have an additional 2 reference counts at this point. 1 for
                // iter->getNode() in the function that called us, and one for passing the parameter to
                // this function. An additional ref count is added by calling CalcMemory.
                CalcMemory(node, 3, CalcMemory);
                node_memory.size += iter->GetMemorySize();
            }
            else if (const auto* prop = iter->GetProperty(); prop)
            {
                node_memory.size += iter->GetMemorySize();
            }
        }

#ifdef __cpp_lib_format
        auto txt_items = std::format(std::locale(""), "{:L}", actions.size());
#else
        tt_string txt_items;
        txt_items << actions.size();
#endif
        ptxt_items->SetLabel(txt_items);

        if (node_memory.size > 0)
        {
#ifdef __cpp_lib_format
            auto txt_totals = std::format(std::locale(""), "{:L} ({:L} node{})", node_memory.size, node_memory.children,
                                          node_memory.children == 1 ? "" : "s");
#else
            tt_string txt_totals;
            txt_totals << node_memory.size << " (" << node_memory.children << ") node"
                       << (node_memory.children == 1 ? "" : "s");
#endif
            ptxt_memory->SetLabel(txt_totals);
        }
        else
        {
            ptxt_memory->SetLabel("0");
        }
    };

    const auto& undo_stack = wxGetMainFrame()->getUndoStack();
    const auto& undo_vector = undo_stack.GetUndoVector();
    const auto& redo_vector = undo_stack.GetRedoVector();

    ParseActions(undo_vector, m_txt_undo_items, m_txt_undo_memory);
    ParseActions(redo_vector, m_txt_redo_items, m_txt_redo_memory);

    Fit();

    event.Skip();
}
