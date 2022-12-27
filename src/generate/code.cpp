/////////////////////////////////////////////////////////////////////////////
// Purpose:   Helper class for generating code
// Author:    Ralph Walden
// Copyright: Copyright (c) 2022 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include <map>

#include <ttmultistr_wx.h>  // ttMultiString -- Class for handling multiple strings

#include "code.h"

#include "mainapp.h"        // App class
#include "node.h"           // Node class
#include "project_class.h"  // Project class

using namespace code;

// clang-format off
static const std::map<std::string_view, std::string_view, std::less<>> s_map_wx_prefix
{
    { "wxAUI_NB_BOTTOM", "wx.aui."},
    { "wxAUI_NB_CLOSE_BUTTON", "wx.aui."},
    { "wxAUI_NB_CLOSE_ON_ACTIVE_TAB", "wx.aui."},
    { "wxAUI_NB_CLOSE_ON_ALL_TABS", "wx.aui."},
    { "wxAUI_NB_MIDDLE_CLICK_CLOSE", "wx.aui."},
    { "wxAUI_NB_SCROLL_BUTTONS", "wx.aui."},
    { "wxAUI_NB_TAB_EXTERNAL_MOVE", "wx.aui."},
    { "wxAUI_NB_TAB_FIXED_WIDTH", "wx.aui."},
    { "wxAUI_NB_TAB_MOVE", "wx.aui."},
    { "wxAUI_NB_TAB_SPLIT", "wx.aui."},
    { "wxAUI_NB_TOP", "wx.aui."},
    { "wxAUI_NB_WINDOWLIST_BUTTON", "wx.aui."},

    { "wxAC_DEFAULT_STYLE", "wx.adv."},
    { "wxAC_NO_AUTORESIZE", "wx.adv."},
    { "wxNullAnimation", "wx.adv."},
    { "wxCAL_SUNDAY_FIRST", "wx.adv."},
    { "wxCAL_MONDAY_FIRST", "wx.adv."},
    { "wxCAL_SHOW_HOLIDAYS", "wx.adv."},
    { "wxCAL_NO_YEAR_CHANGE", "wx.adv."},
    { "wxCAL_NO_MONTH_CHANGE", "wx.adv."},
    { "wxCAL_SHOW_SURROUNDING_WEEKS", "wx.adv."},
    { "wxCAL_SEQUENTIAL_MONTH_SELECTION", "wx.adv."},
    { "wxCAL_SHOW_WEEK_NUMBERS", "wx.adv."},
    { "wxEL_ALLOW_NEW", "wx.adv."},
    { "wxEL_ALLOW_EDIT", "wx.adv."},
    { "wxEL_ALLOW_DELETE", "wx.adv."},
    { "wxEL_NO_REORDER", "wx.adv."},
    { "wxHL_DEFAULT_STYLE", "wx.adv."},
    { "wxHL_ALIGN_LEFT", "wx.adv."},
    { "wxHL_ALIGN_RIGHT", "wx.adv."},
    { "wxHL_ALIGN_CENTRE", "wx.adv."},
    { "wxHL_CONTEXTMENU", "wx.adv."},

};

std::map<std::string_view, std::string_view, std::less<>> g_map_class_prefix
{
    { "wxAnimationCtrl", "wx.adv."},
    { "wxBannerWindow", "wx.adv."},
    { "wxCalendarCtrl", "wx.adv."},
    { "wxDatePickerCtrl", "wx.adv."},
    { "wxEditableListBox", "wx.adv."},
    { "wxHyperlinkCtrl", "wx.adv."},
    { "wxTimePickerCtrl", "wx.adv."},

    { "wxAuiNotebook", "wx.aui."},

};
// clang-format on

Code::Code(Node* node, int language) : m_node(node), m_language(language)
{
    if (language == GEN_LANG_CPLUSPLUS)
    {
        m_break_length = wxGetApp().Preferences().get_cpp_line_length();
    }
    else if (language == GEN_LANG_PYTHON)
    {
        m_break_length = wxGetApp().Preferences().get_python_line_length();
    }
    m_break_at = m_break_length;

    // Reserve large enough for multiple lines -- goal is to avoid multiple reallocations
    m_code.reserve(256);
}

