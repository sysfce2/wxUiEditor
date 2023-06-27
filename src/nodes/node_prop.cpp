/////////////////////////////////////////////////////////////////////////////
// Purpose:   NodeProperty class
// Author:    Ralph Walden
// Copyright: Copyright (c) 2020-2021 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include <array>
#include <charconv>
#include <cstdlib>

#include <wx/animate.h>                // wxAnimation and wxAnimationCtrl
#include <wx/propgrid/propgriddefs.h>  // wxPropertyGrid miscellaneous definitions

#include "font_prop.h"      // FontProperty -- FontProperty class
#include "image_handler.h"  // ImageHandler class
#include "mainapp.h"        // App -- Main application class
#include "node.h"           // Node -- Node class
#include "node_creator.h"   // NodeCreator class
#include "utils.h"          // Utility functions that work with properties

#include "node_prop.h"

using namespace GenEnum;

NodeProperty::NodeProperty(PropDeclaration* info, Node* node) : m_declaration(info), m_node(node) {}

// The advantage of placing the one-line calls to PropDeclaration (m_declaration) here is that it reduces the header-file
// dependency for other modeuls that need NodeProperty, and it allows for changes to PropDeclaration that don't require
// recompiling every module that included prop_decl.h.

bool NodeProperty::IsDefaultValue() const
{
    return m_value.is_sameas(m_declaration->GetDefaultValue());
}

int NodeProperty::as_int() const
{
    switch (type())
    {
        case type_editoption:
        case type_option:
        case type_id:
            return NodeCreation.GetConstantAsInt(m_value, 0);

        case type_bitlist:
            {
                int result = 0;
                tt_string_vector mstr(m_value, '|');
                for (auto& iter: mstr)
                {
                    result |= NodeCreation.GetConstantAsInt(iter);
                }
                return result;
            }

        default:
            return m_value.atoi();  // this will return 0 if the m_value is an empty string
    }
}

int NodeProperty::as_id() const
{
    return NodeCreation.GetConstantAsInt(m_value, wxID_ANY);
}

int NodeProperty::as_mockup(std::string_view prefix) const
{
    switch (type())
    {
        case type_editoption:
        case type_option:
        case type_id:
            if (m_value.starts_with("wx"))
            {
                return NodeCreation.GetConstantAsInt(m_value, 0);
            }
            else
            {
                if (prefix.size())
                {
                    tt_string name;
                    name << prefix << m_value;
                    if (auto result = g_friend_constant.find(name); result != g_friend_constant.end())
                    {
                        return NodeCreation.GetConstantAsInt(result->second, 0);
                    }
                }
                else
                {
                    if (auto result = g_friend_constant.find(m_value); result != g_friend_constant.end())
                    {
                        return NodeCreation.GetConstantAsInt(result->second, 0);
                    }
                }
            }
            return 0;

        case type_bitlist:
            {
                tt_string_vector mstr(m_value, '|', tt::TRIM::both);
                int value = 0;
                for (auto& iter: mstr)
                {
                    if (iter.starts_with("wx"))
                    {
                        value |= NodeCreation.GetConstantAsInt(iter);
                    }
                    else
                    {
                        if (prefix.size())
                        {
                            iter.insert(0, prefix);
                        }
                        if (auto result = g_friend_constant.find(iter); result != g_friend_constant.end())
                        {
                            value |= NodeCreation.GetConstantAsInt(result->second);
                        }
                    }
                }
                return value;
            }

        default:
            return m_value.atoi();  // this will return 0 if the m_value is an empty string
    }
}

const tt_string& NodeProperty::as_constant(std::string_view prefix)
{
    switch (type())
    {
        case type_editoption:
        case type_option:
        case type_id:
            if (m_value.starts_with("wx"))
            {
                return m_value;
            }
            else
            {
                if (prefix.size())
                {
                    m_constant.clear();
                    m_constant << prefix << m_value;
                    if (auto result = g_friend_constant.find(m_constant); result != g_friend_constant.end())
                    {
                        m_constant = result->second;
                    }
                    else
                    {
                        m_constant.clear();
                    }
                }
                else
                {
                    if (auto result = g_friend_constant.find(m_value); result != g_friend_constant.end())
                    {
                        m_constant = result->second;
                    }
                    else
                    {
                        m_constant.clear();
                    }
                }
                return m_constant;
            }

        case type_bitlist:
            {
                tt_string_vector mstr(m_value, '|', tt::TRIM::both);
                m_constant.clear();
                for (auto& iter: mstr)
                {
                    if (iter.starts_with("wx"))
                    {
                        if (m_constant.size())
                        {
                            m_constant << '|';
                        }
                        m_constant << iter;
                    }
                    else
                    {
                        if (prefix.size())
                        {
                            iter.insert(0, prefix);
                        }
                        if (auto result = g_friend_constant.find(iter); result != g_friend_constant.end())
                        {
                            if (m_constant.size())
                            {
                                m_constant << " | ";
                            }
                            m_constant << result->second;
                        }
                    }
                }
                return m_constant;
            }

        default:
            return m_value;  // this will return 0 if the m_value is an empty string
    }
}

