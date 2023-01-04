///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#pragma once

#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/stattext.h>

class GenerateDlg : public wxDialog
{
public:
    GenerateDlg() {}
    GenerateDlg(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Generate Code",
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr)
    {
        Create(parent, id, title, pos, size, style, name);
    }

    bool Create(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Generate Code",
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE, const wxString &name = wxDialogNameStr);

    bool is_gen_base() const { return m_gen_base_code; }
    bool is_gen_inherited() const { return m_gen_inherited_code; }
    bool is_gen_python() const { return m_gen_python_code; }
    bool is_gen_xrc() const { return m_gen_xrc_code; }

protected:

    // Event handlers

    void OnInit(wxInitDialogEvent& event);

    // Validator variables

    bool m_gen_base_code { false };
    bool m_gen_inherited_code { false };
    bool m_gen_python_code { false };
    bool m_gen_xrc_code { false };

    // Class member variables

    wxCheckBox* checkBox_6;
    wxStaticText* m_staticText;
};

// ************* End of generated code ***********
// DO NOT EDIT THIS COMMENT BLOCK!
//
// Code below this comment block will be preserved
// if the code for this class is re-generated.
//
// clang-format on
// ***********************************************

/////////////////// Non-generated Copyright/License Info ////////////////////
// Purpose:   Dialog for choosing and generating specific language file(s)
// Author:    Ralph Walden
// Copyright: Copyright (c) 2021-2022 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

namespace pugi
{
    class xml_node;
}

struct GenResults
{
    size_t file_count { 0 };
    std::vector<ttlib::cstr> msgs;
    std::vector<ttlib::cstr> updated_files;
};

// If pClassList is non-null, it must contain the base class name of every form that needs
// updating.
//
// ../generate/gen_codefiles.cpp
bool GenerateCodeFiles(GenResults& results, std::vector<ttlib::cstr>* pClassList = nullptr);

// ../generate/gen_codefiles.cpp
void GenInhertedClass(GenResults& results);

// ../generate/gen_python.cpp
bool GeneratePythonFiles(GenResults& results, std::vector<ttlib::cstr>* pClassList = nullptr);

// If out_file contains a file, it will override project xrc_file and combine_xrc settings.
//
// If NeedsGenerateCheck is true, this will not write any files, but will return true if at
// least one file needs to be generated.
//
// If pClassList is non-null, it will contain the base class name of every form that needs
// updating.
//
// ../generate/gen_xrc.cpp
bool GenerateXrcFiles(GenResults& results, ttlib::cstr out_file = {}, std::vector<ttlib::cstr>* pClassList = nullptr);

#if defined(INTERNAL_TESTING)
void GenerateTmpFiles(const std::vector<ttlib::cstr>& ClassList, pugi::xml_node root, int language = GEN_LANG_CPLUSPLUS);
#endif