Code& Code::CheckLineLength(size_t next_str_size)
{
    if (m_auto_break && m_code.size() > m_minium_length && m_code.size() + next_str_size > m_break_at)
    {
        if (m_code.back() == ' ')
            m_code.pop_back();
        Eol().Tab();
    }
    return *this;
}

Code& Code::CheckLineLength(GenEnum::PropName next_prop_name)
{
    return CheckLineLength(m_node->as_string(next_prop_name).size());
}

Code& Code::Eol(int flag)
{
    if (flag == eol_if_empty)
    {
        if (m_code.size())
            m_code += '\n';
    }
    else if (flag == eol_if_needed)
    {
        if (m_code.size() && m_code.back() != '\n' ||
            /* If we're in a brace section, the last line will end with \n\t */
            (m_code.size() > 2 && m_code.back() == '\t' && m_code[m_code.size() - 2] == '\n'))
            m_code += '\n';
    }
    else
    {
        if (m_code.size() && m_code.back() == ' ')
            m_code.pop_back();
        m_code += '\n';
    }
    if (m_within_braces && is_cpp())
        m_code += '\t';

    if (m_auto_break)
    {
        m_break_at = m_code.size() + m_break_length;
        m_minium_length = m_code.size() + 10;
    }
    return *this;
}

Code& Code::OpenBrace()
{
    if (is_cpp())
    {
        m_within_braces = true;
        if (m_code.size() && m_code.back() != '\n')
            m_code += '\n';
        m_code += '{';
        Eol();
    }
    return *this;
}

Code& Code::CloseBrace()
{
    if (is_cpp())
    {
        m_within_braces = false;
        while (ttlib::is_whitespace(m_code.back()))
            m_code.pop_back();
        Eol().Str("}").Eol();
    }
    return *this;
}

void Code::InsertLineBreak(size_t cur_pos)
{
    ASSERT(cur_pos > 1 && cur_pos <= m_code.size());
    if (m_code[cur_pos - 1] == ' ')
    {
        m_code[cur_pos - 1] = '\n';
        m_code.insert(cur_pos, "\t");
    }
    else
    {
        m_code.insert(cur_pos, "\n");
    }
    m_break_at = cur_pos + m_break_length;
    m_minium_length = cur_pos + 10;
}

Code& Code::Tab(int tabs)
{
    while (tabs)
    {
        m_code += '\t';
        --tabs;
    }
    return *this;
}

Code& Code::Add(ttlib::sview text)
{
    CheckLineLength(text.size());

    if (is_cpp())
    {
        m_code += text;
    }
    else
    {
        if (text.find('|') != tt::npos)
        {
            bool style_set = false;
            ttlib::multiview multistr(text, "|", tt::TRIM::both);
            for (auto& iter: multistr)
            {
                if (iter.empty())
                    continue;
                if (style_set)
                    m_code += '|';
                if (iter.is_sameprefix("wx"))
                {
                    std::string_view wx_prefix = "wx.";
                    if (auto wx_iter = s_map_wx_prefix.find(iter); wx_iter != s_map_wx_prefix.end())
                    {
                        wx_prefix = wx_iter->second;
                    }

                    m_code << wx_prefix << iter.substr(2);
                }
                else
                    m_code += iter;
                style_set = true;
            }
        }
        else if (text.is_sameprefix("wx"))
        {
            std::string_view prefix = "wx.";
            if (auto iter = s_map_wx_prefix.find(text); iter != s_map_wx_prefix.end())
            {
                prefix = iter->second;
            }
            m_code << prefix << text.substr(2);
        }
        else
        {
            m_code += text;
        }
    }
    return *this;
}

Code& Code::Function(ttlib::sview text)
{
    if (is_cpp())
    {
        m_code << "->" << text;
    }
    else
    {
        m_code << '.';
        if (text.is_sameprefix("wx"))
        {
            m_code << "wx." << text.substr(2);
        }
        else
        {
            m_code += text;
        }
    }
    return *this;
}

Code& Code::ClassMethod(ttlib::sview function_name)
{
    if (is_cpp())
    {
        m_code += "::";
    }
    else
    {
        m_code += '.';
    }

    m_code += function_name;
    return *this;
}

