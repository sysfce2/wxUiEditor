///////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor - see https://github.com/KeyWorksRW/wxUiEditor/
//
// Do not edit any code above the "End of generated code" comment block.
// Any changes before that block will be lost if it is re-generated!
///////////////////////////////////////////////////////////////////////////////

// clang-format off

#include <wx/artprov.h>
#include <wx/gbsizer.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/valgen.h>

#include "maintestdialog.h"

#include <wx/mstream.h>  // memory stream classes

// Convert a data array into a wxImage
inline wxImage wxueImage(const unsigned char* data, size_t size_data)
{
    wxMemoryInputStream strm(data, size_data);
    wxImage image;
    image.LoadFile(strm);
    return image;
};

bool MainTestDialog::Create(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, pos, size, style, name))
        return false;
    if (!wxImage::FindHandler(wxBITMAP_TYPE_PNG))
        wxImage::AddHandler(new wxPNGHandler);

    auto* dlg_sizer = new wxBoxSizer(wxVERTICAL);

    m_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_TOP|wxNB_MULTILINE);
    dlg_sizer->Add(m_notebook, wxSizerFlags().Expand().Border(wxALL));

    auto* page_2 = new wxPanel(m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    m_notebook->AddPage(page_2, "Text");

    auto* page_sizer_1 = new wxBoxSizer(wxVERTICAL);

    m_text_ctrl = new wxTextCtrl(page_2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RICH2);
    m_text_ctrl->SetHint("wxTextCtrl");
    page_sizer_1->Add(m_text_ctrl, wxSizerFlags().Expand().Border(wxALL));

    m_richText = new wxRichTextCtrl(page_2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE|
        wxVSCROLL | wxHSCROLL | wxNO_BORDER | wxWANTS_CHARS);
    m_richText->SetHint("wxRichTextCtrl");
    m_richText->SetMinSize(ConvertDialogToPixels(wxSize(150, 30)));
    page_sizer_1->Add(m_richText, wxSizerFlags().Expand().Border(wxALL));

    m_scintilla = new wxStyledTextCtrl(page_2);
    {
        m_scintilla->SetLexer(wxSTC_LEX_CPP);
        m_scintilla->SetEOLMode(wxSTC_EOL_LF);
        m_scintilla->SetViewWhiteSpace(wxSTC_WS_VISIBLEALWAYS);
        // Sets text margin scaled appropriately for the current DPI on Windows,
        // 5 on wxGTK or wxOSX
        m_scintilla->SetMarginLeft(wxSizerFlags::GetDefaultBorder());
        m_scintilla->SetMarginRight(wxSizerFlags::GetDefaultBorder());
        m_scintilla->SetMarginWidth(1, 0); // Remove default margin
        m_scintilla->SetBackSpaceUnIndents(true);
    }
    m_scintilla->SetMinSize(ConvertDialogToPixels(wxSize(150, 60)));
    page_sizer_1->Add(m_scintilla, wxSizerFlags().Expand().Border(wxALL));
    page_2->SetSizerAndFit(page_sizer_1);

    auto* page_4 = new wxPanel(m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    m_notebook->AddPage(page_4, "Buttons");

    auto* box_sizer_3 = new wxBoxSizer(wxVERTICAL);

    auto* grid_bag_sizer = new wxGridBagSizer();

    m_btn = new wxButton(page_4, wxID_ANY, "Normal");
    m_btn->SetToolTip("A normal button");
    grid_bag_sizer->Add(m_btn, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL, 5);

    m_btn_2 = new wxButton(page_4, wxID_ANY, wxEmptyString);
    m_btn_2->SetLabelMarkup("<b><span foreground=\'red\'>Markup</span></b>");
    m_btn_2->SetToolTip("Text should be Bold and Red.");
    grid_bag_sizer->Add(m_btn_2, wxGBPosition(0, 1), wxGBSpan(1, 1), wxALL, 5);

    m_btn_bitmaps = new wxButton(page_4, wxID_ANY, "Bitmaps");
#if wxCHECK_VERSION(3, 1, 6)
    {
        m_btn_bitmaps->SetBitmap(wxBitmapBundle::FromBitmap(wxueImage(wxue_img::normal_png, sizeof(wxue_img::normal_png))));
        m_btn_bitmaps->SetBitmapDisabled(wxBitmapBundle::FromBitmap(wxueImage(wxue_img::no_hour_png, sizeof(wxue_img::no_hour_png))));
        m_btn_bitmaps->SetBitmapCurrent(wxBitmapBundle::FromBitmap(wxueImage(wxue_img::focus_png, sizeof(wxue_img::focus_png))));
    }
#else
    m_btn_bitmaps->SetBitmap(wxueImage(wxue_img::normal_png, sizeof(wxue_img::normal_png)));
    m_btn_bitmaps->SetBitmapDisabled(wxueImage(wxue_img::no_hour_png, sizeof(wxue_img::no_hour_png)));
    m_btn_bitmaps->SetBitmapCurrent(wxueImage(wxue_img::focus_png, sizeof(wxue_img::focus_png)));
#endif  // wxCHECK_VERSION(3, 1, 6)
    m_btn_bitmaps->SetToolTip("Bitmap should change when mouse is over button, or button is disabled.");
    grid_bag_sizer->Add(m_btn_bitmaps, wxGBPosition(0, 2), wxGBSpan(1, 1), wxALL, 5);

    m_btn_4 = new wxButton(page_4, wxID_ANY, "Right");
    m_btn_4->SetBitmapPosition(wxRIGHT);
#if wxCHECK_VERSION(3, 1, 6)
        m_btn_4->SetBitmap(wxBitmapBundle::FromBitmap(wxueImage(wxue_img::normal_png, sizeof(wxue_img::normal_png))));
#else
    m_btn_4->SetBitmap(wxueImage(wxue_img::normal_png, sizeof(wxue_img::normal_png)));
#endif  // wxCHECK_VERSION(3, 1, 6)
    m_btn_4->SetToolTip("Bitmap should be on the right side (fails in wxPython 4.2).");
    grid_bag_sizer->Add(m_btn_4, wxGBPosition(0, 3), wxGBSpan(1, 1), wxALL, 5);

    m_toggleBtn = new wxToggleButton(page_4, wxID_ANY, "Toggle", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_toggleBtn->SetToolTip("Style set to exact fit, so it should be a bit smaller than usual.");
    grid_bag_sizer->Add(m_toggleBtn, wxGBPosition(0, 4), wxGBSpan(1, 1), wxALL, 5);

    auto* disable_bitmaps = new wxCheckBox(page_4, wxID_ANY, "Disable");
    disable_bitmaps->SetToolTip("This will change the enable state and bitmap of the Bitmaps button.");
    grid_bag_sizer->Add(disable_bitmaps, wxGBPosition(2, 2), wxGBSpan(1, 1), wxALL, 5);

    box_sizer_3->Add(grid_bag_sizer, wxSizerFlags().Border(wxALL));

    auto* box_sizer_7 = new wxBoxSizer(wxHORIZONTAL);

    m_btn_5 = new wxCommandLinkButton(page_4, wxID_ANY, "Command", "wxCommandLinkButton");
#if wxCHECK_VERSION(3, 1, 6)
        m_btn_5->SetBitmap(wxArtProvider::GetBitmapBundle(wxART_GO_FORWARD, wxART_OTHER));
#else
    m_btn_5->SetBitmap(wxArtProvider::GetBitmap(wxART_GO_FORWARD, wxART_OTHER));
#endif  // wxCHECK_VERSION(3, 1, 6)
    m_btn_5->SetToolTip("The bitmap for this is from Art Provider.");
    box_sizer_7->Add(m_btn_5, wxSizerFlags().Border(wxALL));

    wxString radioBox_choices[] = {
        "Button zero ",
        "Button one ",
        "Button two "
    };
    // Trailing spaces added to avoid clipping
    auto* radioBox = new wxRadioBox(page_4, wxID_ANY, "Radio Box", wxDefaultPosition, wxDefaultSize, 3, radioBox_choices,
        0, wxRA_SPECIFY_ROWS);
    radioBox->SetSelection(1);
    radioBox->SetValidator(wxGenericValidator(&m_valRadio));
    box_sizer_7->Add(radioBox, wxSizerFlags().Border(wxALL));

    box_sizer_3->Add(box_sizer_7, wxSizerFlags().Border(wxALL));

    auto* box_sizer2 = new wxBoxSizer(wxHORIZONTAL);

    m_btn_3 = new wxButton(page_4, wxID_ANY, "First btn");
    box_sizer2->Add(m_btn_3, wxSizerFlags().Border(wxALL));

    auto* btn2 = new wxButton(page_4, wxID_ANY, "Popup");
    box_sizer2->Add(btn2, wxSizerFlags().Border(wxALL));

    m_radioBtn = new wxRadioButton(page_4, wxID_ANY, "First radio", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    box_sizer2->Add(m_radioBtn, wxSizerFlags().Center().Border(wxALL));

    m_radioBtn2 = new wxRadioButton(page_4, wxID_ANY, "Second radio");
    box_sizer2->Add(m_radioBtn2, wxSizerFlags().Center().Border(wxALL));

    m_checkBox2 = new wxCheckBox(page_4, wxID_ANY, "Checkbox");
    box_sizer2->Add(m_checkBox2, wxSizerFlags().Center().Border(wxALL));

    box_sizer_3->Add(box_sizer2, wxSizerFlags().Expand().Border(wxALL));
    page_4->SetSizerAndFit(box_sizer_3);

    auto* page_5 = new wxPanel(m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    m_notebook->AddPage(page_5, "Lists");

    auto* box_sizer_5 = new wxBoxSizer(wxVERTICAL);

    auto* flex_grid_sizer = new wxFlexGridSizer(2, 0, 0);

    auto* box_sizer_10 = new wxBoxSizer(wxVERTICAL);

    m_staticText_2 = new wxStaticText(page_5, wxID_ANY, "wxRearrangeCtrl");
    box_sizer_10->Add(m_staticText_2, wxSizerFlags().Expand().Border(wxALL));

    m_rearrange = new wxRearrangeCtrl(page_5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxArrayInt(), wxArrayString());
    box_sizer_10->Add(m_rearrange, wxSizerFlags().Border(wxALL));

    flex_grid_sizer->Add(box_sizer_10, wxSizerFlags().Border(wxALL));

    auto* box_sizer_11 = new wxBoxSizer(wxVERTICAL);

    auto* staticText_3 = new wxStaticText(page_5, wxID_ANY, "wxCheckListBox");
    box_sizer_11->Add(staticText_3, wxSizerFlags().Expand().Border(wxALL));

    m_checkList = new wxCheckListBox(page_5, wxID_ANY);
    box_sizer_11->Add(m_checkList, wxSizerFlags().Border(wxALL));

    flex_grid_sizer->Add(box_sizer_11, wxSizerFlags().Border(wxALL));

    auto* box_sizer_12 = new wxBoxSizer(wxVERTICAL);

    m_staticText_4 = new wxStaticText(page_5, wxID_ANY, "wxListView");
    box_sizer_12->Add(m_staticText_4, wxSizerFlags().Border(wxALL));

    m_listview = new wxListView(page_5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_SINGLE_SEL|wxLC_REPORT);
    {
        m_listview->AppendColumn("name");
        m_listview->AppendColumn("value");
        auto info = wxListItem();
        info.Clear();
        info.SetId(0);
        auto idx = m_listview->InsertItem(info);
        m_listview->SetItem(idx, 0, "meaning");
        m_listview->SetItem(idx, 1, "42");
    }
    m_listview->SetToolTip("Separate content columns with a semi-colon (;)");
    box_sizer_12->Add(m_listview, wxSizerFlags().Border(wxALL));

    flex_grid_sizer->Add(box_sizer_12, wxSizerFlags().Border(wxALL));

    auto* box_sizer_13 = new wxBoxSizer(wxHORIZONTAL);

    m_edit_listbox = new wxEditableListBox(page_5, wxID_ANY, "My Editable ListBox", wxDefaultPosition, wxDefaultSize,
        wxEL_ALLOW_NEW|wxEL_ALLOW_EDIT|wxEL_ALLOW_DELETE);
    box_sizer_13->Add(m_edit_listbox, wxSizerFlags().Border(wxALL));

    flex_grid_sizer->Add(box_sizer_13, wxSizerFlags().Border(wxALL));

    box_sizer_5->Add(flex_grid_sizer, wxSizerFlags().Border(wxALL));
    page_5->SetSizerAndFit(box_sizer_5);

    auto* page_3 = new wxPanel(m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    m_notebook->AddPage(page_3, "Combos");

    auto* page_sizer_2 = new wxBoxSizer(wxVERTICAL);

    auto* static_box = new wxStaticBoxSizer(wxVERTICAL, page_3, "Combos and Choices");

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

    m_checkList_2 = new wxCheckListBox(static_box_sizer5->GetStaticBox(), wxID_ANY);
    m_checkList_2->Append("item #1");
    m_checkList_2->Append("item #2");
    m_checkList_2->Append("item #0");
    static_box_sizer5->Add(m_checkList_2, wxSizerFlags().Border(wxALL));

    m_staticText10 = new wxStaticText(static_box_sizer5->GetStaticBox(), wxID_ANY, "Sorted");
    static_box_sizer5->Add(m_staticText10, wxSizerFlags().Border(wxALL));

    m_checkList2 = new wxCheckListBox(static_box_sizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr,
        wxLB_SINGLE|wxLB_SORT);
    m_checkList2->Append("item #1");
    m_checkList2->Append("item #2");
    m_checkList2->Append("item #0");
    static_box_sizer5->Add(m_checkList2, wxSizerFlags().Border(wxALL));

    box_sizer3->Add(static_box_sizer5, wxSizerFlags().Expand().Border(wxALL));

    static_box->Add(box_sizer3, wxSizerFlags().Expand().Border(wxALL));

    page_sizer_2->Add(static_box, wxSizerFlags().Expand().Border(wxALL));
    page_3->SetSizerAndFit(page_sizer_2);

    auto* page_6 = new wxPanel(m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME|wxTAB_TRAVERSAL);
    m_notebook->AddPage(page_6, "Pickers");

    auto* parent_sizer2 = new wxBoxSizer(wxVERTICAL);

    auto* static_box_2 = new wxStaticBoxSizer(wxVERTICAL, page_6, "Pickers");

    auto* box_sizer = new wxBoxSizer(wxHORIZONTAL);

    auto* staticText__2 = new wxStaticText(static_box_2->GetStaticBox(), wxID_ANY, "File:");
    box_sizer->Add(staticText__2, wxSizerFlags().Center().Border(wxALL));

    m_filePicker = new wxFilePickerCtrl(static_box_2->GetStaticBox(), wxID_ANY, wxEmptyString, wxFileSelectorPromptStr,
        "BMP files|*.bmp", wxDefaultPosition, wxDefaultSize, wxFLP_USE_TEXTCTRL|wxFLP_OPEN|wxFLP_FILE_MUST_EXIST);
    box_sizer->Add(m_filePicker, wxSizerFlags().Border(wxALL));

    static_box_2->Add(box_sizer, wxSizerFlags().Border(wxALL));

    auto* box_sizer_2 = new wxBoxSizer(wxHORIZONTAL);

    auto* staticText__3 = new wxStaticText(static_box_2->GetStaticBox(), wxID_ANY, "Directory:");
    box_sizer_2->Add(staticText__3, wxSizerFlags().Center().Border(wxALL));

    m_dirPicker = new wxDirPickerCtrl(static_box_2->GetStaticBox(), wxID_ANY, ".", wxDirSelectorPromptStr,
        wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_SMALL);
    box_sizer_2->Add(m_dirPicker, wxSizerFlags().Border(wxALL));

    static_box_2->Add(box_sizer_2, wxSizerFlags().Border(wxALL));

    auto* box_sizer_4 = new wxBoxSizer(wxHORIZONTAL);

    auto* staticText__4 = new wxStaticText(static_box_2->GetStaticBox(), wxID_ANY, "Colour:");
    box_sizer_4->Add(staticText__4, wxSizerFlags().Center().Border(wxALL));

    m_colourPicker = new wxColourPickerCtrl(static_box_2->GetStaticBox(), wxID_ANY, *wxBLACK);
    box_sizer_4->Add(m_colourPicker, wxSizerFlags().Border(wxALL));

    static_box_2->Add(box_sizer_4, wxSizerFlags().Border(wxALL));

    auto* box_sizer_6 = new wxBoxSizer(wxHORIZONTAL);

    auto* staticText__5 = new wxStaticText(static_box_2->GetStaticBox(), wxID_ANY, "Date:");
    box_sizer_6->Add(staticText__5, wxSizerFlags().Center().Border(wxALL));

    m_datePicker = new wxDatePickerCtrl(static_box_2->GetStaticBox(), wxID_ANY, wxDefaultDateTime);
    box_sizer_6->Add(m_datePicker, wxSizerFlags().Border(wxALL));

    static_box_2->Add(box_sizer_6, wxSizerFlags().Border(wxALL));

    auto* box_sizer_8 = new wxBoxSizer(wxHORIZONTAL);

    auto* staticText__6 = new wxStaticText(static_box_2->GetStaticBox(), wxID_ANY, "Time:");
    box_sizer_8->Add(staticText__6, wxSizerFlags().Center().Border(wxALL));

    m_timePicker = new wxTimePickerCtrl(static_box_2->GetStaticBox(), wxID_ANY, wxDefaultDateTime);
    box_sizer_8->Add(m_timePicker, wxSizerFlags().Border(wxALL));

    static_box_2->Add(box_sizer_8, wxSizerFlags().Border(wxALL));

    auto* box_sizer_9 = new wxBoxSizer(wxHORIZONTAL);

    auto* staticText__7 = new wxStaticText(static_box_2->GetStaticBox(), wxID_ANY, "Font:");
    box_sizer_9->Add(staticText__7, wxSizerFlags().Center().Border(wxALL));

    m_fontPicker = new wxFontPickerCtrl(static_box_2->GetStaticBox(), wxID_ANY, wxFont(wxNORMAL_FONT->GetPointSize(),
        wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Comic Sans MS"), wxDefaultPosition,
        wxDefaultSize, wxFNTP_DEFAULT_STYLE|wxFNTP_USE_TEXTCTRL);
    box_sizer_9->Add(m_fontPicker, wxSizerFlags().Border(wxALL));

    static_box_2->Add(box_sizer_9, wxSizerFlags().Border(wxALL));

    parent_sizer2->Add(static_box_2, wxSizerFlags().Expand().Border(wxALL));
    page_6->SetSizerAndFit(parent_sizer2);

    auto* page = new wxPanel(m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    m_notebook->AddPage(page, "Tab 3");

    auto* page_sizer_3 = new wxBoxSizer(wxVERTICAL);

    m_staticText = new wxStaticText(page, wxID_ANY, "TODO: replace this control with something more useful...");
    m_staticText->Wrap(200);
    page_sizer_3->Add(m_staticText, wxSizerFlags().Border(wxALL));
    page->SetSizerAndFit(page_sizer_3);

    auto* box_sizer_14 = new wxBoxSizer(wxHORIZONTAL);

    auto* staticText_4 = new wxStaticText(this, wxID_ANY, "Events:");
    box_sizer_14->Add(staticText_4, wxSizerFlags().Center().Border(wxALL));

    auto* btn = new wxButton(this, wxID_ANY, "Clear Events");
    box_sizer_14->Add(btn, wxSizerFlags().Border(wxALL));

    dlg_sizer->Add(box_sizer_14, wxSizerFlags().Border(wxALL));

    m_events_list = new wxListBox(this, wxID_ANY);
    m_events_list->SetMinSize(ConvertDialogToPixels(wxSize(-1, 60)));
    dlg_sizer->Add(m_events_list, wxSizerFlags().Expand().Border(wxALL));

    auto* stdBtn = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    dlg_sizer->Add(CreateSeparatedSizer(stdBtn), wxSizerFlags().Expand().Border(wxALL));

    SetSizerAndFit(dlg_sizer);
    Centre(wxBOTH);

    // Event handlers
    Bind(wxEVT_INIT_DIALOG, &MainTestDialog::OnInit, this);
    m_notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MainTestDialog::OnPageChanged, this);
    m_text_ctrl->Bind(wxEVT_TEXT, &MainTestDialog::OnText, this);
    m_richText->Bind(wxEVT_TEXT, &MainTestDialog::OnRichText, this);
    m_scintilla->Bind(wxEVT_STC_CHANGE, &MainTestDialog::OnStcChange, this);
    m_btn->Bind(wxEVT_BUTTON, &MainTestDialog::OnButton, this);
    m_btn_bitmaps->Bind(wxEVT_BUTTON, &MainTestDialog::OnButton, this);
    m_toggleBtn->Bind(wxEVT_TOGGLEBUTTON, &MainTestDialog::OnToggle, this);
    disable_bitmaps->Bind(wxEVT_CHECKBOX, &MainTestDialog::OnDisableBitmapsBtn, this);
    m_btn_5->Bind(wxEVT_BUTTON, &MainTestDialog::OnButton, this);
    radioBox->Bind(wxEVT_RADIOBOX, &MainTestDialog::OnRadioBox, this);
    m_btn_3->Bind(wxEVT_BUTTON, &MainTestDialog::OnButton, this);
    btn2->Bind(wxEVT_BUTTON, &MainTestDialog::OnPopupBtn, this);
    m_radioBtn->Bind(wxEVT_RADIOBUTTON, &MainTestDialog::OnRadioButton, this);
    m_radioBtn2->Bind(wxEVT_RADIOBUTTON, &MainTestDialog::OnRadioButton, this);
    m_checkBox2->Bind(wxEVT_CHECKBOX, &MainTestDialog::OnCheckBox, this);
    m_comboBox->Bind(wxEVT_COMBOBOX, &MainTestDialog::OnCombobox, this);
    m_comboBox2->Bind(wxEVT_COMBOBOX, &MainTestDialog::OnCombobox, this);
    m_choice->Bind(wxEVT_CHOICE, &MainTestDialog::OnChoice, this);
    m_choice2->Bind(wxEVT_CHOICE, &MainTestDialog::OnChoice, this);
    m_listbox->Bind(wxEVT_LISTBOX, &MainTestDialog::OnListBox, this);
    m_listBox2->Bind(wxEVT_LISTBOX, &MainTestDialog::OnListBox, this);
    m_checkList_2->Bind(wxEVT_CHECKLISTBOX, &MainTestDialog::OnListChecked, this);
    m_checkList2->Bind(wxEVT_CHECKLISTBOX, &MainTestDialog::OnListChecked, this);
    m_filePicker->Bind(wxEVT_FILEPICKER_CHANGED, &MainTestDialog::OnFileChanged, this);
    m_dirPicker->Bind(wxEVT_DIRPICKER_CHANGED, &MainTestDialog::OnDirChanged, this);
    m_colourPicker->Bind(wxEVT_COLOURPICKER_CHANGED, &MainTestDialog::OnColourChanged, this);
    m_datePicker->Bind(wxEVT_DATE_CHANGED, &MainTestDialog::OnDateChanged, this);
    m_timePicker->Bind(wxEVT_TIME_CHANGED, &MainTestDialog::OnTimeChanged, this);
    m_fontPicker->Bind(wxEVT_FONTPICKER_CHANGED, &MainTestDialog::OnFontChanged, this);
    btn->Bind(wxEVT_BUTTON, &MainTestDialog::OnClearList, this);

    return true;
}

namespace wxue_img
{

    const unsigned char focus_png[517] {
        137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,16,0,0,0,16,8,6,0,0,0,31,243,255,97,0,0,0,9,112,72,89,
        115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,1,183,73,68,65,84,56,203,205,147,177,138,226,80,20,134,191,68,99,
        33,25,19,240,142,140,177,8,11,10,214,18,16,11,177,218,222,41,23,242,26,190,132,32,214,211,167,28,216,71,16,
        196,34,133,108,229,140,6,89,86,69,6,217,181,8,67,118,83,36,195,221,98,149,113,86,167,222,253,203,123,206,249,
        57,223,57,247,192,191,151,174,75,116,93,254,245,170,92,200,84,206,234,50,25,169,112,119,39,185,191,199,122,
        120,64,211,52,0,214,235,245,37,3,108,219,150,0,137,148,60,57,14,204,231,100,255,120,43,12,6,3,106,181,26,155,
        205,134,126,191,191,244,125,255,35,176,58,22,183,219,237,229,112,56,4,96,25,199,124,122,124,132,249,28,21,
        0,249,74,48,153,76,232,116,58,85,215,117,191,1,215,192,117,163,209,248,220,235,245,170,231,80,202,161,131,
        19,213,235,117,198,227,49,186,174,227,186,238,119,128,102,179,137,101,89,231,76,82,190,34,28,181,223,239,41,
        20,10,36,73,66,46,151,195,178,44,90,173,214,187,59,80,49,12,184,185,121,55,161,219,237,98,24,6,229,114,249,
        109,160,92,6,211,36,203,213,21,148,74,100,50,25,108,219,198,113,28,22,139,5,249,124,158,56,142,49,77,147,36,
        73,40,22,139,228,114,57,0,126,62,63,67,54,11,186,126,24,34,160,170,42,66,8,102,179,25,149,74,133,40,138,240,
        60,79,9,195,176,164,105,26,219,237,22,33,4,66,8,76,195,56,65,56,40,77,83,130,32,160,90,173,50,26,141,190,122,
        158,167,0,56,142,243,35,12,195,15,0,65,16,16,4,1,171,213,234,196,96,183,131,197,2,41,37,81,20,97,89,22,190,
        239,191,89,153,227,56,171,48,12,157,40,138,136,162,136,95,113,12,65,0,187,29,42,105,10,183,183,40,138,34,0,
        1,136,233,116,122,233,39,126,57,198,21,16,188,188,64,154,254,7,183,248,27,183,73,156,116,14,159,88,75,0,0,
        0,0,73,69,78,68,174,66,96,130
    };

    const unsigned char no_hour_png[347] {
        137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,16,0,0,0,16,8,6,0,0,0,31,243,255,97,0,0,0,9,112,72,89,
        115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,1,13,73,68,65,84,56,203,157,147,49,106,195,48,20,134,63,133,52,
        55,40,89,3,29,60,102,136,33,23,17,244,8,33,107,105,192,119,72,47,144,27,116,8,25,61,152,92,32,240,188,120,
        47,100,77,186,4,186,165,195,235,80,91,72,170,154,154,254,96,100,75,254,62,158,45,61,163,160,0,102,179,129,
        241,152,32,167,19,201,44,22,223,16,96,58,1,128,89,175,195,23,15,135,36,175,219,173,187,55,0,190,228,37,150,
        68,121,94,173,124,216,24,103,245,36,159,215,43,77,211,252,128,103,121,30,192,0,131,110,162,22,113,139,119,
        163,17,101,89,2,184,49,5,7,17,145,165,181,86,21,220,101,173,213,162,40,130,57,96,73,74,208,102,154,101,217,
        135,15,68,240,148,158,169,18,112,255,136,200,253,191,5,34,50,185,241,9,55,65,35,34,143,62,32,34,42,34,41,137,
        251,137,3,207,241,52,203,243,215,238,225,253,124,38,181,197,173,68,137,77,65,137,170,212,117,221,255,32,197,
        240,111,73,84,194,48,232,131,253,158,135,227,17,128,183,203,37,41,201,189,250,21,212,4,237,60,159,255,221,
        141,85,5,187,29,218,86,250,5,221,104,175,34,43,162,179,222,0,0,0,0,73,69,78,68,174,66,96,130
    };

    const unsigned char normal_png[508] {
        137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,16,0,0,0,16,8,6,0,0,0,31,243,255,97,0,0,0,9,112,72,89,
        115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,1,174,73,68,65,84,56,203,165,147,177,110,218,96,20,133,63,215,134,
        129,120,176,84,90,69,130,161,168,68,78,36,166,202,3,3,11,207,192,82,41,188,5,143,193,19,100,247,144,78,97,
        98,71,44,12,255,3,32,135,1,15,216,33,53,137,227,88,66,5,193,223,33,216,36,181,211,14,61,211,255,95,221,115,
        238,213,209,61,10,9,174,174,36,154,6,167,167,105,137,231,103,120,122,34,131,94,15,226,88,1,208,210,162,166,
        193,205,13,156,159,31,27,239,239,225,238,14,164,124,249,43,202,241,157,208,146,199,245,201,73,89,94,94,6,138,
        162,160,105,26,251,253,158,221,110,151,51,188,135,119,152,254,70,160,94,175,3,160,235,58,166,105,18,4,1,174,
        235,102,4,10,133,66,254,6,9,28,199,97,56,28,210,104,52,16,66,0,80,46,151,153,78,167,180,90,173,140,96,186,
        138,16,66,177,44,75,54,155,205,89,187,221,254,186,88,44,208,117,29,128,40,138,168,84,42,140,70,163,217,100,
        50,57,59,240,228,27,129,215,232,118,187,82,215,245,212,3,85,85,137,227,24,219,182,107,192,60,119,131,60,145,
        98,177,8,192,102,179,193,182,237,207,192,207,63,251,180,60,178,16,226,147,97,24,132,97,200,96,48,96,62,159,
        191,55,7,53,135,252,197,48,140,197,118,187,165,84,42,81,171,213,144,82,178,92,46,207,124,223,255,241,87,19,
        129,111,134,97,8,128,106,181,202,106,181,194,247,125,0,60,207,163,223,239,207,198,227,113,190,137,66,136,143,
        64,240,175,59,232,116,58,184,174,155,242,62,240,159,72,77,156,173,215,72,160,4,252,90,173,8,163,8,111,189,
        206,16,182,239,101,225,187,227,4,168,42,152,38,220,222,190,20,31,31,225,224,65,10,203,130,135,7,153,164,241,
        120,7,23,23,217,56,199,49,132,97,54,137,142,3,187,157,2,240,27,89,2,185,55,227,129,139,244,0,0,0,0,73,69,78,
        68,174,66,96,130
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

#include "mainframe.h"  // auto-generated: ../wxui_generated/mainframe_base.h and ../wxui_generated/mainframe_base.cpp

void MainFrame::OnMainTestDlg(wxCommandEvent& WXUNUSED(event))
{
    MainTestDialog dlg(this);
    dlg.ShowModal();
}