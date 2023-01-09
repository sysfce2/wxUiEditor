///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#pragma once

#include <wx/bitmap.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/panel.h>
#include <wx/ribbon/art.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/control.h>
#include <wx/ribbon/page.h>
#include <wx/ribbon/toolbar.h>
#include <wx/sizer.h>

class RibbonPanelBase : public wxPanel
{
public:
    RibbonPanelBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString &name = wxPanelNameStr);

protected:

    // Virtual event handlers -- override them in your derived class

    virtual void OnDropDown(wxRibbonToolBarEvent& event) { event.Skip(); }
    virtual void OnToolClick(wxRibbonToolBarEvent& event) { event.Skip(); }

    // Class member variables

    wxBoxSizer* parent_sizer;
    wxRibbonBar* m_rbnBar;
    wxRibbonPage* m_page_bars;
};

namespace wxue_img
{
    // Images declared in this class module:

    extern const unsigned char WXPOPupTransientWindow_png[358];
    extern const unsigned char auinotebook_png[284];
    extern const unsigned char book_page_png[229];
    extern const unsigned char calendar_png[937];
    extern const unsigned char colourPickerIcon_png[534];
    extern const unsigned char customControl_png[740];
    extern const unsigned char dataviewlist_column_png[224];
    extern const unsigned char datepicker_png[1047];
    extern const unsigned char dirPicker_png[690];
    extern const unsigned char doc_mdi_parent_frame_png[543];
    extern const unsigned char filePicker_png[705];
    extern const unsigned char flex_grid_sizer_png[139];
    extern const unsigned char fontPicker_png[763];
    extern const unsigned char gauge_png[260];
    extern const unsigned char genericdir_ctrl_png[328];
    extern const unsigned char grid_bag_sizer_png[145];
    extern const unsigned char grid_png[171];
    extern const unsigned char grid_sizer_png[127];
    extern const unsigned char htmlwin_png[1053];
    extern const unsigned char hyperlink_ctrl_png[329];
    extern const unsigned char infobar_png[556];
    extern const unsigned char menu_png[795];
    extern const unsigned char menuitem_png[481];
    extern const unsigned char pagectrl_png[601];
    extern const unsigned char propgriditem_png[436];
    extern const unsigned char propgridpage_png[237];
    extern const unsigned char radio_box_png[488];
    extern const unsigned char ribbon_button_png[220];
    extern const unsigned char ribbon_gallery_item_png[679];
    extern const unsigned char ribbon_page_png[368];
    extern const unsigned char ribbon_panel_png[392];
    extern const unsigned char richtextctrl_png[736];
    extern const unsigned char scintilla_png[729];
    extern const unsigned char search_png[800];
    extern const unsigned char separator_png[306];
    extern const unsigned char sizer_horizontal_png[129];
    extern const unsigned char sizer_png[133];
    extern const unsigned char spacer_png[183];
    extern const unsigned char static_bitmap_png[778];
    extern const unsigned char static_line_png[122];
    extern const unsigned char statusbar_png[432];
    extern const unsigned char submenu_png[760];
    extern const unsigned char text_sizer_png[157];
    extern const unsigned char timepicker_png[227];
    extern const unsigned char tree_ctrl_png[246];
    extern const unsigned char treelistctrl_png[425];
    extern const unsigned char treelistctrlcolumn_png[504];
    extern const unsigned char webview_png[1208];
    extern const unsigned char wrap_sizer_png[145];
    extern const unsigned char wxChoicebook_png[434];
    extern const unsigned char wxCollapsiblePane_png[324];
    extern const unsigned char wxDialog_png[636];
    extern const unsigned char wxFrame_png[424];
    extern const unsigned char wxListbook_png[357];
    extern const unsigned char wxMenuBar_png[490];
    extern const unsigned char wxPanel_png[156];
    extern const unsigned char wxPropertyGridManager_png[225];
    extern const unsigned char wxPropertyGrid_png[212];
    extern const unsigned char wxToolBar_png[554];
    extern const unsigned char wxToolbook_png[450];
    extern const unsigned char wxTreebook_png[484];
    extern const unsigned char wxWizardPageSimple_png[605];
    extern const unsigned char wxWizard_png[1047];
    extern const unsigned char wxactivityIndicator_png[796];
    extern const unsigned char wxanimation_png[248];
    extern const unsigned char wxbannerWindow_png[835];
    extern const unsigned char wxcheckBox_png[202];
    extern const unsigned char wxcomboBox_png[233];
    extern const unsigned char wxfileCtrl_png[255];
    extern const unsigned char wxmenuBar_png[490];
    extern const unsigned char wxnotebook_png[177];
    extern const unsigned char wxradioButton_png[268];
    extern const unsigned char wxscrolledWindow_png[258];
    extern const unsigned char wxsimplebook_png[249];
    extern const unsigned char wxsplitterWindow_png[266];
    extern const unsigned char wxtextCtrl_png[283];
    extern const unsigned char wxtoolBar_png[554];
}

// ************* End of generated code ***********
// DO NOT EDIT THIS COMMENT BLOCK!
//
// Code below this comment block will be preserved
// if the code for this class is re-generated.
//
// clang-format on
// ***********************************************
