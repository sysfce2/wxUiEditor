///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#if defined(INTERNAL_TESTING)

#include <wx/artprov.h>
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/sizer.h>

#include "../wxui/ui_images.h"

#include "xrcpreview.h"

#include <wx/mstream.h>  // memory stream classes
#include <wx/zstream.h>  // zlib stream classes

#include <memory>  // for std::make_unique

// Convert compressed SVG string into a wxBitmapBundle
#ifdef __cpp_inline_variables
inline wxBitmapBundle wxueBundleSVG(const unsigned char* data,
    size_t size_data, size_t size_svg, wxSize def_size)
#else
static wxBitmapBundle wxueBundleSVG(const unsigned char* data,
    size_t size_data, size_t size_svg, wxSize def_size)
#endif
{
    auto str = std::make_unique<char[]>(size_svg);
    wxMemoryInputStream stream_in(data, size_data);
    wxZlibInputStream zlib_strm(stream_in);
    zlib_strm.Read(str.get(), size_svg);
    return wxBitmapBundle::FromSVG(str.get(), def_size);
};

namespace wxue_img
{
    extern const unsigned char generate_svg[32526];
    extern const unsigned char xrc_preview_svg[392];
}

bool XrcPreview::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, pos, size, style, name))
        return false;

    auto* dlg_sizer = new wxBoxSizer(wxVERTICAL);

    auto* box_sizer = new wxBoxSizer(wxVERTICAL);

    m_collapsible_pane = new wxCollapsiblePane(this, wxID_ANY, "Information");
    m_collapsible_pane->Collapse();
    box_sizer->Add(m_collapsible_pane, wxSizerFlags().Border(wxALL));

    auto* box_sizer_4 = new wxBoxSizer(wxVERTICAL);

    auto* static_text2 = new wxStaticText(m_collapsible_pane->GetPane(), wxID_ANY,
        "Click Generate then Preview to display a form. You can edit the generated content and Preview that if needed.");
    box_sizer_4->Add(static_text2, wxSizerFlags().Border(wxLEFT|wxRIGHT|wxTOP, wxSizerFlags::GetDefaultBorder()));

    m_staticText = new wxStaticText(m_collapsible_pane->GetPane(), wxID_ANY,
        "Preview only works with Dialogs. Be certain the dialog will be visible and has a close box in the title bar!");
    box_sizer_4->Add(m_staticText, wxSizerFlags().Border(wxLEFT|wxRIGHT, wxSizerFlags::GetDefaultBorder()));
    m_collapsible_pane->GetPane()->SetSizerAndFit(box_sizer_4);

    auto* box_sizer_2 = new wxBoxSizer(wxHORIZONTAL);

    auto* btn_3 = new wxButton(this, wxID_ANY, "&Generate...");
        btn_3->SetBitmap(wxueBundleSVG(wxue_img::generate_svg, 32526, 44316, wxSize(16, 16)));
    btn_3->SetToolTip("Choose a form then generate the XRC code");
    box_sizer_2->Add(btn_3, wxSizerFlags().Border(wxALL));

    m_btn_preview = new wxButton(this, wxID_ANY, "&Preview...");
        m_btn_preview->SetBitmap(wxueBundleSVG(wxue_img::xrc_preview_svg, 392, 1322, wxSize(16, 16)));
    m_btn_preview->SetToolTip("Use wxXmlResource to load and display the contents");
    box_sizer_2->Add(m_btn_preview, wxSizerFlags().Border(wxALL));

    m_btn_import = new wxButton(this, wxID_ANY, "&Import");
        m_btn_import->SetBitmap(wxue_img::bundle_import_svg(16, 16));
    m_btn_import->SetToolTip("Verify that the current contents can be imported");
    box_sizer_2->Add(m_btn_import, wxSizerFlags().Border(wxALL));

    m_btn__export = new wxButton(this, wxID_ANY, "&Export...");
        m_btn__export->SetBitmap(wxArtProvider::GetBitmapBundle(wxART_FILE_SAVE_AS, wxART_MENU));
    m_btn__export->SetToolTip("Load current contents into XML, then Export to a file of your choice");
    box_sizer_2->Add(m_btn__export, wxSizerFlags().Border(wxALL));

    auto* btn3 = new wxButton(this, wxID_ANY, "&Duplicate");
        btn3->SetBitmap(wxArtProvider::GetBitmapBundle(wxART_ADD_BOOKMARK, wxART_MENU));
    btn3->SetToolTip("Load current contents into XML, then Export to a file of your choice");
    box_sizer_2->Add(btn3, wxSizerFlags().Border(wxALL));

    auto* btn_2 = new wxButton(this, wxID_ANY, "&Clear");
        btn_2->SetBitmap(wxArtProvider::GetBitmapBundle(wxART_CUT, wxART_MENU));
    btn_2->SetToolTip("Remove all of the contents");
    box_sizer_2->Add(btn_2, wxSizerFlags().Border(wxALL));

    box_sizer->Add(box_sizer_2, wxSizerFlags().Expand().Border(wxALL));

    auto* box_sizer2 = new wxBoxSizer(wxHORIZONTAL);

    m_contents = new wxStaticText(this, wxID_ANY, "C&ontents:");
    box_sizer2->Add(m_contents, wxSizerFlags(1).Bottom().Border(wxLEFT|wxRIGHT|wxTOP, wxSizerFlags::GetDefaultBorder()));

    auto* box_sizer3 = new wxBoxSizer(wxHORIZONTAL);

    m_searchCtrl = new wxSearchCtrl(this, wxID_ANY, wxEmptyString);
    m_searchCtrl->ShowSearchButton(true);
    m_searchCtrl->SetMinSize(ConvertDialogToPixels(wxSize(100, -1)));
    box_sizer3->Add(m_searchCtrl, wxSizerFlags().Border(wxLEFT|wxRIGHT|wxBOTTOM, wxSizerFlags::GetDefaultBorder()));

    box_sizer2->Add(box_sizer3, wxSizerFlags().Border(wxALL));

    box_sizer->Add(box_sizer2, wxSizerFlags().Expand().Border(wxLEFT|wxRIGHT, wxSizerFlags::GetDefaultBorder()));

    auto* box_sizer_3 = new wxBoxSizer(wxHORIZONTAL);

    m_scintilla = new wxStyledTextCtrl(this);
    {
        m_scintilla->SetLexer(wxSTC_LEX_XML);
        m_scintilla->SetEOLMode(wxSTC_EOL_LF);
        // Sets text margin scaled appropriately for the current DPI on Windows,
        // 5 on wxGTK or wxOSX
        m_scintilla->SetMarginLeft(wxSizerFlags::GetDefaultBorder());
        m_scintilla->SetMarginRight(wxSizerFlags::GetDefaultBorder());
        m_scintilla->SetProperty("fold", "1");
        m_scintilla->SetMarginWidth(1, 16);
        m_scintilla->SetMarginType(1, wxSTC_MARGIN_SYMBOL);
        m_scintilla->SetMarginMask(1, wxSTC_MASK_FOLDERS);
        m_scintilla->SetMarginSensitive(1, true);
        m_scintilla->MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_ARROW);
        m_scintilla->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_ARROWDOWN);
        m_scintilla->MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN);
        m_scintilla->MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_ARROW);
        m_scintilla->MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_BACKGROUND);
        m_scintilla->MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_BACKGROUND);
        m_scintilla->MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_BACKGROUND);
        m_scintilla->SetBackSpaceUnIndents(true);
    }
    box_sizer_3->Add(m_scintilla, wxSizerFlags(1).Expand().Border(wxALL));

    box_sizer->Add(box_sizer_3, wxSizerFlags(1).Expand().Border(wxALL));

    dlg_sizer->Add(box_sizer, wxSizerFlags(1).Expand().Border(wxALL));

    auto* stdBtn = CreateStdDialogButtonSizer(wxCLOSE|wxNO_DEFAULT);
    dlg_sizer->Add(CreateSeparatedSizer(stdBtn), wxSizerFlags().Expand().Border(wxALL));

    SetSizer(dlg_sizer);
    SetMinSize(ConvertDialogToPixels(wxSize(600, 500)));
    Fit();
    Centre(wxBOTH);

    wxPersistentRegisterAndRestore(this, "XrcPreview");

    // Event handlers
    btn_3->Bind(wxEVT_BUTTON, &XrcPreview::OnGenerate, this);
    m_btn_preview->Bind(wxEVT_BUTTON, &XrcPreview::OnPreview, this);
    m_btn_import->Bind(wxEVT_BUTTON, &XrcPreview::OnImport, this);
    m_btn__export->Bind(wxEVT_BUTTON, &XrcPreview::OnExport, this);
    btn3->Bind(wxEVT_BUTTON, &XrcPreview::OnDuplicate, this);
    btn_2->Bind(wxEVT_BUTTON, &XrcPreview::OnClear, this);
    Bind(wxEVT_INIT_DIALOG, &XrcPreview::OnInit, this);
    m_searchCtrl->Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &XrcPreview::OnSearch, this);

    return true;
}