wxPoint NodeProperty::as_point() const
{
    wxPoint result { -1, -1 };
    if (m_value.size())
    {
        tt_view_vector tokens(m_value, ',');
        if (tokens.size())
        {
            if (tokens[0].size())
                result.x = tokens[0].atoi();

            if (tokens.size() > 1 && tokens[1].size())
                result.y = tokens[1].atoi();
        }
    }
    return result;
}

wxSize NodeProperty::as_size() const
{
    wxSize result { -1, -1 };
    if (m_value.size())
    {
        tt_view_vector tokens(m_value, ',');
        if (tokens.size())
        {
            if (tokens[0].size())
                result.x = tokens[0].atoi();

            if (tokens.size() > 1 && tokens[1].size())
                result.y = tokens[1].atoi();
        }
    }
    return result;
}

wxColour NodeProperty::as_color() const
{
    // check for system colour
    if (m_value.starts_with("wx"))
    {
        return wxSystemSettings::GetColour(ConvertToSystemColour(m_value));
    }
    else
    {
        tt_view_vector mstr(m_value, ',');
        unsigned long rgb = 0;
        if (mstr.size() > 2)
        {
            auto blue = mstr[2].atoi();
            if (blue < 0 || blue > 255)
                blue = 0;
            rgb |= (blue << 16);
        }
        if (mstr.size() > 1)
        {
            auto green = mstr[1].atoi();
            if (green < 0 || green > 255)
                green = 0;
            rgb |= (green << 8);
        }
        if (mstr.size() > 0)
        {
            auto red = mstr[0].atoi();
            if (red < 0 || red > 255)
                red = 0;
            rgb |= red;
        }
        wxColour clr(rgb);
        return clr;
    }
}

wxFont NodeProperty::as_font() const
{
    return FontProperty(m_value.subview()).GetFont();
}

FontProperty NodeProperty::as_font_prop() const
{
    FontProperty font_prop(m_value.subview());
    return font_prop;
}

wxBitmap NodeProperty::as_bitmap() const
{
    auto image = ProjectImages.GetImage(m_value);
    if (!image.IsOk())
    {
        image = ProjectImages.GetImage(m_value);
        if (!image.IsOk())
        {
            return wxNullBitmap;
        }
    }

    return image;
}

wxBitmapBundle NodeProperty::as_bitmap_bundle() const
{
    auto bundle = ProjectImages.GetBitmapBundle(m_value, m_node);
    if (!bundle.IsOk())
        return wxNullBitmap;
    else
        return bundle;
}

const ImageBundle* NodeProperty::as_image_bundle() const
{
    auto bundle_ptr = ProjectImages.GetPropertyImageBundle(m_value);
    if (!bundle_ptr || !bundle_ptr->bundle.IsOk())
        return nullptr;
    else
        return bundle_ptr;
}

wxAnimation NodeProperty::as_animation() const
{
    return ProjectImages.GetPropertyAnimation(m_value);
}

tt_string NodeProperty::as_escape_text() const
{
    tt_string result;

    for (auto ch: m_value)
    {
        switch (ch)
        {
            case '\n':
                result += "\\n";
                break;

            case '\t':
                result += "\\t";
                break;

            case '\r':
                result += "\\r";
                break;

            case '\\':
                result += "\\\\";
                break;

            default:
                result += ch;
                break;
        }
    }

    return result;
}

std::vector<tt_string> NodeProperty::as_vector() const
{
    std::vector<tt_string> array;
    if (m_value.empty())
        return array;
    tt_string parse;
    std::string_view value = m_value;
    auto pos = parse.ExtractSubString(value);
    array.emplace_back(parse);

    for (value = tt::stepover(value.data() + pos); value.size(); value = tt::stepover(value.data() + pos))
    {
        pos = parse.ExtractSubString(value);
        array.emplace_back(parse);
    }

    return array;
}