Code& Code::FormFunction(ttlib::sview text)
{
    if (is_python())
    {
        m_code += "self.";
    }
    m_code += text;
    return *this;
}

Code& Code::Class(ttlib::sview text)
{
    if (is_cpp())
    {
        m_code += text;
    }
    else
    {
        if (text.is_sameprefix("wx"))
        {
            m_code << "wx." << text.substr(2);
        }
        else
        {
            m_code += text;
        }
    }
    return *this;
}

Code& Code::CreateClass(bool use_generic, ttlib::sview override_name)
{
    m_code += " = ";
    if (is_cpp())
    {
        m_code += "new ";
        if (m_node->HasValue(prop_derived_class))
        {
            m_code += m_node->prop_as_string(prop_derived_class);
            m_code += '(';
            return *this;
        }
    }

    ttlib::cstr class_name;
    if (override_name.empty())
        class_name = m_node->DeclName();
    else
        class_name = override_name;
    if (use_generic)
    {
        class_name.Replace("wx", "wxGeneric");
    }
    else if (m_node->isGen(gen_BookPage))
    {
        class_name = "wxPanel";
    }

    if (m_language == GEN_LANG_CPLUSPLUS)
        m_code += class_name;
    else
    {
        std::string_view prefix = "wx.";
        if (auto wx_iter = g_map_class_prefix.find(class_name); wx_iter != g_map_class_prefix.end())
        {
            prefix = wx_iter->second;
        }
        m_code << prefix << class_name.substr(2);
    }
    m_code += '(';
    return *this;
}

Code& Code::Assign(ttlib::sview class_name)
{
    m_code += " = ";
    if (m_language == GEN_LANG_CPLUSPLUS)
    {
        m_code += "new ";
    }
    else
    {
        m_code << "wx." << class_name.substr(2);
    }
    return *this;
}

Code& Code::EndFunction()
{
    m_code += ')';
    if (is_cpp())
    {
        m_code += ';';
    }
    return *this;
}

Code& Code::as_string(PropName prop_name)
{
    auto& str = m_node->as_string(prop_name);
    if (is_cpp())
    {
        CheckLineLength(str.size());
        m_code += str;
        return *this;
    }

    if (!ttlib::is_found(str.find('|')))
    {
        if (str == "wxEmptyString")
        {
            m_code += "\"\"";
        }
        else
        {
            CheckLineLength(str.size());
            if (str.is_sameprefix("wx"))
            {
                std::string_view prefix = "wx.";
                if (auto iter = s_map_wx_prefix.find(str); iter != s_map_wx_prefix.end())
                {
                    prefix = iter->second;
                }
                m_code << prefix << str.substr(2);
            }
            else
                m_code += str;
            return *this;
        }
    }

    auto cur_pos = m_code.size();

    ttlib::multiview multistr(str, "|", tt::TRIM::both);
    bool first = true;
    for (auto& iter: multistr)
    {
        if (iter.empty())
            continue;
        if (!first)
            m_code += '|';
        else
            first = false;

        if (iter == "wxEmptyString")
            m_code += "\"\"";
        else if (iter.is_sameprefix("wx"))
        {
            std::string_view prefix = "wx.";
            if (auto wx_iter = s_map_wx_prefix.find(iter); wx_iter != s_map_wx_prefix.end())
            {
                prefix = wx_iter->second;
            }
            m_code << prefix << iter.substr(2);
        }
        else
            m_code += iter;
    }

    if (m_auto_break && m_code.size() > m_break_at)
    {
        InsertLineBreak(cur_pos);
    }

    return *this;
}

Code& Code::NodeName()
{
    if (is_python() && !m_node->IsLocal() && !m_node->IsForm())
        m_code += "self.";
    m_code += m_node->get_node_name();
    return *this;
}

Code& Code::ParentName()
{
    if (is_python() && !m_node->GetParent()->IsLocal() && !m_node->GetParent()->IsForm())
        m_code += "self.";
    m_code << m_node->GetParent()->get_node_name();
    return *this;
}