#endif  // defined(INTERNAL_TESTING)

// ************* End of generated code ***********
// DO NOT EDIT THIS COMMENT BLOCK!
//
// Code below this comment block will be preserved
// if the code for this class is re-generated.
//
// clang-format on
// ***********************************************

/////////////////// Non-generated Copyright/License Info ////////////////////
// Purpose:   Test XRC
// Author:    Ralph Walden
// Copyright: Copyright (c) 2022 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#if defined(INTERNAL_TESTING)

    #include <wx/filedlg.h>     // wxFileDialog base header
    #include <wx/mstream.h>     // Memory stream classes
    #include <wx/xml/xml.h>     // wxXmlDocument - XML parser & data holder class
    #include <wx/xrc/xmlres.h>  // XML resources

    #include "../import/import_wxsmith.h"  // Import a wxSmith file
    #include "gen_xrc.h"                   // BaseCodeGenerator -- Generate Src and Hdr files for Base Class
    #include "mainframe.h"                 // MainFrame -- Main window frame
    #include "node.h"                      // Node class
    #include "project_handler.h"           // ProjectHandler class
    #include "undo_cmds.h"                 // InsertNodeAction -- Undoable command classes derived from UndoAction

    #include "pugixml.hpp"

    #include "xrc_list_dlg.h"

    #include "xrc_list_dlg.h"