std::vector<tt_string> NodeProperty::as_ArrayString() const
{
    std::vector<tt_string> result;
    if (m_value.size())
    {
#if 0
        tt_string parse;
        auto pos = parse.ExtractSubString(m_value);
        if (!tt::is_found(pos))
        {
            // This usually means a property that was hand-edited incorrectly, or a newer version of the project
            // file where the property is encoded differently.
            return array;
        }
        result.emplace_back(parse);

        for (auto tmp_m_value = tt::stepover(m_value.data() + pos); tmp_m_value.size();
             tmp_m_value = tt::stepover(tmp_m_value.data() + pos))
        {
            pos = parse.ExtractSubString(tmp_m_value);
            if (!tt::is_found(pos))
                break;
            result.emplace_back(parse);
        }
#else
        if (m_value[0] == '"')
        {
            // REVIEW: [Randalphwa - 06-26-2023] This uses tt_string_view to parse the string.
            auto view = m_value.view_substr(0, '"', '"');
            while (view.size() > 0)
            {
                result.emplace_back(view);
                view = tt::stepover(view.data() + view.size());
                view = view.view_substr(0, '"', '"');
            }
        }
        else
        {
            tt_string_vector array;
            array.SetString(m_value, ";", tt::TRIM::both);
            result = array;
        }
#endif
    }
    return result;
}

wxArrayString NodeProperty::as_wxArrayString() const
{
    wxArrayString result;

    if (m_value.size())
    {
#if 0
        // REVIEW: [Randalphwa - 06-26-2023] This works, however in wxWidgets 3.2, it converts
        // the entire string to unicode and does a unicode parsing of the string. Since the
        // original string is utf8, that's not efficient.
        if (m_value[0] == '"')
            delimiter = '"';
        else
            delimiter = ';';
        wxString str = m_value.make_wxString();
        wxPGStringTokenizer tokenizer(str, delimiter);
        while (tokenizer.HasMoreTokens())
        {
            result.Add(tokenizer.GetNextToken());
        }
#else
        if (m_value[0] == '"')
        {
            // REVIEW: [Randalphwa - 06-26-2023] This uses tt_string_view to parse the string.
            auto view = m_value.view_substr(0, '"', '"');
            while (view.size() > 0)
            {
                result.Add(view.make_wxString());
                view = tt::stepover(view.data() + view.size());
                view = view.view_substr(0, '"', '"');
            }
        }
        else
        {
            tt_view_vector array;
            array.SetString(m_value, ";", tt::TRIM::both);
            for (auto& str: array)
            {
                result.Add(str.make_wxString());
            }
        }
#endif
    }

    return result;
}

double NodeProperty::as_float() const
{
    return std::atof(m_value.c_str());
}

void NodeProperty::set_value(double value)
{
    std::array<char, 20> str;
    if (auto [ptr, ec] = std::to_chars(str.data(), str.data() + str.size(), value); ec == std::errc())
    {
        m_value.assign(str.data(), ptr);
    }
    else
    {
        m_value.clear();
    }
}

void NodeProperty::set_value(const wxColour& value)
{
    m_value.clear();
    m_value << value.Red() << ',' << value.Green() << ',' << value.Blue();
}

void NodeProperty::set_value(const wxPoint& value)
{
    m_value.clear();
    m_value << value.x << ',' << value.y;
}

void NodeProperty::set_value(const wxSize& value)
{
    m_value.clear();
    m_value << value.x << ',' << value.y;
}

void NodeProperty::set_value(const wxString& value)
{
    m_value.clear();
    m_value << value.utf8_string();
}

// All but one of the std::vector properties contain text which could have commas in it, so we need to use a '|' character as
// the separator.

tt_string NodeProperty::convert_statusbar_fields(std::vector<NODEPROP_STATUSBAR_FIELD>& fields) const
{
    tt_string result;
    for (auto& field: fields)
    {
        if (result.size())
            result << ';';
        result << field.style << '|' << field.width;
    }
    return result;
}

tt_string NodeProperty::convert_checklist_items(std::vector<NODEPROP_CHECKLIST_ITEM>& items) const
{
    tt_string result;
    for (auto& item: items)
    {
        if (result.size())
            result << ';';
        result << item.label;
        if (item.checked.size() || item.checked.atoi() != 0)
            result << '|' << item.checked;
    }
    return result;
}

tt_string NodeProperty::convert_radiobox_items(std::vector<NODEPROP_RADIOBOX_ITEM>& items) const
{
    tt_string result;
    for (auto& item: items)
    {
        if (result.size())
            result << ';';
        result << item.label;
        if (item.enabled.atoi() != 1 || item.show.atoi() != 1 || item.tooltip.size() || item.helptext.size())
            result << '|' << item.enabled << '|' << item.show << '|' << item.tooltip << '|' << item.helptext;
    }
    return result;
}

