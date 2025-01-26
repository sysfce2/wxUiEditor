///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#pragma once

#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/stattext.h>

#include "node_classes.h"

class NodeInfo : public wxDialog
{
public:
    NodeInfo() {}
    NodeInfo(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Node Information", const wxPoint& pos =
        wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr)
    {
        Create(parent, id, title, pos, size, style, name);
    }
    bool Create(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Node Information", const wxPoint& pos =
        wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr);

    struct NodeMemory
    {
        size_t size { 0 };
        size_t children { 0 };
    };

    void SetNode(Node* node) { m_node = node; }
    static void CalcNodeMemory(Node* node, NodeMemory& node_memory);

protected:

    // Event handlers

    void OnInit(wxInitDialogEvent& event);

private:

    // Class member variables

    wxStaticText* m_txt_clipboard;
    wxStaticText* m_txt_generator;
    wxStaticText* m_txt_memory;
    wxStaticText* m_txt_project;
    wxStaticText* m_txt_type;

    Node* m_node { nullptr };
};

// ************* End of generated code ***********
// DO NOT EDIT THIS COMMENT BLOCK!
//
// Code below this comment block will be preserved
// if the code for this class is re-generated.
//
// clang-format on
// ***********************************************
