///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#if wxCHECK_VERSION(3, 1, 6)
    #include <wx/bmpbndl.h>
#else
    #include <wx/bitmap.h>
#endif

#include <wx/button.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>

#include "python_dlg.h"

#include <wx/mstream.h>  // memory stream classes

// Convert a data array into a wxImage
inline wxImage wxueImage(const unsigned char* data, size_t size_data)
{
    wxMemoryInputStream strm(data, size_data);
    wxImage image;
    image.LoadFile(strm);
    return image;
};

namespace wxue_img
{
    extern const unsigned char wxPython_1_5x_png[765];
    extern const unsigned char wxPython_2x_png[251];
    extern const unsigned char wxPython_png[399];
}

bool PythonDlg::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, pos, size, style, name))
        return false;
    if (!wxImage::FindHandler(wxBITMAP_TYPE_PNG))
        wxImage::AddHandler(new wxPNGHandler);

    auto* bSizer1 = new wxBoxSizer(wxVERTICAL);

    auto* box_sizer = new wxBoxSizer(wxVERTICAL);

    m_staticText = new wxStaticText(this, wxID_ANY, wxString::FromUTF8("wxPython est génial n\'est-ce pas?"),
        ConvertDialogToPixels(wxPoint(50, 100)), ConvertDialogToPixels(wxSize(150, 32)), wxALIGN_CENTER_HORIZONTAL,
        "my_text");
    m_staticText->SetWindowVariant(wxWINDOW_VARIANT_LARGE);
    m_staticText->SetForegroundColour(wxColour(0, 128, 0));
    box_sizer->Add(m_staticText, wxSizerFlags().Center().Border(wxALL));
    {
#if wxCHECK_VERSION(3, 1, 6)
        wxVector<wxBitmap> bitmaps;
        bitmaps.push_back(wxueImage(wxue_img::wxPython_png, sizeof(wxue_img::wxPython_png)));
        bitmaps.push_back(wxueImage(wxue_img::wxPython_1_5x_png, sizeof(wxue_img::wxPython_1_5x_png)));
        bitmaps.push_back(wxueImage(wxue_img::wxPython_2x_png, sizeof(wxue_img::wxPython_2x_png)));
#endif
        auto* bmp = new wxStaticBitmap(this, wxID_ANY, 
#if wxCHECK_VERSION(3, 1, 6)
            wxBitmapBundle::FromBitmaps(bitmaps));
#else
            wxBitmap(wxueImage(wxue_img::wxPython_png, sizeof(wxue_img::wxPython_png))));
#endif
        box_sizer->Add(bmp, wxSizerFlags().Border(wxALL));
    }

    bSizer1->Add(box_sizer, wxSizerFlags().Expand().Border(wxALL));

    auto* stdBtn = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    bSizer1->Add(CreateSeparatedSizer(stdBtn), wxSizerFlags().Expand().Border(wxALL));

    SetSizerAndFit(bSizer1);
    Centre(wxBOTH);

    // Event handlers
    Bind(wxEVT_INIT_DIALOG, &PythonDlg::OnInit, this);

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

/////////////////// Non-generated Copyright/License Info ////////////////////
// Author:    Ralph Walden
// Copyright: Copyright (c) 2020-2022 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

void PythonDlg::OnInit(wxInitDialogEvent& event)
{
    event.Skip();  // transfer all validator data to their windows and update UI
}

#include "mainframe.h"

void MainFrame::OnPythonDlg(wxCommandEvent& WXUNUSED(event))
{
    PythonDlg dlg(this);
    dlg.ShowModal();
}