bool Code::is_local_var() const
{
    return m_node->IsLocal();
}

bool Code::HasValue(GenEnum::PropName prop_name) const
{
    return m_node->HasValue(prop_name);
}

int Code::IntValue(GenEnum::PropName prop_name) const
{
    return m_node->as_int(prop_name);
}

bool Code::IsTrue(GenEnum::PropName prop_name) const
{
    return m_node->as_bool(prop_name);
}

bool Code::IsEqualTo(GenEnum::PropName prop_name, ttlib::sview text) const
{
    return (m_node->as_string(prop_name) == text);
}

bool Code::PropContains(GenEnum::PropName prop_name, ttlib::sview text) const
{
    return m_node->as_string(prop_name).contains(text);
}

size_t Code::PropSize(GenEnum::PropName prop_name) const
{
    return m_node->as_string(prop_name).size();
}

// clang-format off

// List of valid component parent types
static constexpr GenType s_GenParentTypes[] = {

    type_auinotebook,
    type_bookpage,
    type_choicebook,
    type_container,
    type_listbook,
    type_notebook,
    type_ribbonpanel,
    type_simplebook,
    type_splitter,
    type_wizardpagesimple,

};

// clang-format on

Code& Code::GetParentName()
{
    auto parent = m_node->GetParent();
    while (parent)
    {
        if (parent->IsSizer())
        {
            if (parent->IsStaticBoxSizer())
            {
                if (is_python() && !parent->IsLocal() && !parent->IsForm())
                    m_code += "self.";
                m_code += parent->get_node_name();
                Function("GetStaticBox()");
                return *this;
            }
        }
        if (parent->IsForm())
        {
            m_code += (is_cpp()) ? "this" : "self";
            return *this;
        }

        for (auto iter: s_GenParentTypes)
        {
            if (parent->isType(iter))
            {
                if (is_python() && !parent->IsLocal() && !parent->IsForm())
                    m_code += "self.";
                m_code += parent->get_node_name();
                if (parent->isGen(gen_wxCollapsiblePane))
                {
                    Function("GetPane()");
                }
                return *this;
            }
        }
        parent = parent->GetParent();
    }

    ASSERT_MSG(parent, ttlib::cstr() << m_node->get_node_name() << " has no parent!");
    return *this;
}

Code& Code::QuotedString(GenEnum::PropName prop_name)
{
    if (!m_node->HasValue(prop_name))
    {
        if (is_cpp())
        {
            CheckLineLength(sizeof("wxEmptyString"));
            m_code += "wxEmptyString";
        }
        else
        {
            m_code += "\"\"";
        }
        return *this;
    }
    else
    {
        return QuotedString(m_node->as_string(prop_name));
    }
}

Code& Code::QuotedString(ttlib::sview text)
{
    auto cur_pos = m_code.size();

    if (GetProject()->prop_as_bool(prop_internationalize))
    {
        m_code += is_cpp() ? "_(" : "wx.GetTranslation(";
    }

    // This is only used by C++, but we need to know if it was set in order to generate closing parenthesis.
    bool has_utf_char = false;
    if (is_cpp())
    {
        for (auto iter: text)
        {
            if (iter < 0)
            {
                has_utf_char = true;
                break;
            }
        }

        if (has_utf_char)
        {
            m_code += "wxString::FromUTF8(";
        }
    }

    m_code += '"';
    for (auto c: text)
    {
        switch (c)
        {
            case '"':
                m_code += "\\\"";
                break;

            // This generally isn't needed for C++, but is needed for Python
            case '\'':
                m_code += "\\'";
                break;

            case '\\':
                m_code += "\\\\";
                break;

            case '\t':
                m_code += "\\t";
                break;

            case '\n':
                m_code += "\\n";
                break;

            case '\r':
                m_code += "\\r";
                break;

            default:
                m_code += c;
                break;
        }
    }
    m_code += '"';

    if (has_utf_char)
    {
        m_code += ')';
    }
    if (GetProject()->prop_as_bool(prop_internationalize))
    {
        m_code += ')';
    }

    if (m_auto_break && m_code.size() > m_break_at)
    {
        InsertLineBreak(cur_pos);
    }

    return *this;
}

