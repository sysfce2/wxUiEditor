/////////////////////////////////////////////////////////////////////////////
// Purpose:   wxGridBagSizer generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2020-2022 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include <wx/gbsizer.h>

#include "gen_common.h"  // GeneratorLibrary -- Generator classes
#include "node.h"        // Node class

#include "pugixml.hpp"  // xml read/write/create/process

#include "gen_gridbag_sizer.h"

wxObject* GridBagSizerGenerator::CreateMockup(Node* node, wxObject* /*parent*/)
{
    auto sizer = new wxGridBagSizer(node->prop_as_int(prop_vgap), node->prop_as_int(prop_hgap));

    if (auto& growable = node->prop_as_string(prop_growablecols); growable.size())
    {
        ttlib::multiview values(growable, ',');
        for (auto& iter: values)
        {
            int proportion = 0;
            if (auto pos = iter.find(':'); ttlib::is_found(pos))
            {
                proportion = ttlib::atoi(ttlib::find_nonspace(iter.data() + pos + 1));
            }
            sizer->AddGrowableCol(iter.atoi(), proportion);
        }
    }
    if (auto& growable = node->prop_as_string(prop_growablerows); growable.size())
    {
        ttlib::multiview values(growable, ',');
        for (auto& iter: values)
        {
            int proportion = 0;
            if (auto pos = iter.find(':'); ttlib::is_found(pos))
            {
                proportion = ttlib::atoi(ttlib::find_nonspace(iter.data() + pos + 1));
            }
            sizer->AddGrowableRow(iter.atoi(), proportion);
        }
    }

    sizer->SetMinSize(node->prop_as_wxSize(prop_minimum_size));
    sizer->SetFlexibleDirection(node->prop_as_int(prop_flexible_direction));
    sizer->SetNonFlexibleGrowMode((wxFlexSizerGrowMode) node->prop_as_int(prop_non_flexible_grow_mode));

    if (node->HasValue(prop_empty_cell_size))
    {
        sizer->SetEmptyCellSize(node->prop_as_wxSize(prop_empty_cell_size));
    }

    return sizer;
}

void GridBagSizerGenerator::AfterCreation(wxObject* wxobject, wxWindow* /*wxparent*/)
{
    auto mockup = GetMockup();
    // For storing objects whose postion needs to be determined
    std::vector<std::pair<wxObject*, wxGBSizerItem*>> newNodes;
    wxGBPosition lastPosition(0, 0);

    auto sizer = wxStaticCast(wxobject, wxGridBagSizer);
    if (!sizer)
    {
        FAIL_MSG("This should be a wxGridBagSizer!");
        return;
    }

    auto count = mockup->GetNode(wxobject)->GetChildCount();
    for (size_t i = 0; i < count; ++i)
    {
        auto wxsizerItem = mockup->GetChild(wxobject, i);
        if (!wxsizerItem)
            continue;  // spacer's don't have objects
        auto node = mockup->GetNode(wxsizerItem);

        // Get the location of the item
        wxGBSpan span(node->prop_as_int(prop_rowspan), node->prop_as_int(prop_colspan));

        int column = node->prop_as_int(prop_column);
        if (column < 0)
        {
            // Needs to be auto positioned after the other children are added

            if (auto item = GetGBSizerItem(node, lastPosition, span, wxsizerItem); item)
            {
                newNodes.push_back(std::pair<wxObject*, wxGBSizerItem*>(wxsizerItem, item));
            }
            continue;
        }

        wxGBPosition position(node->prop_as_int(prop_row), column);

        if (sizer->CheckForIntersection(position, span))
        {
            // REVIEW: [KeyWorks - 10-22-2020] Not creating it in the Mockup isn't very helpful to the user since
            // they won't be able to see why the item hasn't been created.
            continue;
        }

        lastPosition = position;

        if (auto item = GetGBSizerItem(node, position, span, wxsizerItem); item)
        {
            sizer->Add(item);
        }
    }

    for (auto& iter: newNodes)
    {
        wxGBPosition position = iter.second->GetPos();
        wxGBSpan span = iter.second->GetSpan();
        int column = position.GetCol();
        while (sizer->CheckForIntersection(position, span))
        {
            column++;
            position.SetCol(column);
        }
        iter.second->SetPos(position);
        sizer->Add(iter.second);
    }
}

