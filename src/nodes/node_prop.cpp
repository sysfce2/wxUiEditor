/////////////////////////////////////////////////////////////////////////////
// Purpose:   NodeProperty class
// Author:    Ralph Walden
// Copyright: Copyright (c) 2020-2021 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include <array>
#include <charconv>

#include <wx/propgrid/propgriddefs.h>  // wxPropertyGrid miscellaneous definitions

#include <ttmultistr.h>  // multistr -- Breaks a single string into multiple strings

#include "font_prop.h"     // FontProperty -- FontProperty class
#include "mainapp.h"       // App -- App class
#include "node.h"          // Node -- Node class
#include "node_creator.h"  // NodeCreator class
#include "utils.h"         // Utility functions that work with properties

#include "node_prop.h"

NodeProperty::NodeProperty(PropertyInfo* info, Node* node) : m_info(info), m_node(node) {}

// The advantage of placing this one-line calls to PropertyInfo (m_info) here is that it reduces the header-file
// dependency for other modeuls that need NodeProperty, and it allows for changes to PropertyInfo that don't require
// recompiling every module that included node_prop.h.

bool NodeProperty::IsDefaultValue() const
{
    return m_value.is_sameas(m_info->GetDefaultValue());
}

Type NodeProperty::GetType() const
{
    return m_info->GetType();
}

const std::string& NodeProperty::GetPropName() const
{
    return m_info->GetName();
}

int NodeProperty::as_int() const
{
    switch (GetType())
    {
        case Type::Edit_option:
        case Type::Option:
        case Type::ID:
            return g_NodeCreator.GetConstantAsInt(m_value, 0);

        case Type::Bitlist:
        {
            int result = 0;
            ttlib::multistr mstr(m_value, '|');
            for (auto& iter: mstr)
            {
                result |= g_NodeCreator.GetConstantAsInt(iter);
            }
            return result;
        }

        default:
            return m_value.atoi();  // this will return 0 if the m_value is an empty string
    }
}

wxPoint NodeProperty::as_point() const
{
    wxPoint result { -1, -1 };
    if (m_value.size())
    {
        ttlib::multiview tokens(m_value, ',');
        if (tokens.size())
        {
            if (tokens[0].size() && tokens[0].size())
                result.x = ttlib::atoi(tokens[0]);

            if (tokens.size() > 1 && tokens[1].size())
                result.y = ttlib::atoi(tokens[1]);
        }
    }
    return result;
}

wxSize NodeProperty::as_size() const
{
    wxSize result { -1, -1 };
    if (m_value.size())
    {
        ttlib::multiview tokens(m_value, ',');
        if (tokens.size())
        {
            if (tokens[0].size() && tokens[0].size())
                result.x = ttlib::atoi(tokens[0]);

            if (tokens.size() > 1 && tokens[1].size())
                result.y = ttlib::atoi(tokens[1]);
        }
    }
    return result;
}

wxColour NodeProperty::as_color() const
{
    // check for system colour
    if (m_value.is_sameprefix("wx"))
    {
        return wxSystemSettings::GetColour(ConvertToSystemColour(m_value));
    }
    else
    {
        ttlib::multistr mstr(m_value, ',');
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
    auto image = wxGetApp().GetImage(m_value);
    if (!image.IsOk())
        return wxNullBitmap;
    else
        return image;
}

ttlib::cstr NodeProperty::as_escape_text() const
{
    ttlib::cstr result;

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

std::vector<std::string> NodeProperty::as_vector() const
{
    std::vector<std::string> array;
    if (m_value.empty())
        return array;
    ttlib::cstr parse;
    std::string_view value = m_value;
    auto pos = parse.ExtractSubString(value);
    array.emplace_back(parse);

    for (value = ttlib::stepover(value.data() + pos); value.size(); value = ttlib::stepover(value.data() + pos))
    {
        pos = parse.ExtractSubString(value);
        array.emplace_back(parse);
    }

    return array;
}

wxArrayString NodeProperty::as_wxArrayString() const
{
    wxArrayString result;

    if (m_value.empty())
        return result;

    wxString str = wxString::FromUTF8(m_value);
    WX_PG_TOKENIZER2_BEGIN(str, '"')

    result.Add(token);

    WX_PG_TOKENIZER2_END()

    return result;
}

double NodeProperty::as_float() const
{
    double result;

    if (auto [p, ec] = std::from_chars(m_value.data(), m_value.data() + m_value.size(), result); ec == std::errc())
        return result;
    else
        return 0;
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
    m_value << value.wx_str();
}

bool NodeProperty::HasValue()
{
    if (m_value.empty())
        return false;

    switch (GetType())
    {
        case Type::Wxsize:
            return (as_size() != wxDefaultSize);

        case Type::Wxpoint:
            return (as_point() != wxDefaultPosition);

        case Type::Image:
            if (auto semicolonIndex = m_value.find_first_of(";"); ttlib::is_found(semicolonIndex))
            {
                // REVIEW: [KeyWorks - 08-06-2020] This reflects what IsNull() does, but seems suspicious...
                return (semicolonIndex != 0 && semicolonIndex + 2 < m_value.size());
            }
            return m_value.size();

        default:
            return true;
    }
}

void NodeProperty::splitParentProperty(std::map<ttlib::cstr, ttlib::cstr>& children) const
{
    children.clear();
    if (m_info->GetType() != Type::Parent)
    {
        return;
    }

    auto myChildren = m_info->GetChildren();
    auto child_iter = myChildren->begin();

    ttlib::multistr list(m_value, ';');
    for (auto& iter: list)
    {
        if (child_iter == myChildren->end())
        {
            return;
        }
        iter.trim(tt::TRIM::both);
        children[child_iter->m_name] = iter;
        ++child_iter;
    }
}

void NodeProperty::SplitParentProperty(std::map<wxString, wxString>* children) const
{
    children->clear();
    if (m_info->GetType() != Type::Parent)
    {
        return;
    }

    auto myChildren = m_info->GetChildren();
    auto iter = myChildren->begin();

    wxStringTokenizer tkz(m_value.wx_str(), ";", wxTOKEN_RET_EMPTY_ALL);
    while (tkz.HasMoreTokens())
    {
        if (myChildren->end() == iter)
        {
            return;
        }
        wxString child = tkz.GetNextToken();
        child.Trim(false);
        child.Trim(true);
        children->insert(std::map<wxString, wxString>::value_type(iter->m_name, child));
        ++iter;
    }
}

ttlib::cstr NodeProperty::getChildFromParent(const ttlib::cstr& childName) const
{
    std::map<ttlib::cstr, ttlib::cstr> children;
    splitParentProperty(children);

    auto child = children.find(childName);
    if (child == children.end())
    {
        return ttlib::cstr();
    }
    else
    {
        return child->second;
    }
}
