/////////////////////////////////////////////////////////////////////////////
// Purpose:   Generate Ruby code files
// Author:    Ralph Walden
// Copyright: Copyright (c) 2023 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include <set>
#include <unordered_set>

#include "mainframe.h"

#include "base_generator.h"   // BaseGenerator -- Base widget generator class
#include "code.h"             // Code -- Helper class for generating code
#include "file_codewriter.h"  // FileCodeWriter -- Classs to write code to disk
#include "gen_base.h"         // BaseCodeGenerator -- Generate Src and Hdr files for Base Class
#include "gen_common.h"       // Common component functions
#include "gen_results.h"      // Code generation file writing functions
#include "image_gen.h"        // Functions for generating embedded images
#include "image_handler.h"    // ImageHandler class
#include "node.h"             // Node class
#include "project_handler.h"  // ProjectHandler class
#include "utils.h"            // Miscellaneous utilities
#include "write_code.h"       // Write code to Scintilla or file

#include "pugixml.hpp"

// This *must* be written on a line by itself with *no* indentation.
const char* ruby_begin_cmt_block = "=begin";

// This *must* be written on a line by itself with *no* indentation.
const char* ruby_end_cmt_block = "=end";

#if defined(_DEBUG)
static const std::vector<tt_string> disable_list = {
    "Metrics/MethodLength",
    "Metrics/ParameterLists",
    "Style/Documentation",
    "Metrics/AbcSize",
};
#endif  // _DEBUG

bool GenerateRubyFiles(GenResults& results, std::vector<tt_string>* pClassList)
{
    if (Project.getChildCount() == 0)
    {
        wxMessageBox("You cannot generate any code until you have added a top level form.", "Code Generation");
        return false;
    }
    tt_cwd cwd(true);
    Project.ChangeDir();
    tt_string path;

    bool generate_result = true;
    std::vector<Node*> forms;
    Project.CollectForms(forms);

#if defined(_DEBUG) || defined(INTERNAL_TESTING)
    results.StartClock();
#endif

    for (const auto& form: forms)
    {
        if (auto& base_file = form->as_string(prop_ruby_file); base_file.size())
        {
            path = Project.getBaseDirectory(form, GEN_LANG_RUBY);
            if (path.size())
            {
                path.append_filename(base_file);
            }
            else
            {
                path = base_file;
            }

            path.make_absolute();
            path.backslashestoforward();
        }
        else
        {
#if !defined(_DEBUG)
            // For a lot of wxRuby testing of projects with multiple dialogs, there may
            // only be a few forms where wxRuby generation is being tested, so don't nag in
            // Debug builds. :-)
            results.msgs.emplace_back() << "No Ruby filename specified for " << form->as_string(prop_class_name) << '\n';
#endif  // _DEBUG
            continue;
        }

        try
        {
            BaseCodeGenerator codegen(GEN_LANG_RUBY);

            auto h_cw = std::make_unique<FileCodeWriter>(path);
            h_cw->SetTabToSpaces(2);
            codegen.SetHdrWriteCode(h_cw.get());

            // REVIEW: [Randalphwa - 07-13-2023] The .rb extension should work, however on
            // Windows, a .rbw extension can be used as well to launch in a new console window.
            path.replace_extension(".rb");
            auto cpp_cw = std::make_unique<FileCodeWriter>(path);
            cpp_cw->SetTabToSpaces(2);
            codegen.SetSrcWriteCode(cpp_cw.get());

            codegen.GenerateRubyClass(form);
            int flags = flag_no_ui;
            if (pClassList)
                flags |= flag_test_only;
            auto retval = cpp_cw->WriteFile(GEN_LANG_RUBY, flags);

            if (retval > 0)
            {
                if (!pClassList)
                {
                    results.updated_files.emplace_back(path);
                }
                else
                {
                    if (form->isGen(gen_Images))
                        pClassList->emplace_back(GenEnum::map_GenNames[gen_Images]);
                    else
                        pClassList->emplace_back(form->as_string(prop_class_name));
                    continue;
                }
            }

            else if (retval < 0)
            {
                results.msgs.emplace_back() << "Cannot create or write to the file " << path << '\n';
            }
            else  // retval == result::exists
            {
                ++results.file_count;
            }
        }
        catch (const std::exception& TESTING_PARAM(e))
        {
            MSG_ERROR(e.what());
            wxMessageBox(tt_string("An internal error occurred generating code files for ")
                             << form->as_string(prop_ruby_file),
                         "Code generation");
            continue;
        }
    }

#if defined(_DEBUG) || defined(INTERNAL_TESTING)
    results.EndClock();
#endif

    return generate_result;
}

using namespace GenEnum;

// clang-format off

inline constexpr const auto txt_PyPerlRubyCmtBlock =
R"===(###############################################################################
# Code generated by wxUiEditor -- see https://github.com/KeyWorksRW/wxUiEditor/
#
# Do not edit any code above the "End of generated code" comment block.
# Any changes before that block will be lost if it is re-generated!
###############################################################################

)===";

// clang-format on

// Equivalent to GenerateBaseClass in gen_base.cpp

