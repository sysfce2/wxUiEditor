////////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor -- see https://github.com/KeyWorksRW/wxUiEditor/
//
// DO NOT EDIT THIS FILE! Your changes will be lost if it is re-generated!
////////////////////////////////////////////////////////////////////////////////

#include <wx/icon.h>

#include "import_base.h"

#include <wx/mstream.h>  // memory stream classes
#include <wx/zstream.h>  // zlib stream classes

#include <memory>  // for std::make_unique

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

namespace wxue_img
{
    extern const unsigned char import_svg[418];
}

bool ImportBase::Create(wxWindow* parent, wxWindowID id, const wxString& title,
        const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxDialog::Create(parent, id, title, pos, size, style, name))
        return false;

    SetIcon(wxueBundleSVG(wxue_img::import_svg, 418, 1013, wxSize(16, 16)).GetIconFor(this));

    auto parent_sizer = new wxBoxSizer(wxVERTICAL);

    m_import_staticbox = new wxStaticBoxSizer(wxVERTICAL, this, "Import Type");
    parent_sizer->Add(m_import_staticbox, wxSizerFlags().Expand().Border(wxALL));

    auto flex_grid_sizer = new wxFlexGridSizer(2, 0, 0);
    m_import_staticbox->Add(flex_grid_sizer, wxSizerFlags().Border(wxALL));

    m_radio_wxCrafter = new wxRadioButton(m_import_staticbox->GetStaticBox(), wxID_ANY, "wx&Crafter Project(s)", wxDefaultPosition, wxDefaultSize,
        wxRB_GROUP);
    flex_grid_sizer->Add(m_radio_wxCrafter, wxSizerFlags().Border(wxALL));

    m_radio_wxFormBuilder = new wxRadioButton(m_import_staticbox->GetStaticBox(), wxID_ANY, "wx&FormBuilder Project(s)");
    flex_grid_sizer->Add(m_radio_wxFormBuilder, wxSizerFlags().Border(wxALL));

    m_radio_wxGlade = new wxRadioButton(m_import_staticbox->GetStaticBox(), wxID_ANY, "wx&Glade Project(s)");
    flex_grid_sizer->Add(m_radio_wxGlade, wxSizerFlags().Border(wxALL));

    m_radio_wxSmith = new wxRadioButton(m_import_staticbox->GetStaticBox(), wxID_ANY, "wx&Smith Project(s)");
    flex_grid_sizer->Add(m_radio_wxSmith, wxSizerFlags().Border(wxALL));

    m_radio_WindowsResource = new wxRadioButton(m_import_staticbox->GetStaticBox(), wxID_ANY, "&Windows Resource");
    flex_grid_sizer->Add(m_radio_WindowsResource, wxSizerFlags().Border(wxALL));

    m_radio_XRC = new wxRadioButton(m_import_staticbox->GetStaticBox(), wxID_ANY, "&XRC File(s)");
    flex_grid_sizer->Add(m_radio_XRC, wxSizerFlags().Border(wxALL));

    auto box_sizer = new wxBoxSizer(wxHORIZONTAL);
    m_import_staticbox->Add(box_sizer, wxSizerFlags().Border(wxALL));

    m_combo_recent_dirs = new wxComboBox(m_import_staticbox->GetStaticBox(), wxID_ANY, wxEmptyString);
    m_combo_recent_dirs->Hide();
    m_combo_recent_dirs->SetInitialSize(wxSize(240 > GetBestSize().x ? 240 : -1, -1));
    box_sizer->Add(m_combo_recent_dirs, wxSizerFlags().Border(wxALL));

    m_btnRemove = new wxButton(m_import_staticbox->GetStaticBox(), wxID_ANY, "Remove");
    m_btnRemove->Hide();
    box_sizer->Add(m_btnRemove, wxSizerFlags().Border(wxALL));

    auto box_sizer6 = new wxBoxSizer(wxHORIZONTAL);
    m_import_staticbox->Add(box_sizer6, wxSizerFlags().Expand().Border(wxALL));

    m_btnAddFile = new wxButton(m_import_staticbox->GetStaticBox(), wxID_ANY, "&Directory...");
    m_btnAddFile->SetToolTip("You can add multiple formbuilder projects to a single wxUiEdtior project.");
    box_sizer6->Add(m_btnAddFile, wxSizerFlags().Center().Border(wxLEFT|wxRIGHT|wxTOP, wxSizerFlags::GetDefaultBorder()));

    m_static_cwd = new wxStaticText(m_import_staticbox->GetStaticBox(), wxID_ANY, "...", wxDefaultPosition, wxDefaultSize,
        wxST_ELLIPSIZE_MIDDLE);
    box_sizer6->Add(m_static_cwd, wxSizerFlags(1).Center().Border(wxALL));

    auto box_sizer7 = new wxBoxSizer(wxVERTICAL);
    m_import_staticbox->Add(box_sizer7, wxSizerFlags(1).Expand().Border(wxALL));

    m_staticImportList = new wxStaticText(m_import_staticbox->GetStaticBox(), wxID_ANY, "&Files:");
    box_sizer7->Add(m_staticImportList, wxSizerFlags().Border(wxLEFT|wxRIGHT|wxTOP, wxSizerFlags::GetDefaultBorder()));

    m_checkListProjects = new wxCheckListBox(m_import_staticbox->GetStaticBox(), wxID_ANY);
    m_checkListProjects->SetMinSize(wxSize(-1, 240));
    box_sizer7->Add(m_checkListProjects, wxSizerFlags().Expand().Border(wxALL));

    auto box_sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    box_sizer7->Add(box_sizer_2, wxSizerFlags().Border(wxALL));

    auto btn_2 = new wxButton(m_import_staticbox->GetStaticBox(), wxID_ANY, "Select &All");
    box_sizer_2->Add(btn_2, wxSizerFlags().Border(wxALL));

    auto btn__2 = new wxButton(m_import_staticbox->GetStaticBox(), wxID_ANY, "Select &None");
    box_sizer_2->Add(btn__2, wxSizerFlags().Border(wxALL));

    m_stdBtn = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    parent_sizer->Add(CreateSeparatedSizer(m_stdBtn), wxSizerFlags().Expand().Border(wxALL));

    SetSizerAndFit(parent_sizer);
    Centre(wxBOTH);

    // Event handlers
    Bind(wxEVT_INIT_DIALOG, &ImportBase::OnInitDialog, this);
    m_radio_wxCrafter->Bind(wxEVT_RADIOBUTTON, &ImportBase::OnCrafter, this);
    m_radio_wxFormBuilder->Bind(wxEVT_RADIOBUTTON, &ImportBase::OnFormBuilder, this);
    m_radio_wxGlade->Bind(wxEVT_RADIOBUTTON, &ImportBase::OnWxGlade, this);
    m_radio_wxSmith->Bind(wxEVT_RADIOBUTTON, &ImportBase::OnWxSmith, this);
    m_radio_WindowsResource->Bind(wxEVT_RADIOBUTTON, &ImportBase::OnWindowsResource, this);
    m_radio_XRC->Bind(wxEVT_RADIOBUTTON, &ImportBase::OnXRC, this);
    m_combo_recent_dirs->Bind(wxEVT_COMBOBOX, &ImportBase::OnRecentDir, this);
    m_btnRemove->Bind(wxEVT_BUTTON, &ImportBase::OnRemove, this);
    m_btnAddFile->Bind(wxEVT_BUTTON, &ImportBase::OnDirectory, this);
    m_checkListProjects->Bind(wxEVT_CHECKLISTBOX, &ImportBase::OnCheckFiles, this);
    btn_2->Bind(wxEVT_BUTTON, &ImportBase::OnSelectAll, this);
    btn__2->Bind(wxEVT_BUTTON, &ImportBase::OnSelectNone, this);
    Bind(wxEVT_BUTTON, &ImportBase::OnOK, this, wxID_OK);

    return true;
}