const int node_marker = 1;

    #if defined(_DEBUG)  // Starts debug section.

void MainFrame::OnXrcPreview(wxCommandEvent& /* event */)
{
    XrcPreview dlg(this);
    dlg.ShowModal();
}

    #endif

void XrcPreview::OnClear(wxCommandEvent& WXUNUSED(event))
{
    m_scintilla->ClearAll();
}

void XrcPreview::OnGenerate(wxCommandEvent& WXUNUSED(event))
{
    XrcListDlg dlg(this);
    if (dlg.ShowModal() != wxID_OK)
        return;

    auto form = dlg.get_form();

    if (!form)
    {
        wxMessageBox("You need to select a form first.", "XRC Dialog Preview");
        return;
    }

    if (!form->isForm())
    {
        form = form->getForm();
    }

    auto doc_str = GenerateXrcStr(form, form->isGen(gen_PanelForm) ? xrc::previewing : 0);

    m_scintilla->ClearAll();
    m_scintilla->AddTextRaw(doc_str.c_str(), (to_int) doc_str.size());
    m_scintilla->SetEmptySelection(0);

    tt_view_vector m_view;
    m_view.ReadString(doc_str);

    std::string search("name=\"");

    if (form->hasProp(prop_id) && form->as_string(prop_id) != "wxID_ANY")
    {
        search = form->as_string(prop_id);
    }
    else if (form->hasValue(prop_var_name))
    {
        search = form->as_string(prop_var_name);
    }
    else
    {
        search = form->as_string(prop_class_name);
    }

    m_contents->SetLabelText("Contents: " + search);

    int line = (to_int) m_view.FindLineContaining(search);

    if (!tt::is_found(line))
        return;

    m_scintilla->MarkerDeleteAll(node_marker);
    m_scintilla->MarkerAdd(line, node_marker);

    // Unlike GetLineVisible(), this function does ensure that the line is visible.
    m_scintilla->ScrollToLine(line);
}