std::optional<ttlib::cstr> GridBagSizerGenerator::GenConstruction(Node* node)
{
    // The leading tab is in case we indent in a brace block later on
    ttlib::cstr code("\t");
    if (node->IsLocal())
        code << "auto ";

    code << node->get_node_name() << " = new wxGridBagSizer(";

    auto vgap = node->prop_as_int(prop_vgap);
    auto hgap = node->prop_as_int(prop_hgap);
    if (vgap != 0 || hgap != 0)
    {
        code << vgap << ", " << hgap;
    }
    code << ");";

    // If growable settings are used, there can be a lot of lines of code generated. To make it a bit clearer, we put it
    // in braces
    bool isExpanded = false;

    if (auto& growable = node->prop_as_string(prop_growablecols); growable.size())
    {
        ttlib::multistr values(growable, ',');
        for (auto& iter: values)
        {
            if (!isExpanded)
            {
                code << "\n\t{";
                isExpanded = true;
            }
            auto val = iter.atoi();
            int proportion = 0;
            if (auto pos = iter.find(':'); ttlib::is_found(pos))
            {
                proportion = ttlib::atoi(ttlib::find_nonspace(iter.c_str() + pos + 1));
            }
            code << "\n\t    " << node->get_node_name() << "->AddGrowableCol(" << val;
            if (proportion > 0)
                code << ", " << proportion;
            code << ");";
        }
    }

    if (auto& growable = node->prop_as_string(prop_growablerows); growable.size())
    {
        ttlib::multiview values(growable, ',');
        for (auto& iter: values)
        {
            if (!isExpanded)
            {
                code << "\n\t{";
                isExpanded = true;
            }
            auto val = iter.atoi();
            int proportion = 0;
            if (auto pos = iter.find(':'); ttlib::is_found(pos))
            {
                proportion = ttlib::atoi(ttlib::find_nonspace(iter.data() + pos + 1));
            }
            code << "\n\t    " << node->get_node_name() << "->AddGrowableRow(" << val;
            if (proportion > 0)
                code << ", " << proportion;
            code << ");";
        }
    }

    auto& direction = node->prop_as_string(prop_flexible_direction);
    if (direction.empty() || direction.is_sameas("wxBOTH"))
    {
        if (isExpanded)
            code << "\n\t}";
        return code;
    }

    code << (isExpanded ? "\n\t    " : "\n\t") << node->get_node_name() << "->SetFlexibleDirection(" << direction << ");";

    auto non_flex_growth = node->prop_as_string(prop_non_flexible_grow_mode);
    if (non_flex_growth.empty() || non_flex_growth.is_sameas("wxFLEX_GROWMODE_SPECIFIED"))
    {
        if (isExpanded)
            code << "\n\t}";
        return code;
    }
    code << (isExpanded ? "\n\t    " : "\n\t") << node->get_node_name() << "->SetNonFlexibleGrowMode(" << non_flex_growth
         << ");";

    if (isExpanded)
        code << "\n\t}";
    return code;
}

bool GridBagSizerGenerator::GetIncludes(Node* node, std::set<std::string>& set_src, std::set<std::string>& set_hdr)
{
    InsertGeneratorInclude(node, "#include <wx/gbsizer.h>", set_src, set_hdr);
    return true;
}

wxGBSizerItem* GridBagSizerGenerator::GetGBSizerItem(Node* sizeritem, const wxGBPosition& position, const wxGBSpan& span,
                                                     wxObject* child)
{
    auto sizer_flags = sizeritem->GetSizerFlags();

    if (sizeritem->isGen(gen_spacer))
    {
        return new wxGBSizerItem(sizeritem->prop_as_int(prop_width), sizeritem->prop_as_int(prop_height), position, span,
                                 sizer_flags.GetFlags(), sizer_flags.GetBorderInPixels());
    }

    // Add the child (window or sizer) to the sizer
    auto windowChild = wxDynamicCast(child, wxWindow);
    auto sizerChild = wxDynamicCast(child, wxSizer);

    if (windowChild)
    {
        return new wxGBSizerItem(windowChild, position, span, sizer_flags.GetFlags(), sizer_flags.GetBorderInPixels());
    }
    else if (sizerChild)
    {
        return new wxGBSizerItem(sizerChild, position, span, sizer_flags.GetFlags(), sizer_flags.GetBorderInPixels());
    }
    else
    {
        FAIL_MSG("The GBSizerItem component's child is not a wxWindow or a wxSizer or a Spacer - this should not be "
                 "possible!");
        return nullptr;
    }
}