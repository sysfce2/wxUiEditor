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

#include <wx/event.h>
#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/valgen.h>
#include <wx/valtext.h>
#include <wx/window.h>

#include "custom_ctrls/split_button.h"

#include "commonctrls.h"

#include "../art/clr_hourglass_gif.hxx"
#include "../art/empty.xpm"

#include <wx/animate.h>

#include <wx/mstream.h>  // memory stream classes
#include <wx/zstream.h>  // zlib stream classes

#include <memory>  // for std::make_unique

#if !wxCHECK_VERSION(3, 1, 6)
    #error "You must build with wxWidgets 3.1.6 or later to use SVG images."
#endif

// Convert compressed SVG string into a wxBitmapBundle
inline wxBitmapBundle wxueBundleSVG(const unsigned char* data,
    size_t size_data, size_t size_svg, wxSize def_size)
{
    auto str = std::make_unique<char[]>(size_svg);
    wxMemoryInputStream stream_in(data, size_data);
    wxZlibInputStream zlib_strm(stream_in);
    zlib_strm.Read(str.get(), size_svg);
    return wxBitmapBundle::FromSVG(str.get(), def_size);
};

// Convert a data array into a wxAnimation
inline wxAnimation wxueAnimation(const unsigned char* data, size_t size_data)
{
    wxMemoryInputStream strm(data, size_data);
    wxAnimation animation;
    animation.Load(strm);
    return animation;
};