Code& Code::WxSize(GenEnum::PropName prop_name)
{
    if (m_node->prop_as_wxSize(prop_name) == wxDefaultSize)
    {
        CheckLineLength(sizeof("wxDefaultSize"));
        m_code += is_cpp() ? "wxDefaultSize" : "wx.DefaultSize";
        return *this;
    }

    auto cur_pos = m_code.size();

    bool dialog_units = m_node->value(prop_name).contains("d", tt::CASE::either);
    if (dialog_units)
    {
        CheckLineLength(sizeof("self.ConvertDialogToPixels(wxSize(999, 999))"));
        FormFunction("ConvertDialogToPixels(");
    }

    auto size = m_node->prop_as_wxSize(prop_name);
    Class("wxSize(").itoa(size.x).Comma().itoa(size.y) << ')';

    if (dialog_units)
        m_code += ')';

    if (m_auto_break && m_code.size() > m_break_at)
    {
        InsertLineBreak(cur_pos);
    }

    return *this;
}

Code& Code::Pos(GenEnum::PropName prop_name)
{
    if (m_node->prop_as_wxPoint(prop_name) == wxDefaultPosition)
    {
        CheckLineLength(sizeof("wxDefaultPosition"));
        m_code += is_cpp() ? "wxDefaultPosition" : "wx.DefaultPosition";
        return *this;
    }

    auto cur_pos = m_code.size();

    bool dialog_units = m_node->value(prop_name).contains("d", tt::CASE::either);
    if (dialog_units)
    {
        CheckLineLength(sizeof("self.ConvertDialogToPixels(wxPoint(999, 999))"));
        FormFunction("ConvertDialogToPixels(");
    }

    auto size = m_node->prop_as_wxSize(prop_name);
    Class("wxPoint(").itoa(size.x).Comma().itoa(size.y) << ')';

    if (dialog_units)
        m_code += ')';

    if (m_auto_break && m_code.size() > m_break_at)
    {
        InsertLineBreak(cur_pos);
    }

    return *this;
}

Code& Code::Style(const char* prefix, ttlib::sview force_style)
{
    bool style_set = false;
    if (force_style.size())
    {
        Add(force_style);
        style_set = true;
    }

    if (m_node->HasValue(prop_tab_position) && !m_node->prop_as_string(prop_tab_position).is_sameas("wxBK_DEFAULT"))
    {
        if (style_set)
            m_code += '|';
        style_set = true;
        as_string(prop_tab_position);
    }
    if (m_node->HasValue(prop_orientation) && !m_node->prop_as_string(prop_orientation).is_sameas("wxGA_HORIZONTAL"))
    {
        if (style_set)
            m_code += '|';
        style_set = true;
        as_string(prop_orientation);
    }

    // Note that as_string() may break the line, so recalculate any time as_string() is called
    auto cur_pos = m_code.size();

    if (m_node->isGen(gen_wxRichTextCtrl))
    {
        if (style_set)
            m_code += '|';
        style_set = true;
        Add("wxRE_MULTILINE");
    }

    if (m_node->HasValue(prop_style))
    {
        if (style_set)
            m_code += '|';
        if (prefix)
        {
            if (is_cpp())
            {
                m_code += m_node->prop_as_constant(prop_style, prefix);
            }
            else
            {
                ttlib::multiview multistr(m_node->prop_as_constant(prop_style, prefix), "|", tt::TRIM::both);
                for (auto& iter: multistr)
                {
                    if (iter.empty())
                        continue;
                    if (style_set)
                        m_code += '|';
                    if (iter.is_sameprefix("wx"))
                    {
                        std::string_view wx_prefix = "wx.";
                        if (auto wx_iter = s_map_wx_prefix.find(iter); wx_iter != s_map_wx_prefix.end())
                        {
                            wx_prefix = wx_iter->second;
                        }

                        m_code << wx_prefix << iter.substr(2);
                    }
                    else
                        m_code += iter;
                    style_set = true;
                }
            }
        }
        else
        {
            as_string(prop_style);
            cur_pos = m_code.size();
        }
        style_set = true;
    }

    if (m_node->HasValue(prop_window_style))
    {
        if (style_set)
            m_code += '|';
        style_set = true;
        as_string(prop_window_style);
        cur_pos = m_code.size();
    }

    if (m_node->isGen(gen_wxListView))
    {
        if (style_set)
            m_code += '|';
        style_set = true;
        as_string(prop_mode);
        cur_pos = m_code.size();
    }

    if (!style_set)
    {
        m_code += "0";
    }

    if (m_auto_break && m_code.size() > m_break_at)
    {
        InsertLineBreak(cur_pos);
    }

    return *this;
}

