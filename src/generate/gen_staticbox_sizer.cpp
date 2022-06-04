/////////////////////////////////////////////////////////////////////////////
// Purpose:   wxStaticBoxSizer generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2020-2022 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include <wx/sizer.h>
#include <wx/statbox.h>

#include "gen_common.h"  // GeneratorLibrary -- Generator classes
#include "node.h"        // Node class

#include "pugixml.hpp"  // xml read/write/create/process

#include "gen_staticbox_sizer.h"

wxObject* StaticBoxSizerGenerator::CreateMockup(Node* node, wxObject* parent)
{
    auto sizer = new wxStaticBoxSizer(node->prop_as_int(prop_orientation), wxStaticCast(parent, wxWindow),
                                      node->prop_as_wxString(prop_label));

    auto min_size = node->prop_as_wxSize(prop_minimum_size);
    if (min_size.x != -1 || min_size.y != -1)
        sizer->SetMinSize(min_size);

    if (node->prop_as_bool(prop_hidden) && !GetMockup()->IsShowingHidden())
        sizer->GetStaticBox()->Hide();

    return sizer;
}

std::optional<ttlib::cstr> StaticBoxSizerGenerator::GenConstruction(Node* node)
{
    ttlib::cstr code;
    if (node->IsLocal())
        code << "auto ";

    ttlib::cstr parent_name("this");
    if (!node->GetParent()->IsForm())
    {
        auto parent = node->GetParent();
        while (parent)
        {
            if (parent->IsContainer())
            {
                parent_name = parent->get_node_name();
                break;
            }
            else if (parent->isGen(gen_wxStaticBoxSizer) || parent->isGen(gen_StaticCheckboxBoxSizer) ||
                     parent->isGen(gen_StaticRadioBtnBoxSizer))
            {
                parent_name.clear();
                parent_name << parent->get_node_name() << "->GetStaticBox()";
                break;
            }
            parent = parent->GetParent();
        }
    }

    code << node->get_node_name() << " = new wxStaticBoxSizer(" << node->prop_as_string(prop_orientation) << ", "
         << parent_name;

    auto& label = node->prop_as_string(prop_label);
    if (label.size())
    {
        code << ", " << GenerateQuotedString(label);
    }
    code << ");";

    auto min_size = node->prop_as_wxSize(prop_minimum_size);
    if (min_size.GetX() != -1 || min_size.GetY() != -1)
    {
        code << "\n\t" << node->get_node_name() << "->SetMinSize(" << min_size.GetX() << ", " << min_size.GetY() << ");";
    }

    return code;
}

std::optional<ttlib::cstr> StaticBoxSizerGenerator::GenSettings(Node* node, size_t& /* auto_indent */)
{
    ttlib::cstr code;
    if (node->prop_as_bool(prop_disabled))
    {
        code << node->get_node_name() << "->GetStaticBox()->Enable(false);";
    }
    if (node->prop_as_bool(prop_hidden))
    {
        if (code.size())
            code << "\n\t";
        code << node->get_node_name() << "->GetStaticBox()->Hide();";
    }

    return code;
}

std::optional<ttlib::cstr> StaticBoxSizerGenerator::GenEvents(NodeEvent* event, const std::string& class_name)
{
    return GenEventCode(event, class_name);
}

bool StaticBoxSizerGenerator::GetIncludes(Node* node, std::set<std::string>& set_src, std::set<std::string>& set_hdr)
{
    InsertGeneratorInclude(node, "#include <wx/sizer.h>", set_src, set_hdr);
    InsertGeneratorInclude(node, "#include <wx/statbox.h>", set_src, set_hdr);
    return true;
}
int StaticBoxSizerGenerator::GenXrcObject(Node* node, pugi::xml_node& object, bool /* add_comments */)
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

    item.append_attribute("class").set_value("wxStaticBoxSizer");
    item.append_attribute("name").set_value(node->prop_as_string(prop_var_name));
    item.append_child("orient").text().set(node->prop_as_string(prop_orientation));
    if (node->HasValue(prop_minimum_size))
    {
        item.append_child("minsize").text().set(node->prop_as_string(prop_minimum_size));
    }

    ADD_ITEM_PROP(prop_label, "label")

    return result;
}

void StaticBoxSizerGenerator::RequiredHandlers(Node* /* node */, std::set<std::string>& handlers)
{
    handlers.emplace("wxSizerXmlHandler");
}