bool CommonCtrls::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, pos, size, style, name))
        return false;

    auto* parent_sizer = new wxBoxSizer(wxVERTICAL);

    auto* box_sizer6 = new wxBoxSizer(wxVERTICAL);

    m_infoBar = new wxInfoBar(this);
    m_infoBar->SetShowHideEffects(wxSHOW_EFFECT_EXPAND, wxSHOW_EFFECT_NONE);
    m_infoBar->SetEffectDuration(500);
    box_sizer6->Add(m_infoBar, wxSizerFlags().Expand().Border(wxALL));

    parent_sizer->Add(box_sizer6, wxSizerFlags().Expand().Border(wxALL));

    auto* box_sizer = new wxBoxSizer(wxHORIZONTAL);

    m_staticText = new wxStaticText(this, wxID_ANY, "Text:");
    box_sizer->Add(m_staticText, wxSizerFlags().Center().Border(wxLEFT|wxTOP|wxBOTTOM, wxSizerFlags::GetDefaultBorder()));

    m_textCtrl = new wxTextCtrl(this, wxID_ANY, "Text \"ctrl\"", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    {
        wxArrayString tmp_array;
        tmp_array.push_back(wxString::FromUTF8("foo"));
        tmp_array.push_back(wxString::FromUTF8("bar"));
        m_textCtrl->AutoComplete(tmp_array);
    }
    m_textCtrl->SetValidator(wxTextValidator(wxFILTER_NONE, &m_textCtrlValidate));
    m_textCtrl->SetToolTip("Auto-complete contains \"foo\" and \"bar\"");
    box_sizer->Add(m_textCtrl, wxSizerFlags().Border(wxALL));

    m_staticText2 = new wxStaticText(this, wxID_ANY, "More text:");
    box_sizer->Add(m_staticText2,
        wxSizerFlags().Center().Border(wxLEFT|wxTOP|wxBOTTOM, wxSizerFlags::GetDefaultBorder()));

    m_textCtrl2 = new wxTextCtrl(this, wxID_ANY, "Another ctrl");
    box_sizer->Add(m_textCtrl2, wxSizerFlags().Border(wxALL));

    m_checkBox = new wxCheckBox(this, wxID_ANY, "2-state Checkbox");
    box_sizer->Add(m_checkBox, wxSizerFlags().Center().Border(wxALL));

    parent_sizer->Add(box_sizer, wxSizerFlags().Expand().Border(wxALL));

    auto* box_sizer2 = new wxBoxSizer(wxHORIZONTAL);

    m_btn = new wxButton(this, wxID_ANY, "First btn");
    box_sizer2->Add(m_btn, wxSizerFlags().Border(wxALL));

    auto* btn2 = new wxButton(this, wxID_ANY, "Popup");
    box_sizer2->Add(btn2, wxSizerFlags().Border(wxALL));

    m_radioBtn = new wxRadioButton(this, wxID_ANY, "First radio", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    box_sizer2->Add(m_radioBtn, wxSizerFlags().Center().Border(wxALL));

    m_radioBtn2 = new wxRadioButton(this, wxID_ANY, "Second radio");
    box_sizer2->Add(m_radioBtn2, wxSizerFlags().Center().Border(wxALL));

    m_checkBox2 = new wxCheckBox(this, wxID_ANY, "Checkbox");
    box_sizer2->Add(m_checkBox2, wxSizerFlags().Center().Border(wxALL));

    parent_sizer->Add(box_sizer2, wxSizerFlags().Expand().Border(wxALL));

    auto* static_box = new wxStaticBoxSizer(wxVERTICAL, this, "Combos and Choices");

    auto* box_sizer3 = new wxBoxSizer(wxHORIZONTAL);

    auto* static_box_sizer2 = new wxStaticBoxSizer(wxVERTICAL, static_box->GetStaticBox(), "Combo");

    m_staticText3 = new wxStaticText(static_box_sizer2->GetStaticBox(), wxID_ANY, "Unsorted");
    static_box_sizer2->Add(m_staticText3, wxSizerFlags().Border(wxALL));

    m_comboBox = new wxComboBox(static_box_sizer2->GetStaticBox(), wxID_ANY);
    m_comboBox->Append("item #1");
    m_comboBox->Append("item #2");
    m_comboBox->Append("item #0");
    m_comboBox->SetStringSelection("item #2");
    m_comboBox->SetToolTip("Item #0 should be selected by default");
    static_box_sizer2->Add(m_comboBox, wxSizerFlags().Expand().Border(wxALL));

    m_staticText4 = new wxStaticText(static_box_sizer2->GetStaticBox(), wxID_ANY, "Sorted");
    static_box_sizer2->Add(m_staticText4, wxSizerFlags().Border(wxALL));

    m_comboBox2 = new wxComboBox(static_box_sizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
        wxDefaultSize, 0, nullptr, wxCB_SORT);
    m_comboBox2->Append("item #1");
    m_comboBox2->Append("item #2");
    m_comboBox2->Append("item #0");
    m_comboBox2->SetStringSelection("item #2");
    m_comboBox2->SetToolTip("Item #2 should be selected by default");
    static_box_sizer2->Add(m_comboBox2, wxSizerFlags().Border(wxALL));

    box_sizer3->Add(static_box_sizer2, wxSizerFlags().Expand().Border(wxALL));

    auto* static_box_sizer3 = new wxStaticBoxSizer(wxVERTICAL, static_box->GetStaticBox(), "Choice");

    m_staticText5 = new wxStaticText(static_box_sizer3->GetStaticBox(), wxID_ANY, "Unsorted");
    static_box_sizer3->Add(m_staticText5, wxSizerFlags().Border(wxALL));

    m_choice = new wxChoice(static_box_sizer3->GetStaticBox(), wxID_ANY);
    m_choice->Append("item #1");
    m_choice->Append("item #2");
    m_choice->Append("item #0");
    m_choice->SetSelection(2);
    m_choice->SetToolTip("Item #0 should be selected by default");
    static_box_sizer3->Add(m_choice, wxSizerFlags().Border(wxALL));

    m_staticText6 = new wxStaticText(static_box_sizer3->GetStaticBox(), wxID_ANY, "Sorted");
    static_box_sizer3->Add(m_staticText6, wxSizerFlags().Border(wxALL));

    m_choice2 = new wxChoice(static_box_sizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize,
        0, nullptr, wxCB_SORT);
    m_choice2->Append("item #1");
    m_choice2->Append("item #2");
    m_choice2->Append("item #0");
    m_choice2->SetSelection(2);
    m_choice2->SetToolTip("Item #2 should be selected by default");
    static_box_sizer3->Add(m_choice2, wxSizerFlags().Border(wxALL));

    box_sizer3->Add(static_box_sizer3, wxSizerFlags().Expand().Border(wxALL));

    auto* static_box_sizer4 = new wxStaticBoxSizer(wxVERTICAL, static_box->GetStaticBox(), "List");

    m_staticText7 = new wxStaticText(static_box_sizer4->GetStaticBox(), wxID_ANY, "Unsorted");
    static_box_sizer4->Add(m_staticText7, wxSizerFlags().Border(wxALL));

    m_listbox = new wxListBox(static_box_sizer4->GetStaticBox(), wxID_ANY);
    m_listbox->Append("item #1");
    m_listbox->Append("item #2");
    m_listbox->Append("item #0");
    static_box_sizer4->Add(m_listbox, wxSizerFlags().Border(wxALL));

    m_staticText8 = new wxStaticText(static_box_sizer4->GetStaticBox(), wxID_ANY, "Sorted");
    static_box_sizer4->Add(m_staticText8, wxSizerFlags().Border(wxALL));

    m_listBox2 = new wxListBox(static_box_sizer4->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr,
        wxLB_SINGLE|wxLB_SORT);
    m_listBox2->Append("item #1");
    m_listBox2->Append("item #2");
    m_listBox2->Append("item #0");
    static_box_sizer4->Add(m_listBox2, wxSizerFlags().Border(wxALL));

    box_sizer3->Add(static_box_sizer4, wxSizerFlags().Expand().Border(wxALL));

    auto* static_box_sizer5 = new wxStaticBoxSizer(wxVERTICAL, static_box->GetStaticBox(), "Checked");

    m_staticText9 = new wxStaticText(static_box_sizer5->GetStaticBox(), wxID_ANY, "Unsorted");
    static_box_sizer5->Add(m_staticText9, wxSizerFlags().Border(wxALL));

    m_checkList = new wxCheckListBox(static_box_sizer5->GetStaticBox(), wxID_ANY);
    m_checkList->Append("\"item #1\" \"item #2\" \"item #0\"");
    static_box_sizer5->Add(m_checkList, wxSizerFlags().Border(wxALL));

    m_staticText10 = new wxStaticText(static_box_sizer5->GetStaticBox(), wxID_ANY, "Sorted");
    static_box_sizer5->Add(m_staticText10, wxSizerFlags().Border(wxALL));

    m_checkList2 = new wxCheckListBox(static_box_sizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr,
        wxLB_SINGLE|wxLB_SORT);
    m_checkList2->Append("\"item #1\" \"item #2\" \"item #0\"");
    static_box_sizer5->Add(m_checkList2, wxSizerFlags().Border(wxALL));

    box_sizer3->Add(static_box_sizer5, wxSizerFlags().Expand().Border(wxALL));

    static_box->Add(box_sizer3, wxSizerFlags().Expand().Border(wxALL));

    parent_sizer->Add(static_box, wxSizerFlags().Expand().Border(wxALL));

    auto* flex_grid_sizer = new wxFlexGridSizer(4, 0, 0);

    m_staticText11 = new wxStaticText(this, wxID_ANY,
        "On Windows 10, the items may be be clipped unless they have a trailing space.");
    m_staticText11->Wrap(200);
    flex_grid_sizer->Add(m_staticText11, wxSizerFlags().Border(wxALL));
    {
        wxString radioBox_choices[] = {
            "Button zero ",
            "Button one ",
            "Button two "
        };
        // Trailing spaces added to avoid clipping
        m_radioBox = new wxRadioBox(this, wxID_ANY, "Radio Box", wxDefaultPosition, wxDefaultSize, 3, radioBox_choices, 0,
        wxRA_SPECIFY_ROWS);
    }
    m_radioBox->SetSelection(1);
    m_radioBox->SetValidator(wxGenericValidator(&m_valRadio));
    flex_grid_sizer->Add(m_radioBox, wxSizerFlags().Border(wxALL));

    auto* box_sizer_2 = new wxBoxSizer(wxVERTICAL);

        auto* bmp = new wxStaticBitmap(this, wxID_ANY, 
#if wxCHECK_VERSION(3, 1, 6)
            wxueBundleSVG(wxue_img::face_smile_svg, 1781, 7417, wxSize(64, 64)));
#else
        wxBitmap(wxNullBitmap /* SVG images require wxWidgets 3.1.6 */));
#endif
    box_sizer_2->Add(bmp, wxSizerFlags().Border(wxALL));

    m_staticText_2 = new wxStaticText(this, wxID_ANY, "SVG image");
    box_sizer_2->Add(m_staticText_2, wxSizerFlags().Border(wxALL));

    flex_grid_sizer->Add(box_sizer_2, wxSizerFlags().Border(wxALL));

    m_bmpComboBox = new wxBitmapComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        0, nullptr, wxCB_READONLY);
    flex_grid_sizer->Add(m_bmpComboBox, wxSizerFlags().Border(wxALL));

    m_checkPlayAnimation = new wxCheckBox(this, wxID_ANY, "Play Animation");
    auto* static_box_2 = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY,