Code& Code::PosSizeFlags(bool uses_def_validator, ttlib::sview def_style)
{
    if (m_node->HasValue(prop_window_name))
    {
        // Window name is always the last parameter, so if it is specified, everything has to be generated.
        Comma();
        Pos().Comma().WxSize().Comma();
        Style();
        if (uses_def_validator)
            Comma().Add("wxDefaultValidator");
        Comma();
        QuotedString(prop_window_name).EndFunction();
        return *this;
    }

    // This could be done as a single if statement, but it is easier to read this way.
    bool style_needed = false;
    if ((m_node->HasValue(prop_style) && m_node->as_string(prop_style) != def_style))
        style_needed = true;
    else if (m_node->HasValue(prop_window_style))
        style_needed = true;
    else if (m_node->HasValue(prop_orientation) && !m_node->as_string(prop_orientation).is_sameas("wxGA_HORIZONTAL") &&
             !m_node->as_string(prop_orientation).is_sameas("wxSL_HORIZONTAL"))
        style_needed = true;
    else if (m_node->HasValue(prop_tab_position) && !m_node->as_string(prop_tab_position).is_sameas("wxBK_DEFAULT"))
        style_needed = true;
    else if (m_node->isGen(gen_wxRichTextCtrl) || m_node->isGen(gen_wxListView))
        style_needed = true;

    // Do we need a style and/or a default validator?
    if (style_needed)
    {
        Comma();
        Pos().Comma().WxSize().Comma().Style();
        if (def_style.size() && m_code.ends_with(def_style))
        {
            m_code.erase(m_code.size() - def_style.size());
        }
    }
    else if (m_node->prop_as_wxSize(prop_size) != wxDefaultSize)
    {
        Comma();
        Pos().Comma().WxSize();
    }
    else if (m_node->prop_as_wxPoint(prop_pos) != wxDefaultPosition)
    {
        Comma();
        Pos();
    }
    EndFunction();
    return *this;
}

int Code::WhatParamsNeeded(ttlib::sview default_style) const
{
    if (m_node->HasValue(prop_window_name))
    {
        return (pos_needed | size_needed | style_needed | window_name_needed);
    }

    // This could be done as a single if statement, but it is easier to read this way.
    if ((m_node->HasValue(prop_style) && m_node->as_string(prop_style) != default_style))
        return (pos_needed | size_needed | style_needed);
    else if (m_node->HasValue(prop_window_style))
        return (pos_needed | size_needed | style_needed);
    else if (m_node->HasValue(prop_orientation) && !m_node->as_string(prop_orientation).is_sameas("wxGA_HORIZONTAL") &&
             !m_node->as_string(prop_orientation).is_sameas("wxSL_HORIZONTAL"))
        return (pos_needed | size_needed | style_needed);
    else if (m_node->HasValue(prop_tab_position) && !m_node->as_string(prop_tab_position).is_sameas("wxBK_DEFAULT"))
        return (pos_needed | size_needed | style_needed);
    else if (m_node->isGen(gen_wxRichTextCtrl) || m_node->isGen(gen_wxListView))
        return (pos_needed | size_needed | style_needed);

    if (m_node->prop_as_wxSize(prop_size) != wxDefaultSize)
        return (pos_needed | size_needed);
    else if (m_node->prop_as_wxPoint(prop_pos) != wxDefaultPosition)
        return pos_needed;

    return nothing_needed;
}

