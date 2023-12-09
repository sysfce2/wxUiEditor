///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#include "ui_images.h"

#include "ribbon_ids.h"
#include "gen_enums.h"     // Enumerations for generators

using namespace GenEnum;

#include "menu_bartools.h"

MenuBarTools::MenuBarTools() : wxMenu()
{
    if (!wxImage::FindHandler(wxBITMAP_TYPE_PNG))
        wxImage::AddHandler(new wxPNGHandler);

    auto* menu_item = Append(gen_tool, "Add Tool", "Insert a normal button tool", wxITEM_NORMAL);
    menu_item->SetBitmap(wxue_img::bundle_tool_png());
    auto* menu_item_2 = Append(gen_tool_dropdown, "Add Dropdown", "Add Dropdown tool that you can add menu items to.",
        wxITEM_NORMAL);
    menu_item_2->SetBitmap(wxue_img::bundle_tool_dropdown_png());
    auto* menu_item_4 = Append(gen_toolSeparator, "Add Space", "Add space to separate tools", wxITEM_NORMAL);
    menu_item_4->SetBitmap(wxue_img::bundle_toolspacer_png());
    auto* menu_item_5 = Append(gen_toolStretchable, "Add Stretchable Space", "Add space to separate tools", wxITEM_NORMAL);
    menu_item_5->SetBitmap(wxue_img::bundle_toolStretchable_png());
    AppendSeparator();
    auto* menu_item_3 = Append(gen_wxComboBox, "Add Combobox", "Add a wxComboBox control", wxITEM_NORMAL);
    menu_item_3->SetBitmap(wxue_img::bundle_wxComboBox_png());
    auto* menu_item_6 = Append(gen_wxSlider, "Add Slider", "Add a wxSlider control", wxITEM_NORMAL);
    menu_item_6->SetBitmap(wxue_img::bundle_slider_png());
    auto* menu_item_7 = Append(gen_wxSpinCtrl, "Add Spin Control", "Add a wxSpinCtrl control", wxITEM_NORMAL);
    menu_item_7->SetBitmap(wxue_img::bundle_spin_ctrl_png());
}

// ************* End of generated code ***********
// DO NOT EDIT THIS COMMENT BLOCK!
//
// Code below this comment block will be preserved
// if the code for this class is re-generated.
//
// clang-format on
// ***********************************************