#if wxCHECK_VERSION(3, 1, 1)
        m_checkPlayAnimation),
#else
        wxEmptyString),
#endif
    wxVERTICAL);

    m_toggleBtn = new wxToggleButton(static_box_2->GetStaticBox(), wxID_ANY, "Play Animation", wxDefaultPosition,
        wxDefaultSize, wxBU_EXACTFIT);
    static_box_2->Add(m_toggleBtn, wxSizerFlags().Border(wxALL));

    m_animation_ctrl = new wxAnimationCtrl(static_box_2->GetStaticBox(), wxID_ANY, wxueAnimation(clr_hourglass_gif, sizeof(clr_hourglass_gif)),
        wxDefaultPosition, wxDefaultSize, wxAC_DEFAULT_STYLE);
    m_animation_ctrl->SetInactiveBitmap(wxImage(empty_xpm));
    static_box_2->Add(m_animation_ctrl, wxSizerFlags().Border(wxALL));

    flex_grid_sizer->Add(static_box_2, wxSizerFlags().Border(wxALL));

    m_split_button = new wxue_ctrl::SplitButton(this, wxID_ANY, "Play");
    {
        const int ID_PLAY { 100 };
        const int ID_STOP { 101 };
        m_split_button->GetMenu().Append(ID_PLAY, "Play");
        m_split_button->GetMenu().Append(ID_STOP, "Stop");

        m_split_button->Bind(wxEVT_MENU,
            [this](wxCommandEvent&)
            {
                m_animation_ctrl->Play();
                m_checkPlayAnimation->SetValue(true);
            }, ID_PLAY);

        m_split_button->Bind(wxEVT_MENU,
            [this](wxCommandEvent&)
            {
                m_animation_ctrl->Stop();
                m_checkPlayAnimation->SetValue(false);
            }, ID_STOP);

        m_split_button->Bind(wxEVT_BUTTON,
            [this](wxCommandEvent&)
            {
                m_animation_ctrl->Play();
                m_checkPlayAnimation->SetValue(true);
            } );
    }
    flex_grid_sizer->Add(m_split_button, wxSizerFlags().DoubleBorder(wxALL));

    flex_grid_sizer->AddSpacer(0);

    m_edit_listbox = new wxEditableListBox(this, wxID_ANY, "My Editable ListBox", wxDefaultPosition, wxDefaultSize,
        wxEL_ALLOW_NEW|wxEL_ALLOW_EDIT|wxEL_ALLOW_DELETE);
    {
        wxArrayString tmp_array;
        tmp_array.push_back(wxString::FromUTF8("item #1"));
        tmp_array.push_back(wxString::FromUTF8("item #2"));
        tmp_array.push_back(wxString::FromUTF8("item #3"));
        m_edit_listbox->SetStrings(tmp_array);
    }
    flex_grid_sizer->Add(m_edit_listbox, wxSizerFlags().Border(wxALL));

    parent_sizer->Add(flex_grid_sizer, wxSizerFlags().Expand().Border(wxALL));

    auto* box_sizer5 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText12 = new wxStaticText(this, wxID_ANY, "Slider:");
    box_sizer5->Add(m_staticText12,
        wxSizerFlags().Center().Border(wxLEFT|wxTOP|wxBOTTOM, wxSizerFlags::GetDefaultBorder()));

    m_slider = new wxSlider(this, wxID_ANY, 50, 0, 100);
    m_slider->SetValue(50);
    box_sizer5->Add(m_slider, wxSizerFlags().Border(wxALL));

    m_staticText13 = new wxStaticText(this, wxID_ANY, "Gauge:");
    box_sizer5->Add(m_staticText13,
        wxSizerFlags().Center().Border(wxLEFT|wxTOP|wxBOTTOM, wxSizerFlags::GetDefaultBorder()));

    m_gauge = new wxGauge(this, wxID_ANY, 100);
    m_gauge->SetValue(0);
    box_sizer5->Add(m_gauge, wxSizerFlags().Center().Border(wxALL));

    parent_sizer->Add(box_sizer5, wxSizerFlags().Expand().Border(wxALL));

    auto* stdBtn = CreateStdDialogButtonSizer(wxOK|wxCANCEL|wxHELP);
    parent_sizer->Add(CreateSeparatedSizer(stdBtn), wxSizerFlags().Expand().Border(wxALL));

    SetSizerAndFit(parent_sizer);
    Centre(wxBOTH);

    // Event handlers
    Bind(wxEVT_INIT_DIALOG, &CommonCtrls::OnInit, this);
    Bind(wxEVT_CONTEXT_MENU, &CommonCtrls::OnContextMenu, this);
    m_textCtrl->Bind(wxEVT_TEXT_ENTER,
        [this](wxCommandEvent&)
        {
            m_infoBar->ShowMessage("wxEVT_TEXT_ENTER event");
            Fit();
        } );
    m_checkBox->Bind(wxEVT_CHECKBOX,
        [this](wxCommandEvent&)
        {
            m_infoBar->ShowMessage("wxEVT_CHECKBOX event");
            Fit();

        } );
    m_btn->Bind(wxEVT_BUTTON,
        [this](wxCommandEvent&)
        {
            m_infoBar->ShowMessage("wxEVT_BUTTON event");
            Fit();
        } );
    btn2->Bind(wxEVT_BUTTON, &CommonCtrls::OnPopupBtn, this);
    m_radioBtn->Bind(wxEVT_RADIOBUTTON,
        [this](wxCommandEvent&)
        {
            m_infoBar->ShowMessage("wxEVT_RADIOBUTTON event");
            Fit();
        } );
    m_radioBtn2->Bind(wxEVT_RADIOBUTTON, &CommonCtrls::OnRadio, this);
    m_checkBox2->Bind(wxEVT_CHECKBOX, &CommonCtrls::OnCheckBox, this);
    m_comboBox->Bind(wxEVT_COMBOBOX,
        [this](wxCommandEvent&)
        {
            m_infoBar->ShowMessage("wxEVT_COMBOBOX event");
            Fit();
        } );
    m_comboBox2->Bind(wxEVT_COMBOBOX,
        [this](wxCommandEvent&)
        {
            m_infoBar->ShowMessage("wxEVT_COMBOBOX event");
            Fit();
        } );
    m_comboBox2->Bind(wxEVT_COMBOBOX_CLOSEUP,
        [this](wxCommandEvent&)
        {
            m_infoBar->ShowMessage("wxEVT_COMBOBOX_CLOSEUP event");
            Fit();
        } );
    m_choice->Bind(wxEVT_CHOICE,
        [this](wxCommandEvent&)
        {
            m_infoBar->ShowMessage("wxEVT_CHOICE event");
            Fit();
        } );
    m_choice2->Bind(wxEVT_CHOICE, &CommonCtrls::OnChoice, this);
    m_listbox->Bind(wxEVT_LISTBOX, &CommonCtrls::OnListBox, this);
    m_listBox2->Bind(wxEVT_LISTBOX, &CommonCtrls::OnListBox, this);
    m_checkList->Bind(wxEVT_CHECKLISTBOX, &CommonCtrls::OnListChecked, this);
    m_radioBox->Bind(wxEVT_RADIOBOX, &CommonCtrls::OnRadioBox, this);
    m_checkPlayAnimation->Bind(wxEVT_CHECKBOX,
        [this](wxCommandEvent&)
        {
            if (m_checkPlayAnimation->GetValue()) 
            {
                m_animation_ctrl->Play();
            }
            else 
            {  
                m_animation_ctrl->Stop();
            }

        } );
    m_toggleBtn->Bind(wxEVT_TOGGLEBUTTON,
        [this](wxCommandEvent&)
        {
            if (m_toggleBtn->GetValue()) 
            {
                m_animation_ctrl->Play();
                m_checkPlayAnimation->SetValue(true);
            }
            else 
            {  
                m_animation_ctrl->Stop();
                m_checkPlayAnimation->SetValue(false);
            }

            m_infoBar->ShowMessage("wxEVT_TOGGLEBUTTON event");
            Fit();
        } );
    m_edit_listbox->Bind(wxEVT_LIST_BEGIN_DRAG,
        [this](wxListEvent&)
        {
            m_infoBar->ShowMessage("wxEVT_LIST_BEGIN_DRAG event");
            Fit();
        } );
    m_slider->Bind(wxEVT_SLIDER, &CommonCtrls::OnSlider, this);

    return true;
}
void CommonCtrls::OnContextMenu(wxContextMenuEvent& event)
{
    wxMenu ctx_menu;
    auto p_ctx_menu = &ctx_menu;  // convenience variable for the auto-generated code
    auto* menu_item = new wxMenuItem(p_ctx_menu, wxID_ANY, "Play Animation");
    p_ctx_menu->Append(menu_item);
    auto* menu_item_2 = new wxMenuItem(p_ctx_menu, wxID_ANY, "Stop Animation");
    p_ctx_menu->Append(menu_item_2);
    p_ctx_menu->AppendSeparator();
    auto* menu_item_3 = new wxMenuItem(p_ctx_menu, wxID_ANY, "Set Slider to 25");
    p_ctx_menu->Append(menu_item_3);
    auto* menu_item_4 = new wxMenuItem(p_ctx_menu, wxID_ANY, "Set Slider to 75");
    p_ctx_menu->Append(menu_item_4);
    auto* menu_item_5 = new wxMenuItem(p_ctx_menu, wxID_ANY, "Set Gauge to 25");
    p_ctx_menu->Append(menu_item_5);
    auto* menu_item_6 = new wxMenuItem(p_ctx_menu, wxID_ANY, "Set Gauge to 75");
    p_ctx_menu->Append(menu_item_6);

    ctx_menu.Bind(wxEVT_MENU,
        [this](wxCommandEvent&) { m_animation_ctrl->Play(); },
        menu_item->GetId());
    ctx_menu.Bind(wxEVT_MENU,
        [this](wxCommandEvent&) { m_animation_ctrl->Stop(); },
        menu_item_2->GetId());
    ctx_menu.Bind(wxEVT_MENU,
        [this](wxCommandEvent&) { m_slider->SetValue(25); },
        menu_item_3->GetId());
    ctx_menu.Bind(wxEVT_MENU,
        [this](wxCommandEvent&) { m_slider->SetValue(75); },
        menu_item_4->GetId());
    ctx_menu.Bind(wxEVT_MENU,
        [this](wxCommandEvent&) { m_gauge->SetValue(25); },
        menu_item_5->GetId());
    ctx_menu.Bind(wxEVT_MENU,
        [this](wxCommandEvent&) { m_gauge->SetValue(75); },
        menu_item_6->GetId());

    wxStaticCast(event.GetEventObject(), wxWindow)->PopupMenu(&ctx_menu);
}

