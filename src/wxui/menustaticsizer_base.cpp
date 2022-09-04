////////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor -- see https://github.com/KeyWorksRW/wxUiEditor/
//
// DO NOT EDIT THIS FILE! Your changes will be lost if it is re-generated!
////////////////////////////////////////////////////////////////////////////////

#include "ui_images.h"

#include "ribbon_ids.h"
#include "gen_enums.h"     // Enumerations for generators

using namespace GenEnum;

#include "menustaticsizer_base.h"

namespace wxue_img
{
    extern const unsigned char wxStaticBoxSizer_png[199];
    extern const unsigned char wxStaticCheckBoxSizer_png[341];
    extern const unsigned char wxStaticRadioBtnSizer_png[367];
}

MenuStaticSizer::MenuStaticSizer() : wxMenu()
{
    if (!wxImage::FindHandler(wxBITMAP_TYPE_PNG))
        wxImage::AddHandler(new wxPNGHandler);

    auto* menu_item = Append(gen_wxStaticBoxSizer, "Insert wxStaticBoxSizer");
    menu_item->SetBitmap(wxue_img::bundle_wxStaticBoxSizer_png());

    auto* menu_item_2 = Append(gen_StaticCheckboxBoxSizer, "Insert CheckBox wxStaticBoxSizer");
    menu_item_2->SetBitmap(wxue_img::bundle_wxStaticCheckBoxSizer_png());

    auto* menu_item_3 = Append(gen_StaticRadioBtnBoxSizer, "Insert RadioButton wxStaticBoxSizer");
    menu_item_3->SetBitmap(wxue_img::bundle_wxStaticRadioBtnSizer_png());
}
