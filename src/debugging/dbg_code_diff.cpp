/////////////////////////////////////////////////////////////////////////////
// Purpose:   Compare code generation
// Author:    Ralph Walden
// Copyright: Copyright (c) 2021-2022 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

// CAUTION! This dialog is only used in Debug builds, and will ONLY work correctly when compiled for Windows. It will list
// all the classes in the current loaded project that need to have updated code generation. If there is at least one, the
// WinMerge button is enabled. Clicking that will generate temporary files (prefixed with ~wxue_") and then run
// `WinMergeU.exe`. Once the dialog is closed, all files prefixed with "~wxue_" will be deleted -- even if the files were
// created in a previous session.

// Note that if you running wxUiEditor under a debugger, and you compare the files then switch back to the debugger and close
// the executable, then the temporary files will NOT be deleted. Also not that if you have WinMerge running, and you alt+tab
// back to wxUiEditor and close the dialog, all those temporary files will be deleted out from underneath WinMerge.

#include <wx/dir.h>  // wxDir is a class for enumerating the files in a directory

#include "ttcwd.h"  // cwd -- Class for storing and optionally restoring the current directory

#include "dbg_code_diff.h"  // auto-generated: dbg_code_diff_base.h and dbg_code_diff_base.cpp
#include "gen_base.h"       // BaseCodeGenerator -- Generate Src and Hdr files for Base Class
#include "mainapp.h"        // App -- Main application class
#include "node.h"           // Node class
#include "pjtsettings.h"    // ProjectSettings -- Hold data for currently loaded project

#include "pugixml.hpp"

DbgCodeDiff::DbgCodeDiff(wxWindow* parent) : DbgCodeDiffBase(parent) {}

DbgCodeDiff::~DbgCodeDiff()
{
    wxDir dir;
    wxArrayString files;

    dir.GetAllFiles(".", &files, "~wxue_**.*");

    for (auto& iter: files)
    {
        wxRemoveFile(iter);
    }

    auto project = wxGetApp().GetProject();
    if (project->HasValue(prop_base_directory))
    {
        dir.GetAllFiles(project->prop_as_wxString(prop_base_directory), &files, "~wxue_**.*");

        for (auto& iter: files)
        {
            // ~wxue_.WinMerge will often be added to this list, but deleted before we start processing, so check first
            if (wxFileExists(iter))
            {
                wxRemoveFile(iter);
            }
        }
    }
}

void DbgCodeDiff::OnInit(wxInitDialogEvent& WXUNUSED(event))
{
    // First make sure all embedded images have been parsed.
    wxGetApp().GetProjectSettings()->FinishThreads();

    if (GenerateCodeFiles(this, true, &m_class_list))
    {
        for (auto& iter: m_class_list)
        {
            m_list_changes->AppendString(iter.wx_str());
        }
        m_btn->Enable();
    }
}

#if defined(_WIN32)

    #include <windows.h>

/// Converts all text to UTF16 before calling ShellExecuteW(...)
HINSTANCE winShellRun(std::string_view filename, std::string_view args, std::string_view directory,
                      INT nShow = SW_SHOWNORMAL, HWND hwndParent = NULL);

HINSTANCE winShellRun(std::string_view filename, std::string_view args, std::string_view dir, INT nShow, HWND hwndParent)
{
    std::wstring name16;
    ttlib::utf8to16(filename, name16);
    std::wstring args16;
    ttlib::utf8to16(args, args16);
    std::wstring dir16;
    ttlib::utf8to16(dir, dir16);

    return ShellExecuteW(hwndParent, NULL, name16.c_str(), args16.c_str(), dir16.c_str(), nShow);
}

#endif  // _WIN32

void DbgCodeDiff::OnWinMerge(wxCommandEvent& WXUNUSED(event))
{
    pugi::xml_document doc;
    auto root = doc.append_child("project");

    GenerateTmpFiles(m_class_list, root);

    doc.save_file("~wxue_.WinMerge");

    // WinMergeU.exe typically is not in the system PATH, and as such, wxExecute won't be able to find it. ShellExecute will
    // find the registered location for the program.

    ttlib::cwd cwd;

    // /e -- terminate with escape
    // /u -- don't add files to MRU
    winShellRun("WinMergeU.exe", "/e /u ~wxue_.WinMerge", cwd);
}