Code& Code::PosSizeForceStyle(ttlib::sview force_style, bool uses_def_validator)
{
    if (m_node->HasValue(prop_window_name))
    {
        // Window name is always the last parameter, so if it is specified, everything has to be generated.
        Comma();
        Pos().Comma().WxSize().Comma();
        Style(nullptr, force_style);
        if (uses_def_validator)
            Comma().Add("wxDefaultValidator");
        Comma();
        QuotedString(prop_window_name).EndFunction();
        return *this;
    }
    else
    {
        Comma();
        Pos().Comma().WxSize().Comma().Style(nullptr, force_style);
    }
    EndFunction();
    return *this;
}

Code& Code::GenSizerFlags()
{
    // wxSizerFlags functions are chained together, so we don't want to break them. Instead,
    // shut off auto_break and then restore it when we are done, after which we can check whether
    // or note the entire wxSizerFlags() statement needs to be broken.

    bool save_auto_break = m_auto_break;
    m_auto_break = false;
    auto cur_pos = m_code.size();

    Add("wxSizerFlags");

    if (auto& prop = m_node->prop_as_string(prop_proportion); prop != "0")
    {
        m_code << '(' << prop << ')';
    }
    else
    {
        m_code << "()";
    }

    if (auto& prop = m_node->prop_as_string(prop_alignment); prop.size())
    {
        if (prop.contains("wxALIGN_CENTER"))
        {
            // Note that CenterHorizontal() and CenterVertical() require wxWidgets 3.1 or higher. Their advantage is
            // generating an assert if you try to use one that is invalid if the sizer parent's orientation doesn't
            // support it. Center() just works without the assertion check.
            m_code << ".Center()";
        }

        if (prop.contains("wxALIGN_LEFT"))
        {
            m_code += ".Left()";
        }
        else if (prop.contains("wxALIGN_RIGHT"))
        {
            m_code += ".Right()";
        }

        if (prop.contains("wxALIGN_TOP"))
        {
            m_code += ".Top()";
        }
        else if (prop.contains("wxALIGN_BOTTOM"))
        {
            m_code += ".Bottom()";
        }
    }

    if (auto& prop = m_node->prop_as_string(prop_flags); prop.size())
    {
        if (prop.contains("wxEXPAND"))
        {
            m_code += ".Expand()";
        }
        if (prop.contains("wxSHAPED"))
        {
            m_code += ".Shaped()";
        }
        if (prop.contains("wxFIXED_MINSIZE"))
        {
            m_code += ".FixedMinSize()";
        }
        if (prop.contains("wxRESERVE_SPACE_EVEN_IF_HIDDEN"))
        {
            m_code += ".ReserveSpaceEvenIfHidden()";
        }
    }

    if (auto& prop = m_node->prop_as_string(prop_borders); prop.size())
    {
        auto border_size = m_node->prop_as_string(prop_border_size);
        if (prop.contains("wxALL"))
        {
            if (border_size == "5")
                Add(".Border(").Add("wxALL)");
            else if (border_size == "10")
                Add(".DoubleBorder(").Add("wxALL)");
            else if (border_size == "15")
                Add(".TripleBorder(").Add("wxALL)");
            else
            {
                Add(".Border(").Add("wxALL, ") << border_size << ')';
            }
        }
        else
        {
            m_code << ".Border(";
            ttlib::cstr border_flags;

            if (prop.contains("wxLEFT"))
            {
                if (border_flags.size())
                    border_flags << '|';
                border_flags += is_cpp() ? "wxLEFT" : "wx.LEFT";
            }
            if (prop.contains("wxRIGHT"))
            {
                if (border_flags.size())
                    border_flags << '|';
                border_flags += is_cpp() ? "wxRIGHT" : "wx.RIGHT";
            }
            if (prop.contains("wxTOP"))
            {
                if (border_flags.size())
                    border_flags << '|';
                border_flags += is_cpp() ? "wxTOP" : "wx.TOP";
            }
            if (prop.contains("wxBOTTOM"))
            {
                if (border_flags.size())
                    border_flags << '|';
                border_flags += is_cpp() ? "wxBOTTOM" : "wx.BOTTOM";
            }
            if (border_flags.empty())
                border_flags = "0";

            m_code << border_flags << ", ";
            if (border_size == "5")
            {
                m_code += is_cpp() ? "wxSizerFlags::GetDefaultBorder())" : "wx.SizerFlags.GetDefaultBorder())";
            }
            else
            {
                m_code << border_size << ')';
            }
        }
    }

    m_auto_break = save_auto_break;

    if (m_auto_break && m_code.size() > m_break_at)
    {
        InsertLineBreak(cur_pos);
    }

    return *this;
}

