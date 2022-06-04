//////////////////////////////////////////////////////////////////////////
// Purpose:   wxBitmapButton::CreateCloseButton generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2020-2022 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include <wx/bmpbuttn.h>  // wxBitmapButton class interface

#include "gen_common.h"     // GeneratorLibrary -- Generator classes
#include "gen_xrc_utils.h"  // Common XRC generating functions
#include "node.h"           // Node class
#include "pugixml.hpp"      // xml read/write/create/process
#include "utils.h"          // Utility functions that work with properties

#include "gen_close_btn.h"

wxObject* CloseButtonGenerator::CreateMockup(Node* /* node */, wxObject* parent)
{
    auto widget = new wxBitmapButton;
    widget->CreateCloseButton(wxStaticCast(parent, wxWindow), wxID_ANY);

    widget->Bind(wxEVT_LEFT_DOWN, &BaseGenerator::OnLeftClick, this);

    return widget;
}

std::optional<ttlib::cstr> CloseButtonGenerator::GenConstruction(Node* node)
{
    ttlib::cstr code;
    if (node->IsLocal())
        code << "auto ";
    code << node->get_node_name() << " = new wxBitmapButton;\n";
    code << node->get_node_name() << "->CreateCloseButton(" << GetParentName(node) << ", ";
    if (!node->HasValue(prop_id))
    {
        code << "wxID_ANY);";
    }
    else
    {
        code << node->prop_as_string(prop_id) << ");";
    }

    return code;
}

std::optional<ttlib::cstr> CloseButtonGenerator::GenEvents(NodeEvent* event, const std::string& class_name)
{
    return GenEventCode(event, class_name);
}

bool CloseButtonGenerator::GetIncludes(Node* node, std::set<std::string>& set_src, std::set<std::string>& set_hdr)
{
    InsertGeneratorInclude(node, "#include <wx/bmpbuttn.h>", set_src, set_hdr);
    InsertGeneratorInclude(node, "#include <wx/button.h>", set_src, set_hdr);
    return true;
}

int CloseButtonGenerator::GenXrcObject(Node* node, pugi::xml_node& object, bool add_comments)
{
    pugi::xml_node item;
    auto result = BaseGenerator::xrc_sizer_item_created;

    if (node->GetParent()->IsSizer())
    {
        GenXrcSizerItem(node, object);
        item = object.append_child("object");
    }
    else
    {
        item = object;
        result = BaseGenerator::xrc_updated;
    }

    item.append_attribute("class").set_value("wxBitmapButton");
    item.append_attribute("name").set_value(node->prop_as_string(prop_var_name));

    item.append_child("close").text().set("1");

    GenXrcWindowSettings(node, item);

    if (add_comments)
    {
        GenXrcComments(node, item);
    }

    return result;
}

void CloseButtonGenerator::RequiredHandlers(Node* /* node */, std::set<std::string>& handlers)
{
    handlers.emplace("wxBitmapButtonXmlHandler");
}