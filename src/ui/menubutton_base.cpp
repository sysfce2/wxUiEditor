////////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor -- see https://github.com/KeyWorksRW/wxUiEditor/
//
// DO NOT EDIT THIS FILE! Your changes will be lost if it is re-generated!
////////////////////////////////////////////////////////////////////////////////

#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>

#include "ribbon_ids.h"
#include "gen_enums.h"     // Enumerations for generators

using namespace GenEnum;

#include "menubutton_base.h"

#include <wx/mstream.h>  // Memory stream classes

// Convert a data array into a wxImage
inline wxImage GetImageFromArray(const unsigned char* data, size_t size_data)
{
    wxMemoryInputStream strm(data, size_data);
    wxImage image;
    image.LoadFile(strm);
    return image;
};

namespace wxue_img
{
    extern const unsigned char stddialogbuttonsizer_png[524];
    extern const unsigned char toggle_button_png[277];
    extern const unsigned char wxButton_png[500];
    extern const unsigned char wxCommandLinkButton_png[582];
}

MenuButton::MenuButton() : wxMenu()
{
    if (!wxImage::FindHandler(wxBITMAP_TYPE_PNG))
        wxImage::AddHandler(new wxPNGHandler);

    auto menu_item = Append(gen_wxButton, wxString::FromUTF8("Insert wxButton"));
    menu_item->SetBitmap(GetImageFromArray(wxue_img::wxButton_png, sizeof(wxue_img::wxButton_png)));

    auto menu_item_2 = Append(gen_wxToggleButton, wxString::FromUTF8("Insert wxToggleButton"));
    menu_item_2->SetBitmap(GetImageFromArray(wxue_img::toggle_button_png, sizeof(wxue_img::toggle_button_png)));

    auto menu_item_3 = Append(gen_wxStdDialogButtonSizer, wxString::FromUTF8("Insert wxStdDialogButtonSizer"));
    menu_item_3->SetBitmap(GetImageFromArray(wxue_img::stddialogbuttonsizer_png, sizeof(wxue_img::stddialogbuttonsizer_png)));

    auto menu_item_4 = Append(gen_wxCommandLinkButton, wxString::FromUTF8("Insert wxCommandLinkButton"));
    menu_item_4->SetBitmap(GetImageFromArray(wxue_img::wxCommandLinkButton_png, sizeof(wxue_img::wxCommandLinkButton_png)));
}