tt_string NodeProperty::convert_bmp_combo_items(std::vector<NODEPROP_BMP_COMBO_ITEM>& items) const
{
    tt_string result;
    for (auto& item: items)
    {
        if (result.size())
            result << ';';
        result << item.label;
        if (item.bitmap.size())
            result << '|' << item.bitmap;
    }
    return result;
}

std::vector<NODEPROP_STATUSBAR_FIELD> NodeProperty::as_statusbar_fields() const
{
    std::vector<NODEPROP_STATUSBAR_FIELD> result;

    // "1" is the default value, indicating nothing has been set.
    if (m_value == "1")
    {
        NODEPROP_STATUSBAR_FIELD field;
        field.style = "wxSB_NORMAL";
        field.width = "-1";
        result.emplace_back(field);
        return result;
    }

    tt_string_vector fields(m_value, ';');
    for (auto& field: fields)
    {
        tt_string_vector parts(field, '|');
        auto& item = result.emplace_back();
        if (parts.size() == 2)
        {
            item.style = parts[0];
            item.width = parts[1];
        }
        else if (parts.size() > 0)
        {
            item.style = parts[0];
            item.width = "-1";
        }
        else
        {
            item.style = "wxSB_NORMAL";
            item.width = "-1";
        }
    }

    return result;
}

std::vector<NODEPROP_CHECKLIST_ITEM> NodeProperty::as_checklist_items() const
{
    std::vector<NODEPROP_CHECKLIST_ITEM> result;

    if (m_value.size() && m_value[0] == '"' && wxGetApp().GetProjectVersion() <= minRequiredVer)
    {
        auto array = ConvertToArrayString(m_value);
        for (auto& iter: array)
        {
            NODEPROP_CHECKLIST_ITEM item;
            item.label = iter;
            result.emplace_back(item);
        }
        return result;
    }

    tt_string_vector fields(m_value, ';');
    for (auto& field: fields)
    {
        NODEPROP_CHECKLIST_ITEM item;
        tt_string_vector parts(field, '|');
        if (parts.size())
        {
            item.label = parts[0];
            if (parts.size() > 1)
            {
                item.checked = parts[1];
            }
        }
        result.emplace_back(item);
    }

    return result;
}

std::vector<NODEPROP_BMP_COMBO_ITEM> NodeProperty::as_bmp_combo_items() const
{
    std::vector<NODEPROP_BMP_COMBO_ITEM> result;

    tt_string_vector fields(m_value, ';');
    for (auto& field: fields)
    {
        NODEPROP_BMP_COMBO_ITEM item;
        tt_string_vector parts(field, '|');
        if (parts.size())
        {
            item.label = parts[0];
            if (parts.size() > 1)
            {
                item.bitmap = parts[1];
            }
        }
        result.emplace_back(item);
    }

    return result;
}

std::vector<NODEPROP_RADIOBOX_ITEM> NodeProperty::as_radiobox_items() const
{
    std::vector<NODEPROP_RADIOBOX_ITEM> result;

    tt_string_vector fields(m_value, ';');
    for (auto& field: fields)
    {
        tt_string_vector parts(field, '|');
        NODEPROP_RADIOBOX_ITEM item;
        if (parts.size() > 0)
            item.label = parts[0];
        if (parts.size() > 1)
            item.enabled = parts[1];
        if (parts.size() > 2)
            item.show = parts[2];
        if (parts.size() > 3)
            item.tooltip = parts[3];
        if (parts.size() > 4)
            item.helptext = parts[4];
        result.emplace_back(item);
    }

    return result;
}

bool NodeProperty::HasValue() const
{
    if (m_value.empty())
        return false;

    switch (type())
    {
        case type_wxSize:
            return (as_size() != wxDefaultSize);

        case type_wxPoint:
            return (as_point() != wxDefaultPosition);

        case type_animation:
            if (auto semicolonIndex = m_value.find_first_of(";"); tt::is_found(semicolonIndex))
            {
                return (semicolonIndex != 0);
            }
            return m_value.size();

        case type_image:
            if (auto semicolonIndex = m_value.find_first_of(";"); tt::is_found(semicolonIndex))
            {
                return (semicolonIndex != 0 && semicolonIndex + 2 < m_value.size());
            }
            return m_value.size();

        case type_statbar_fields:
            return (m_value == "1" || m_value == "wxSB_NORMAL|-1") ? false : true;

        default:
            return true;
    }
}