void BaseCodeGenerator::GenerateRubyClass(Node* form_node, PANEL_PAGE panel_type)
{
    Code code(form_node, GEN_LANG_RUBY);

    m_embedded_images.clear();

    m_form_node = form_node;
    m_ImagesForm = nullptr;

    for (const auto& form: Project.getChildNodePtrs())
    {
        if (form->isGen(gen_folder))
        {
            for (const auto& child_form: form->getChildNodePtrs())
            {
                if (child_form->isGen(gen_Images))
                {
                    m_ImagesForm = child_form.get();
                    break;
                }
            }
            break;
        }

        else if (form->isGen(gen_Images))
        {
            m_ImagesForm = form.get();
            break;
        }
    }

    EventVector events;
    std::thread thrd_get_events(&BaseCodeGenerator::CollectEventHandlers, this, form_node, std::ref(events));

    // Caution! CollectImageHeaders() needs access to m_baseFullPath, so don't start this
    // thread until it has been set!
    //
    // thrd_collect_img_headers will populate m_embedded_images;

    std::set<std::string> img_include_set;
    std::thread thrd_collect_img_headers(&BaseCodeGenerator::CollectImageHeaders, this, form_node,
                                         std::ref(img_include_set));

    // If the code files are being written to disk, then UpdateEmbedNodes() has already been called.
    if (panel_type != NOT_PANEL)
    {
        ProjectImages.UpdateEmbedNodes();
    }

    std::vector<Node*> forms;
    Project.CollectForms(forms);

    m_panel_type = panel_type;

    m_header->Clear();
    m_source->Clear();
    m_source->SetLastLineBlank();

    if (m_panel_type == NOT_PANEL)
    {
        m_source->writeLine(txt_PyPerlRubyCmtBlock);

        if (Project.as_bool(prop_disable_rubo_cop))
        {
#if defined(_DEBUG)
            for (auto& iter: disable_list)
            {
                m_source->writeLine("# rubocop:disable " + iter);
            }
#else
            m_source->writeLine("# rubocop:disable all");
#endif
            m_source->writeLine();
        }
    }

    if (form_node->isGen(gen_Images))
    {
        thrd_get_events.join();
        thrd_collect_img_headers.join();
        GenerateRubyImagesForm();
        return;
    }

    m_header->writeLine(tt_string("# Sample inherited class from ") << form_node->as_string(prop_class_name));
    m_header->writeLine();
    m_source->writeLine("WX_GLOBAL_CONSTANTS = true unless defined? WX_GLOBAL_CONSTANTS\n\nrequire 'wx/core'");
    m_header->writeLine("WX_GLOBAL_CONSTANTS = true unless defined? WX_GLOBAL_CONSTANTS\n\nrequire 'wx/core'");

    std::set<std::string> imports;

    auto GatherImportModules = [&](Node* node, auto&& GatherImportModules) -> void
    {
        if (auto* gen = node->getGenerator(); gen)
        {
            gen->GetRubyImports(node, imports);
        }
        for (auto& child: node->getChildNodePtrs())
        {
            GatherImportModules(child.get(), GatherImportModules);
        }
    };
    GatherImportModules(form_node, GatherImportModules);

    for (const auto& import: imports)
    {
        m_source->writeLine(import);
        m_header->writeLine(import);
    }
    m_source->writeLine();
    m_header->writeLine();

    if (form_node->hasValue(prop_relative_require_list))
    {
        tt_string_vector list;
        list.SetString(form_node->as_string(prop_relative_require_list));
        for (auto& iter: list)
        {
            iter.remove_extension();
            m_source->writeLine(tt_string("require_relative '") << iter << '\'');
        }
        if (list.size())
        {
            m_source->writeLine();
        }
    }

    if (form_node->isGen(gen_wxFrame) && form_node->as_bool(prop_import_all_dialogs))
    {
        for (auto& form: forms)
        {
            if ((form->isGen(gen_wxDialog) || form->isGen(gen_wxWizard)) && form->hasValue(prop_ruby_file))
            {
                tt_string import_name(form->as_string(prop_ruby_file).filename());
                import_name.remove_extension();
                m_source->writeLine(tt_string("require '") << import_name << "'");
            }
        }
    }

    m_set_enum_ids.clear();
    m_set_const_ids.clear();
    BaseCodeGenerator::CollectIDs(form_node, m_set_enum_ids, m_set_const_ids);

    int id_value = wxID_HIGHEST;
    for (auto& iter: m_set_enum_ids)
    {
        m_source->writeLine(tt_string() << '$' << iter << " = " << id_value++);
    }
    for (auto& iter: m_set_const_ids)
    {
        if (tt::contains(iter, " wx"))
        {
            tt_string id = '$' + iter;
            id.Replace(" wx", " Wx::", true, tt::CASE::exact);
            m_source->writeLine(id);
        }
        else
        {
            m_source->writeLine('$' + iter);
        }
    }

    thrd_collect_img_headers.join();
    if (m_embedded_images.size())
    {
        m_source->writeLine();

        // TODO: [Randalphwa - 07-13-2023] Need to figure out how to handle images in wxRuby. I
        // don't know yet if we can use the zlib + base64 encoding that we use for wxPython.
    }

    m_source->writeLine();
    m_header->writeLine();
    m_header->writeLine(tt_string("requires '") << form_node->as_string(prop_python_file) << "'\n");
    m_header->writeLine();

    if (m_form_node->hasValue(prop_ruby_insert))
    {
        tt_string convert(m_form_node->as_string(prop_ruby_insert));
        convert.Replace("@@", "\n", tt::REPLACE::all);
        tt_string_vector lines(convert, '\n', tt::TRIM::right);
        for (auto& line: lines)
        {
            m_source->doWrite(line);
            m_source->doWrite("\n");
        }
        m_source->doWrite("\n");
    }

    tt_string inherit_name = form_node->as_string(prop_ruby_inherit_name);
    if (inherit_name.empty())
    {
        inherit_name += " < " + form_node->as_string(prop_class_name);
    }
    if (inherit_name.size())
    {
        tt_string inherit("class ");
        inherit << inherit_name;
        inherit << form_node->as_string(prop_ruby_file) << "." << form_node->as_string(prop_class_name) << "):";

        m_header->writeLine(inherit);
        m_header->Indent();
        m_header->writeLine("def initialize(parent)");
        m_header->writeLine("end");
        m_header->Unindent();
        m_header->writeLine();
    }

    thrd_get_events.join();

    auto generator = form_node->getNodeDeclaration()->getGenerator();
    code.clear();
    if (generator->ConstructionCode(code))
    {
        m_source->writeLine(code);
        m_source->writeLine();
        m_source->Indent();
        m_source->Indent();

        id_value = wxID_HIGHEST;
        for (auto& iter: m_set_enum_ids)
        {
            m_source->writeLine(tt_string() << '@' << iter << id_value++);
        }

        if (id_value > 1)
        {
            // If at least one id was set, add a blank line
            m_source->writeLine();
        }
    }

    code.clear();
    if (generator->SettingsCode(code))
    {
        if (code.size())
        {
            m_source->writeLine(code);
            m_source->writeLine();
        }
    }

    if (form_node->getPropPtr(prop_window_extra_style))
    {
        code.clear();
        code.GenWindowSettings();
        if (code.size())
        {
            m_source->writeLine(code);
        }
    }

    m_source->SetLastLineBlank();
    for (const auto& child: form_node->getChildNodePtrs())
    {
        if (child->isGen(gen_wxContextMenuEvent))
            continue;
        GenConstruction(child.get());
    }

    code.clear();
    if (generator->AfterChildrenCode(code))
    {
        if (code.size())
        {
            m_source->writeLine();
            m_source->writeLine(code);
        }
    }

    // TODO: [Randalphwa - 07-13-2023] Need to figure out if wxRuby supports persistence

    if (events.size())
    {
        m_source->writeLine();
        m_source->writeLine("# Event handlers");
        GenSrcEventBinding(form_node, events);
        m_source->writeLine("\tend", indent::none);
        m_source->SetLastLineBlank();

        m_source->ResetIndent();
        m_source->writeLine();
        m_source->Indent();
        GenRubyEventHandlers(events);
    }
    else
    {
        m_source->ResetIndent();
        m_source->writeLine("\tend", indent::none);
    }

    if (m_form_node->isGen(gen_wxWizard))
    {
        code.clear();
        code.Eol().Str("# Add the following below the comment block to add a simple");
        code.Eol().Str("# Run() function to launch the wizard").Eol().Str("=begin");
        // see for an example C:\rwCode\wxRuby3\samples\dialogs\wizard.rb
        code.Eol().Str("=end").Eol();
        m_source->writeLine(code);
    }

    // Make certain indentation is reset after all construction code is written
    m_source->ResetIndent();
    m_source->writeLine("end\n\n", indent::none);

    m_header->ResetIndent();

    // TODO: [Randalphwa - 07-13-2023] If we use embedded images, we need to write them out here.
#if 0
    std::sort(m_embedded_images.begin(), m_embedded_images.end(),
              [](const EmbeddedImage* a, const EmbeddedImage* b)
              {
                  return (a->array_name.compare(b->array_name) < 0);
              });
#endif

    if (m_panel_type == NOT_PANEL)
    {
        if (Project.as_bool(prop_disable_rubo_cop))
        {
#if defined(_DEBUG)
            for (auto& iter: disable_list)
            {
                m_source->writeLine("# rubocop:enable " + iter);
            }
#else
            m_source->writeLine("# rubocop:enable all");
#endif  // _DEBUG
            m_source->writeLine();
        }
    }
}

tt_string MakeRubyPath(Node* node)
{
    tt_string path;
    Node* form = node->getForm();

    if (auto& base_file = form->as_string(prop_ruby_file); base_file.size())
    {
        path = Project.getBaseDirectory(form, GEN_LANG_RUBY);
        if (path.size())
        {
            path.append_filename(base_file);
        }
        else
        {
            path = base_file;
        }

        path.make_absolute();
        path.backslashestoforward();
    }

    if (path.empty())
        path = "./";
    path.make_absolute();
    path.remove_filename();
    return path;
}