void XrcPreview::OnPreview(wxCommandEvent& WXUNUSED(event))
{
    auto xrc_text = m_scintilla->GetText();
    wxString dlg_name;
    auto pos = xrc_text.Find("name=\"");
    if (!tt::is_found(pos))
    {
        wxMessageBox("Could not locate the dialog's name.", "XRC Dialog Preview");
        return;
    }
    pos += (sizeof("name=\"") - 1);
    while (pos < (to_int) xrc_text.size() && xrc_text[pos] != '"')
    {
        dlg_name << xrc_text[pos++];
    }

    wxMemoryInputStream stream(xrc_text.data(), xrc_text.size());
    auto xmlDoc = std::make_unique<wxXmlDocument>(wxXmlDocument(stream));
    if (!xmlDoc->IsOk())
    {
        wxMessageBox("Invalid XRC -- wxXmlDocument can't parse it.", "XRC Dialog Preview");
        return;
    }

    auto xrc_resource = wxXmlResource::Get();
    xrc_resource->InitAllHandlers();

    wxString res_name("wxuiDlgPreview");

    if (!xrc_resource->LoadDocument(xmlDoc.release(), res_name))
    {
        wxMessageBox("wxWidgets could not parse the XRC data.", "XRC Dialog Preview");
        return;
    }

    wxDialog dlg;
    if (xrc_resource->LoadDialog(&dlg, this, dlg_name))
    {
        dlg.ShowModal();
    }
    else
    {
        wxMessageBox(wxString("Could not load ") << dlg_name << " resource.", "XRC Dialog Preview");
    }
    xrc_resource->Unload(res_name);
}

    #ifndef SCI_SETKEYWORDS
        #define SCI_SETKEYWORDS 4005
        #define SCI_GETTEXT_MSG 2182
    #endif

extern const char* g_xrc_keywords;