namespace wxue_img
{

    const unsigned char face_smile_svg[1781] {
        120,218,237,89,75,111,220,54,16,238,79,17,228,75,12,172,21,190,31,107,175,129,34,135,94,82,244,208,230,92,
        40,43,174,163,70,94,45,36,217,137,253,235,59,212,131,162,36,238,35,13,130,2,69,181,112,44,127,28,206,12,103,
        190,25,146,155,187,250,249,225,254,46,51,187,58,202,179,77,108,95,104,124,127,151,239,63,215,219,244,96,214,
        7,83,213,7,179,109,242,103,19,213,101,150,31,224,103,221,188,28,204,38,158,202,208,44,142,28,242,124,248,243,
        235,38,70,209,58,34,12,254,193,211,161,151,110,8,35,100,127,161,233,224,235,38,102,42,52,177,183,114,83,86,
        249,67,190,223,196,157,128,232,165,192,119,207,85,170,227,183,247,119,69,190,55,105,245,75,149,102,185,217,
        55,173,204,20,162,68,35,88,108,221,148,135,118,212,190,0,70,226,168,220,237,106,211,128,159,9,234,158,56,170,
        155,151,194,116,50,55,219,178,40,171,245,213,110,183,219,102,230,182,133,202,67,186,205,155,151,53,30,102,
        220,90,23,90,213,161,153,194,72,145,30,157,233,217,23,140,41,174,165,142,125,15,153,211,237,129,98,156,134,
        207,184,253,81,82,117,202,237,183,211,56,221,223,217,151,180,112,161,172,54,177,74,52,34,72,90,171,59,72,40,
        230,137,228,92,98,136,221,14,82,79,116,130,185,98,2,70,183,253,40,65,90,49,248,179,27,37,74,33,9,137,123,232,
        85,126,216,231,77,189,137,159,106,83,253,14,46,153,223,246,31,106,211,173,121,106,155,72,12,90,190,130,131,
        159,215,159,42,179,219,196,87,129,164,142,180,129,53,23,64,138,77,156,22,95,210,151,250,34,94,16,142,116,124,
        34,121,16,192,140,95,146,60,151,133,33,77,132,99,124,138,23,38,203,24,232,56,171,26,7,85,211,75,114,55,68,
        252,143,42,221,215,187,178,122,220,196,143,105,83,229,95,223,224,4,22,14,207,106,112,124,124,113,67,55,34,
        97,82,51,38,86,55,152,38,84,18,140,175,59,31,210,252,161,202,72,159,96,158,32,78,100,151,124,170,19,174,137,
        138,45,107,90,154,200,129,36,131,212,206,151,58,205,136,62,116,151,213,167,108,159,227,209,28,66,167,4,34,
        46,43,46,196,65,149,243,168,195,212,182,24,223,78,163,124,1,201,24,23,252,4,79,103,245,13,210,210,99,214,9,
        223,102,203,189,93,180,10,80,165,227,139,150,57,85,117,164,53,156,239,178,138,176,69,151,85,68,156,91,206,
        174,125,206,46,7,84,169,75,59,223,86,219,207,55,117,190,11,150,135,150,155,136,66,223,176,137,24,147,137,127,
        178,137,24,166,183,100,119,73,31,226,104,201,91,17,216,68,20,144,249,226,77,100,43,196,246,123,54,145,51,173,
        255,84,159,154,183,39,239,133,182,207,136,64,147,129,29,131,232,235,174,255,232,246,47,197,251,166,163,18,
        216,179,24,69,125,67,98,110,116,59,29,221,78,71,151,219,18,227,118,55,59,177,45,157,41,119,27,47,123,248,186,
        191,123,24,133,30,170,242,233,240,88,102,16,250,34,125,49,149,55,191,72,63,154,98,19,191,183,240,112,0,106,
        101,48,112,241,144,54,159,34,0,126,141,24,75,172,199,18,69,110,49,209,207,145,139,66,36,90,16,54,227,8,69,
        24,62,17,31,82,184,186,112,66,200,194,107,60,158,21,43,8,164,155,228,227,95,39,217,112,248,44,240,35,190,204,
        128,93,38,132,149,58,126,186,78,149,112,138,5,131,243,200,237,180,159,237,242,162,88,63,85,197,155,171,101,
        246,174,219,81,159,203,29,80,61,21,102,109,158,205,190,204,50,160,123,85,126,54,235,125,185,55,253,251,205,
        151,60,107,62,129,73,134,152,146,88,210,1,183,233,135,84,173,33,135,251,204,7,255,42,243,125,143,62,166,213,
        103,83,117,234,186,247,155,186,73,171,102,130,60,230,217,228,111,179,207,38,14,60,230,141,169,138,28,126,173,
        153,43,192,126,44,75,235,79,105,85,165,47,147,25,22,237,170,124,141,230,51,150,181,252,156,215,249,199,188,
        176,96,251,90,152,219,44,175,15,192,182,117,190,183,11,186,45,159,77,181,43,202,47,195,120,60,191,42,164,213,
        214,50,188,229,101,179,168,103,146,32,69,33,175,129,122,118,67,55,12,146,202,36,230,112,238,128,35,136,38,
        132,65,69,183,28,135,147,131,148,12,78,159,150,166,8,41,65,48,80,86,37,66,16,196,165,246,222,122,202,18,146,
        48,142,4,131,99,205,101,19,66,22,230,28,119,147,102,28,15,225,237,145,120,208,52,227,56,197,9,198,68,104,229,
        113,156,146,177,7,207,99,61,207,69,32,91,71,51,123,1,29,194,4,10,82,110,78,207,35,244,93,16,124,162,121,86,
        32,167,106,201,21,30,108,192,12,170,111,40,206,43,189,85,91,148,6,170,119,94,224,103,186,130,189,106,92,207,
        58,200,98,246,55,114,29,39,112,151,147,138,4,207,216,253,208,13,149,176,141,97,162,128,235,44,129,19,50,19,
        215,65,51,203,190,39,36,156,200,57,214,161,190,215,134,249,68,8,130,157,110,60,133,77,98,206,17,199,72,16,
        249,127,179,51,147,58,37,199,171,249,108,245,31,235,22,179,238,242,175,246,188,129,216,206,57,224,138,177,
        132,132,3,220,246,21,62,99,52,136,224,206,91,9,247,125,38,168,92,181,59,184,214,66,68,239,34,202,18,34,20,
        150,208,229,117,98,175,148,84,71,20,37,146,97,76,217,138,82,144,132,140,240,8,230,48,65,160,229,123,216,187,
        8,171,132,2,42,185,135,194,141,84,105,161,57,183,26,169,68,20,169,8,219,12,32,132,133,181,205,25,197,74,219,
        217,52,1,247,224,88,184,34,18,238,157,26,35,29,97,168,58,77,52,83,43,155,53,164,57,194,214,54,214,146,18,233,
        97,224,57,73,0,130,51,134,135,90,47,24,232,161,43,162,18,130,136,96,34,184,238,215,40,80,182,20,92,128,71,
        133,202,118,168,192,179,149,11,164,127,53,85,121,252,140,178,104,252,67,213,126,124,106,154,69,209,182,149,
        246,159,45,90,71,228,46,21,227,22,208,125,141,113,125,89,92,67,11,11,113,30,65,51,23,100,206,121,66,129,67,
        124,202,121,132,136,238,120,55,114,190,199,102,156,239,81,143,243,182,134,225,168,192,124,206,195,40,21,72,
        241,41,231,5,204,33,109,197,140,156,183,39,88,66,181,244,57,239,176,9,231,29,234,113,94,194,153,140,115,70,
        130,235,182,156,31,218,130,18,72,196,39,250,199,91,123,3,242,246,205,246,181,72,27,243,198,150,9,229,28,140,
        89,159,37,18,253,23,79,15,112,151,21,241,52,159,129,210,90,22,211,119,100,151,96,240,65,97,174,86,152,67,92,
        236,165,4,98,228,161,50,81,29,74,80,66,36,109,49,61,96,144,71,213,203,57,236,157,205,5,39,115,73,225,102,203,
        0,230,217,246,80,226,36,165,243,7,121,182,101,47,135,70,219,224,37,102,51,73,88,205,66,163,135,57,219,239,
        131,209,152,230,28,163,121,197,253,232,12,1,75,133,82,28,147,73,148,60,116,204,144,78,224,18,217,98,46,238,
        80,75,184,151,243,50,100,235,6,207,37,121,64,35,15,217,246,208,49,158,163,70,20,176,237,103,104,244,210,161,
        222,106,72,0,59,150,11,18,236,126,87,223,178,161,92,86,26,44,17,90,4,74,3,119,232,164,52,122,108,82,26,120,
        152,61,41,141,65,82,44,53,122,152,103,219,67,137,147,28,53,162,128,109,52,218,246,188,116,168,183,26,18,192,
        156,237,89,224,217,15,13,188,151,121,111,241,19,198,15,174,250,140,31,48,159,241,227,226,125,198,15,146,60,
        160,145,135,108,79,24,63,72,250,140,95,218,246,3,239,51,190,71,39,140,95,98,199,2,47,218,239,215,30,250,31,
        251,95,158,63,253,13,128,254,92,34
    };

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
// Purpose:   Common controls dialog
// Author:    Ralph Walden
// Copyright: Copyright (c) 2020-2023 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include <wx/artprov.h>

#include "mainframe.h"  // auto-generated: ../wxui_generated/mainframe_base.h and ../wxui_generated/mainframe_base.cpp

void MainFrame::OnCommonDialog(wxCommandEvent& WXUNUSED(event))
{
    CommonCtrls dlg(this);
    dlg.ShowModal();
}

void CommonCtrls::OnInit(wxInitDialogEvent& event)
{
    m_bmpComboBox->Append("Home", wxArtProvider::GetBitmap(wxART_GO_HOME, wxART_MENU));
    m_bmpComboBox->Append("Print", wxArtProvider::GetBitmap(wxART_PRINT, wxART_MENU));

    event.Skip();  // transfer all validator data to their windows and update UI
}

CommonCtrls::~CommonCtrls()
{
    delete m_popup_win;
}

void CommonCtrls::OnListChecked(wxCommandEvent& WXUNUSED(event))
{
    m_infoBar->ShowMessage("wxEVT_CHECKLISTBOX event");
    Fit();
}

void CommonCtrls::OnRadioBox(wxCommandEvent& WXUNUSED(event))
{
    m_infoBar->ShowMessage("wxEVT_RADIOBOX event");
    Fit();
}

void CommonCtrls::OnSlider(wxCommandEvent& WXUNUSED(event))
{
    m_infoBar->ShowMessage("wxEVT_SLIDER event");
    Fit();
}

void CommonCtrls::OnListBox(wxCommandEvent& WXUNUSED(event))
{
    m_infoBar->ShowMessage("wxEVT_LISTBOX event");
    Fit();
}

void CommonCtrls::OnCheckBox(wxCommandEvent& WXUNUSED(event))
{
    // TODO: Implement OnCheckBox
}

void CommonCtrls::OnChoice(wxCommandEvent& WXUNUSED(event))
{
    // TODO: Implement OnChoice
}

void CommonCtrls::OnRadio(wxCommandEvent& WXUNUSED(event))
{
    // TODO: Implement OnRadio
}

void CommonCtrls::OnPopupBtn(wxCommandEvent& event)
{
    if (m_popup_win)
        delete m_popup_win;
    m_popup_win = new PopupWin(this);

    auto btn = wxStaticCast(event.GetEventObject(), wxWindow);
    auto pos = btn->ClientToScreen(wxPoint(0, 0));
    m_popup_win->Position(pos, btn->GetSize());

    m_popup_win->Popup();
}