void Code::GenWindowSettings()
{
    if (HasValue(prop_window_extra_style))
    {
        if (m_node->IsForm())
            FormFunction("SetExtraStyle(");
        else
            NodeName().Function("SetExtraStyle(");

        if (is_cpp())
        {
            as_string(prop_window_extra_style);
        }
        else
        {
            ttlib::multiview multistr(m_node->as_string(prop_window_extra_style), "|", tt::TRIM::both);
            bool style_set = false;

            for (auto& iter: multistr)
            {
                if (iter.empty())
                    continue;
                if (style_set)
                    m_code += '|';
                if (iter.is_sameprefix("wx"))
                    m_code << "wx." << iter.substr(2);
                else
                    m_code += iter;
                style_set = true;
            }
        }
        EndFunction();
    }

    if (IsTrue(prop_disabled))
    {
        Eol(eol_if_empty);
        if (!m_node->IsForm())
            NodeName().Function("Enable(false");
        else
            FormFunction("Enable(false");
        EndFunction();
    }

    if (IsTrue(prop_hidden))
    {
        Eol(eol_if_empty);
        if (!m_node->IsForm())
            NodeName().Function("Hide(");
        else
            FormFunction("Hide(");
        EndFunction();
    }

    bool allow_minmax { true };
    if (m_node->IsForm() && !m_node->isGen(gen_PanelForm) && !m_node->isGen(gen_wxToolBar))
        allow_minmax = false;

    if (allow_minmax && m_node->as_wxSize(prop_minimum_size) != wxDefaultSize)
    {
        Eol(eol_if_empty);
        if (!m_node->IsForm())
            NodeName().Function("SetMinSize(");
        else
            NodeName().FormFunction("SetMinSize(");
        WxSize(prop_minimum_size);
        EndFunction();
    }

    if (allow_minmax && m_node->as_wxSize(prop_maximum_size) != wxDefaultSize)
    {
        Eol(eol_if_empty);
        if (!m_node->IsForm())
            NodeName().Function("SetMaxSize(");
        else
            FormFunction("SetMaxSize(");
        WxSize(prop_maximum_size);
        EndFunction();
    }

    if (!m_node->IsForm() && !m_node->isPropValue(prop_variant, "normal"))
    {
        Eol(eol_if_empty);
        NodeName().Function("SetWindowVariant(");
        if (m_node->isPropValue(prop_variant, "small"))
            Add("wxWINDOW_VARIANT_SMALL");
        else if (m_node->isPropValue(prop_variant, "mini"))
            Add("wxWINDOW_VARIANT_MINI");
        else
            Add("wxWINDOW_VARIANT_LARGE");

        EndFunction();
    }

    if (HasValue(prop_tooltip))
    {
        Eol(eol_if_empty);
        if (!m_node->IsForm())
            NodeName().Function("SetToolTip(");
        else
            FormFunction("SetToolTip(");
        QuotedString(prop_tooltip).EndFunction();
    }

    if (HasValue(prop_context_help))
    {
        Eol(eol_if_empty);
        if (!m_node->IsForm())
            NodeName().Function("SetHelpText(");
        else
            FormFunction("SetHelpText(");
        QuotedString(prop_context_help).EndFunction();
    }

    GenFontColourSettings();
}

extern ttlib::cstr GenFontColourSettings(Node* node);

void Code::GenFontColourSettings()
{
    // TODO: [Randalphwa - 12-08-2022] Need to implement C++/Python version of GenFontColourSettings

    if (is_cpp())
    {
        auto result = ::GenFontColourSettings(m_node);
        if (result.size())
        {
            Eol(eol_if_empty);
            Add(result);
        }
    }

#if 0
    if (m_node->HasValue(prop_font))
    {
        FontProperty fontprop(m_node->get_prop_ptr(prop_font));
    }
#endif
}