void XrcPreview::OnInit(wxInitDialogEvent& event)
{
    // On Windows, this saves converting the UTF8 to UTF16 and then back to ANSI.
    m_scintilla->SendMsg(SCI_SETKEYWORDS, 0, (wxIntPtr) g_xrc_keywords);

    m_scintilla->StyleSetBold(wxSTC_H_TAG, true);
    m_scintilla->StyleSetForeground(wxSTC_H_ATTRIBUTE, wxColour("#E91AFF"));
    m_scintilla->StyleSetForeground(wxSTC_H_TAG, *wxBLUE);
    m_scintilla->StyleSetForeground(wxSTC_H_COMMENT, wxColour(0, 128, 0));
    m_scintilla->StyleSetForeground(wxSTC_H_NUMBER, *wxRED);
    m_scintilla->StyleSetForeground(wxSTC_H_ENTITY, *wxRED);
    m_scintilla->StyleSetForeground(wxSTC_H_DOUBLESTRING, wxColour(0, 128, 0));
    m_scintilla->StyleSetForeground(wxSTC_H_SINGLESTRING, wxColour(0, 128, 0));
    if (UserPrefs.is_DarkMode())
    {
        auto fg = UserPrefs.GetColour(wxSYS_COLOUR_WINDOWTEXT);
        auto bg = UserPrefs.GetColour(wxSYS_COLOUR_WINDOW);
        for (int idx = 0; idx <= wxSTC_STYLE_LASTPREDEFINED; idx++)
        {
            m_scintilla->StyleSetForeground(idx, fg);
            m_scintilla->StyleSetBackground(idx, bg);
        }

        m_scintilla->StyleSetForeground(wxSTC_H_ATTRIBUTE, wxColour("#FF00FF"));
        m_scintilla->StyleSetForeground(wxSTC_H_TAG, wxColour("#80ccff"));
        m_scintilla->StyleSetForeground(wxSTC_H_COMMENT, wxColour("#85e085"));
        m_scintilla->StyleSetForeground(wxSTC_H_NUMBER, wxColour("#ff6666"));
        m_scintilla->StyleSetForeground(wxSTC_H_ENTITY, wxColour("#ff6666"));
        m_scintilla->StyleSetForeground(wxSTC_H_DOUBLESTRING, wxColour("#85e085"));
        m_scintilla->StyleSetForeground(wxSTC_H_SINGLESTRING, wxColour("#85e085"));
    }
    else
    {
        m_scintilla->StyleSetForeground(wxSTC_H_ATTRIBUTE, wxColour("#FF00FF"));
        m_scintilla->StyleSetForeground(wxSTC_H_TAG, *wxBLUE);
        m_scintilla->StyleSetForeground(wxSTC_H_COMMENT, wxColour(0, 128, 0));
        m_scintilla->StyleSetForeground(wxSTC_H_NUMBER, *wxRED);
        m_scintilla->StyleSetForeground(wxSTC_H_ENTITY, *wxRED);
        m_scintilla->StyleSetForeground(wxSTC_H_DOUBLESTRING, wxColour(0, 128, 0));
        m_scintilla->StyleSetForeground(wxSTC_H_SINGLESTRING, wxColour(0, 128, 0));
    }

    wxFont font(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    m_scintilla->StyleSetFont(wxSTC_STYLE_DEFAULT, font);

    m_scintilla->MarkerDefine(node_marker, wxSTC_MARK_BOOKMARK, wxNullColour, *wxGREEN);

    event.Skip();
}

void XrcPreview::OnImport(wxCommandEvent& WXUNUSED(event))
{
    auto xrc_text = m_scintilla->GetText();
    pugi::xml_document doc;
    {
        // Place this in a block so that the string is destroyed before we process the XML
        // document (to save allocated memory).
        auto result = doc.load_string(xrc_text.utf8_string());
        if (!result)
        {
            wxMessageBox("Error parsing XRC document: " + tt_string(result.description()), "XRC Import Test");
            return;
        }
    }

    auto root = doc.first_child();
    if (!tt::is_sameas(root.name(), "resource", tt::CASE::either))
    {
        wxMessageBox("Invalid XRC -- no resource object", "Import XRC Test");
        return;
    }

    g_pMsgLogging->ShowLogger();
    wxYield();

    MSG_INFO("--- Importing XRC document ---");

    WxSmith doc_import;

    // If this is an actual form rather than the project, then there will only be one child
    // object, which is the form.
    for (auto& iter: root.children())
    {
        auto new_node = doc_import.CreateXrcNode(iter, nullptr);
    }

    MSG_INFO("--- Import completed ---");
}

void XrcPreview::OnExport(wxCommandEvent& WXUNUSED(event))
{
    tt_string path = Project.getProjectPath();
    #if defined(_WIN32)
    path.forwardslashestoback();
    #endif  // _WIN32
    wxFileDialog dialog(this, "Export Project As XRC", path.make_wxString(), "preview_test.xrc", "XRC File (*.xrc)|*.xrc",
                        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (dialog.ShowModal() == wxID_OK)
    {
        tt_string filename = dialog.GetPath().utf8_string();

        std::string buf;
        buf.reserve(m_scintilla->GetTextLength() + 1);
        auto len = m_scintilla->GetTextLength() + 1;
        m_scintilla->SendMsg(SCI_GETTEXT_MSG, len, (wxIntPtr) buf.data());

        pugi::xml_document doc;
        doc.load_string(buf.c_str());

        if (!doc.save_file_stream(filename))
        {
            wxMessageBox(wxString("An unexpected error occurred exporting ") << filename.make_wxString(), "Export XRC");
        }
    }
}

void XrcPreview::OnDuplicate(wxCommandEvent& WXUNUSED(event))
{
    auto xrc_text = m_scintilla->GetText();
    pugi::xml_document doc;
    {
        // Place this in a block so that the string is destroyed before we process the XML
        // document (to save allocated memory).
        auto result = doc.load_string(xrc_text.utf8_string());
        if (!result)
        {
            wxMessageBox("Error parsing XRC document: " + tt_string(result.description()), "XRC Import Test");
            return;
        }
    }

    auto root = doc.first_child();
    if (!tt::is_sameas(root.name(), "resource", tt::CASE::either))
    {
        wxMessageBox("Invalid XRC -- no resource object", "Import XRC Test");
        return;
    }

    WxSmith doc_import;

    auto first_child = root.first_child();
    auto new_node = doc_import.CreateXrcNode(first_child, nullptr);
    if (new_node)
    {
        Project.FixupDuplicatedNode(new_node.get());
        tt_string undo_str("duplicate ");
        undo_str << new_node->declName();
        wxGetMainFrame()->PushUndoAction(
            std::make_shared<InsertNodeAction>(new_node.get(), Project.getProjectNode(), undo_str));
        wxGetMainFrame()->FireCreatedEvent(new_node);
        wxGetMainFrame()->SelectNode(new_node, evt_flags::fire_event | evt_flags::force_selection);
    }
    else
    {
        MSG_ERROR("Failed to create node");
    }
}

void XrcPreview::OnSearch(wxCommandEvent& event)
{
    m_scintilla->SetSelectionStart(m_scintilla->GetSelectionEnd());
    m_scintilla->SearchAnchor();
    auto srch_string = event.GetString();
    auto result = m_scintilla->SearchNext(0, event.GetString());

    if (result == wxSTC_INVALID_POSITION)
    {
        wxMessageBox(wxString() << event.GetString() << " not found.", "Not Found", wxICON_ERROR);
    }
    else
    {
        m_scintilla->EnsureCaretVisible();
    }
}

#endif  // defined(INTERNAL_TESTING)
