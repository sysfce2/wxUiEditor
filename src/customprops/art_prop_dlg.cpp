///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#include <wx/bmpbndl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbox.h>

#include "art_prop_dlg.h"

bool ArtBrowserDialog::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, wxWindow::FromDIP(pos), wxWindow::FromDIP(size), style, name))
        return false;

    auto* parent_sizer = new wxBoxSizer(wxVERTICAL);

    auto* box_sizer = new wxBoxSizer(wxHORIZONTAL);

    auto* box_sizer4 = new wxBoxSizer(wxVERTICAL);

    m_list = new wxListView(this, wxID_ANY, wxDefaultPosition, FromDIP(wxSize(250, 400)),
        wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxBORDER_SUNKEN|wxLC_REPORT);
    box_sizer4->Add(m_list, wxSizerFlags().Border(wxRIGHT, 10));

    box_sizer->Add(box_sizer4, wxSizerFlags().Border(wxALL));

    auto* box_sizer3 = new wxBoxSizer(wxVERTICAL);

    m_text = new wxStaticText(this, wxID_ANY, "Size: 333x333");
    box_sizer3->Add(m_text, wxSizerFlags().Border(wxALL));

    auto* static_box = new wxStaticBoxSizer(wxVERTICAL, this);

    m_canvas = new wxStaticBitmap(static_box->GetStaticBox(), wxID_ANY, wxNullBitmap);
    static_box->Add(m_canvas, wxSizerFlags());

    box_sizer3->Add(static_box, wxSizerFlags().Border(wxALL));

    box_sizer->Add(box_sizer3, wxSizerFlags(1).Border(wxALL));

    parent_sizer->Add(box_sizer, wxSizerFlags().Border(wxALL));

    auto* box_sizer2 = new wxBoxSizer(wxHORIZONTAL);

    auto* staticText = new wxStaticText(this, wxID_ANY, "Client:");
    box_sizer2->Add(staticText, wxSizerFlags().Center().Border(wxALL));

    m_choice_client = new wxChoice(this, wxID_ANY);
    box_sizer2->Add(m_choice_client, wxSizerFlags(1).Border(wxALL));

    parent_sizer->Add(box_sizer2, wxSizerFlags().Border(wxALL));

    auto* stdBtn = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    parent_sizer->Add(CreateSeparatedSizer(stdBtn), wxSizerFlags().Expand().Border(wxALL));

    SetSizerAndFit(parent_sizer);
    Centre(wxBOTH);

    // Event handlers
    m_choice_client->Bind(wxEVT_CHOICE, &ArtBrowserDialog::OnChooseClient, this);
    m_list->Bind(wxEVT_LIST_ITEM_SELECTED, &ArtBrowserDialog::OnSelectItem, this);

    return true;
}

// ************* End of generated code ***********
// DO NOT EDIT THIS COMMENT BLOCK!
//
// Code below this comment block will be preserved
// if the code for this class is re-generated.
//
// clang-format on
// ***********************************************

//
// The original file was missing the comment block ending the generated code!
//
// The entire original file has been copied below this comment block.

/////////////////// Non-generated Copyright/License Info ////////////////////
// Purpose:   Art Property Dialog for image property
// Author:    Ralph Walden
// Copyright: Copyright (c) 2021-2023 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include <set>

#include <wx/artprov.h>  // wxArtProvider class

#include "mainframe.h"  // MainFrame -- Main window frame
#include "node.h"       // Node class

extern std::set<std::string> set_art_ids;  // defined in pg_image.cpp

ArtBrowserDialog::ArtBrowserDialog(wxWindow* parent, const ImageProperties& img_props)
{
    Create(parent);

    m_list->AppendColumn(wxEmptyString);

    m_choice_client->Append("wxART_TOOLBAR");
    m_choice_client->Append("wxART_MENU");
    m_choice_client->Append("wxART_BUTTON");
    m_choice_client->Append("wxART_FRAME_ICON");
    m_choice_client->Append("wxART_CMN_DIALOG");
    m_choice_client->Append("wxART_HELP_BROWSER");
    m_choice_client->Append("wxART_MESSAGE_BOX");
    m_choice_client->Append("wxART_OTHER");

    if (auto pos = img_props.image.find('|'); tt::is_found(pos))
    {
        m_client = img_props.image.subview(pos + 1).make_wxString();
    }
    else
    {
        if (auto node = wxGetFrame().getSelectedNode(); node)
        {
            if (node->isType(type_tool) || node->isType(type_ribbontool) || node->isType(type_aui_tool))
            {
                m_client = "wxART_TOOLBAR";
            }
            else if (node->isType(type_menuitem))
            {
                m_client = "wxART_MENU";
            }
            else if (node->isGen(gen_wxButton))
            {
                m_client = "wxART_BUTTON";
            }
            else
            {
                m_client = "wxART_OTHER";
            }
        }
        else
        {
            m_client = "wxART_OTHER";
        }
    }

    m_choice_client->SetStringSelection(m_client);
    ChangeClient();
}

void ArtBrowserDialog::ChangeClient()
{
    // Save the current selection before all items are deleted. Restore the selection after the new items have been added.
    auto sel = m_list->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (sel < 0)
        sel = 0;

    m_list->DeleteAllItems();

    int index = 0;
    wxVector<wxBitmapBundle> bitmap_bundles;
    for (auto& iter: set_art_ids)
    {
        if (auto bundle = wxArtProvider::GetBitmapBundle(iter, wxART_MAKE_CLIENT_ID_FROM_STR(m_client), wxSize(16, 16));
            bundle.IsOk())
        {
            bitmap_bundles.push_back(bundle);
            m_list->InsertItem(index, iter, (to_int) (bitmap_bundles.size() - 1));
            m_list->SetItemPtrData(index++, reinterpret_cast<wxUIntPtr>(iter.c_str()));
        }
    }
    m_list->SetSmallImages(bitmap_bundles);

    m_list->SetColumnWidth(0, wxLIST_AUTOSIZE);
    m_list->SetItemState(sel, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void ArtBrowserDialog::OnChooseClient(wxCommandEvent& WXUNUSED(event))
{
    m_client = m_choice_client->GetStringSelection();
    ChangeClient();
}

void ArtBrowserDialog::OnSelectItem(wxListEvent& event)
{
    m_id = reinterpret_cast<const char*>(event.GetData());
    if (!m_id)
        return;
    auto bmp = wxArtProvider::GetBitmap(m_id, wxART_MAKE_CLIENT_ID_FROM_STR(m_client));
    ASSERT(bmp.IsOk());
    if (bmp.IsOk())
    {
        m_canvas->SetSize(bmp.GetWidth(), bmp.GetHeight());
        m_canvas->SetBitmap(bmp);
        m_text->SetLabel(wxString().Format("Size: %d x %d", bmp.GetWidth(), bmp.GetHeight()));
        Layout();
    }
    Refresh();
}

wxString ArtBrowserDialog::GetResults()
{
    wxString results = m_id;
    results << '|' << m_client;
    return results;
}
