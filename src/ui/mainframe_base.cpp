////////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor -- see https://github.com/KeyWorksRW/wxUiEditor/
//
// DO NOT EDIT THIS FILE! Your changes will be lost if it is re-generated!
////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>

#include "mainframe.h"

#include "mainframe_base.h"

#include "../xpm/alignbottom_png.hxx"
#include "../xpm/aligncenter_png.hxx"
#include "../xpm/alignleft_png.hxx"
#include "../xpm/alignright_png.hxx"
#include "../xpm/aligntop_png.hxx"
#include "../xpm/alignvertcenter_png.hxx"
#include "../xpm/bottom.xpm"
#include "../xpm/expand.xpm"
#include "../xpm/generate.xpm"
#include "../xpm/hidden.xpm"
#include "../xpm/left.xpm"
#include "../xpm/magnify.xpm"
#include "../xpm/nav_movedown_png.hxx"
#include "../xpm/nav_moveleft_png.hxx"
#include "../xpm/nav_moveright_png.hxx"
#include "../xpm/nav_moveup_png.hxx"
#include "../xpm/right.xpm"
#include "../xpm/top.xpm"

#include <wx/mstream.h>  // Memory stream classes

// Convert a data header file into a wxImage
static wxImage GetImgFromHdr(const unsigned char* data, size_t size_data)
{
    wxMemoryInputStream strm(data, size_data);
    wxImage image;
    image.LoadFile(strm);
    return image;
};

MainFrameBase::MainFrameBase(wxWindow* parent, wxWindowID id, const wxString& title,
		const wxPoint& pos, const wxSize& size, long style) :
	wxFrame(parent, id, title, pos, size, style)
{
    SetSizeHints(wxSize(800, 800));

    m_menubar = new wxMenuBar();

    m_menuFile = new wxMenu();

    auto menuItem = new wxMenuItem(m_menuFile, id_NewProject, wxString::FromUTF8("&New Project...\tCtrl+N"),
    wxString::FromUTF8("Create an empty project"), wxITEM_NORMAL);
    menuItem->SetBitmap(wxArtProvider::GetBitmap(wxART_NEW, wxART_MENU));
    m_menuFile->Append(menuItem);

    auto menuItem2 = new wxMenuItem(m_menuFile, id_OpenProject, wxString::FromUTF8("&Open Project...\tCtrl+O"),
    wxString::FromUTF8("Open a project"), wxITEM_NORMAL);
    menuItem2->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_MENU));
    m_menuFile->Append(menuItem2);

    m_submenu_recent = new wxMenu();
    m_menuFile->AppendSubMenu(m_submenu_recent, wxString::FromUTF8("Open &Recent"));

    m_menuFile->AppendSeparator();

    auto menu_item = new wxMenuItem(m_menuFile, wxID_SAVE, wxString::FromUTF8("&Save\tCtrl+S"),
    wxString::FromUTF8("Save current project"), wxITEM_NORMAL);
    menu_item->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_MENU));
    m_menuFile->Append(menu_item);

    auto menu_item2 = new wxMenuItem(m_menuFile, id_SaveProjectAs, wxString::FromUTF8("Save &As...\tCtrl-Shift+S"),
    wxString::FromUTF8("Save current project to a different filename"), wxITEM_NORMAL);
    menu_item2->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS, wxART_MENU));
    m_menuFile->Append(menu_item2);

    m_menuFile->AppendSeparator();

    auto submenu = new wxMenu();

    auto menu_item_1 = new wxMenuItem(submenu, id_AppendFormBuilder, wxString::FromUTF8("wxFormBuilder Project..."),
    wxString::FromUTF8("Append wxFormBuilder project into current project"), wxITEM_NORMAL);
    submenu->Append(menu_item_1);

    auto menu_item_2 = new wxMenuItem(submenu, id_AppendGlade, wxString::FromUTF8("wxGlade Project..."),
    wxString::FromUTF8("Append wxGlade project into current project"), wxITEM_NORMAL);
    submenu->Append(menu_item_2);

    auto menu_item_3 = new wxMenuItem(submenu, id_AppendSmith, wxString::FromUTF8("wxSmith Project..."),
    wxString::FromUTF8("Append wxSmith project into current project"), wxITEM_NORMAL);
    submenu->Append(menu_item_3);

    auto menu_item_4 = new wxMenuItem(submenu, id_AppendXRC, wxString::FromUTF8("XRC Project..."),
    wxString::FromUTF8("Append XRC project into current project"), wxITEM_NORMAL);
    submenu->Append(menu_item_4);
    m_menuFile->AppendSubMenu(submenu, wxString::FromUTF8("&Append"));

    m_menuFile->AppendSeparator();

    auto menu_preferences = new wxMenuItem(m_menuFile, id_OptionsDlg, wxString::FromUTF8("&Options..."),
    wxString::FromUTF8("Code generation options"), wxITEM_NORMAL);
    m_menuFile->Append(menu_preferences);

    m_menuFile->AppendSeparator();

    auto menu_quit = new wxMenuItem(m_menuFile, wxID_EXIT, wxEmptyString);
    menu_quit->SetBitmap(wxArtProvider::GetBitmap(wxART_QUIT, wxART_MENU));
    m_menuFile->Append(menu_quit);
    m_menubar->Append(m_menuFile, wxString::FromUTF8("&File"));

    m_menuEdit = new wxMenu();

    auto menu_undo = new wxMenuItem(m_menuEdit, wxID_UNDO, wxEmptyString);
    menu_undo->SetBitmap(wxArtProvider::GetBitmap(wxART_UNDO, wxART_MENU));
    m_menuEdit->Append(menu_undo);

    auto menu_redo = new wxMenuItem(m_menuEdit, wxID_REDO, wxEmptyString);
    menu_redo->SetBitmap(wxArtProvider::GetBitmap(wxART_REDO, wxART_MENU));
    m_menuEdit->Append(menu_redo);

    m_menuEdit->AppendSeparator();

    auto menu_cut = new wxMenuItem(m_menuEdit, wxID_CUT, wxEmptyString);
    menu_cut->SetBitmap(wxArtProvider::GetBitmap(wxART_CUT, wxART_MENU));
    m_menuEdit->Append(menu_cut);

    auto menu_copy = new wxMenuItem(m_menuEdit, wxID_COPY, wxEmptyString);
    menu_copy->SetBitmap(wxArtProvider::GetBitmap(wxART_COPY, wxART_MENU));
    m_menuEdit->Append(menu_copy);

    auto menu_paste = new wxMenuItem(m_menuEdit, wxID_PASTE, wxEmptyString);
    menu_paste->SetBitmap(wxArtProvider::GetBitmap(wxART_PASTE, wxART_MENU));
    m_menuEdit->Append(menu_paste);

    auto menu_delete = new wxMenuItem(m_menuEdit, wxID_DELETE, wxEmptyString,
    wxString::FromUTF8("Delete selected object without using clipboard."), wxITEM_NORMAL);
    menu_delete->SetBitmap(wxArtProvider::GetBitmap(wxART_DELETE, wxART_MENU));
    m_menuEdit->Append(menu_delete);

    m_menuEdit->AppendSeparator();

    auto menu_find = new wxMenuItem(m_menuEdit, wxID_FIND, wxEmptyString,
    wxString::FromUTF8("Find text in the active code viewer."), wxITEM_NORMAL);
    menu_find->SetBitmap(wxArtProvider::GetBitmap(wxART_FIND, wxART_MENU));
    m_menuEdit->Append(menu_find);

    auto menu_insert_widget = new wxMenuItem(m_menuEdit, id_insert_widget, wxString::FromUTF8("&Insert widget..."),
    wxString::FromUTF8("Find text in the active code viewer."), wxITEM_NORMAL);
    menu_insert_widget->SetBitmap(wxArtProvider::GetBitmap(wxART_EDIT, wxART_MENU));
    m_menuEdit->Append(menu_insert_widget);

    m_menuEdit->AppendSeparator();

    auto submenu3 = new wxMenu();

    auto menu_item4 = new wxMenuItem(submenu3, id_MoveUp, wxString::FromUTF8("Up") + '\t' + "Alt+Up",
    wxString::FromUTF8("Moves selected item up"), wxITEM_NORMAL);
    menu_item4->SetBitmap(GetImgFromHdr(nav_moveup_png, sizeof(nav_moveup_png)));
    submenu3->Append(menu_item4);

    auto menu_item5 = new wxMenuItem(submenu3, id_MoveDown, wxString::FromUTF8("Down") + '\t' + "Alt+Down",
    wxString::FromUTF8("Moves selected item down"), wxITEM_NORMAL);
    menu_item5->SetBitmap(GetImgFromHdr(nav_movedown_png, sizeof(nav_movedown_png)));
    submenu3->Append(menu_item5);

    auto menu_item6 = new wxMenuItem(submenu3, id_MoveLeft, wxString::FromUTF8("Left") + '\t' + "Alt+Left",
    wxString::FromUTF8("Moves selected item left"), wxITEM_NORMAL);
    menu_item6->SetBitmap(GetImgFromHdr(nav_moveleft_png, sizeof(nav_moveleft_png)));
    submenu3->Append(menu_item6);

    auto menu_item7 = new wxMenuItem(submenu3, id_MoveRight, wxString::FromUTF8("Right") + '\t' + "Alt+Right",
    wxString::FromUTF8("Moves selected item right"), wxITEM_NORMAL);
    menu_item7->SetBitmap(GetImgFromHdr(nav_moveright_png, sizeof(nav_moveright_png)));
    submenu3->Append(menu_item7);
    m_menuEdit->AppendSubMenu(submenu3, wxString::FromUTF8("Move"));

    auto submenu2 = new wxMenu();

    auto menu_item8 = new wxMenuItem(submenu2, id_AlignLeft, wxString::FromUTF8("&Left") + '\t' + "Alt+Shift+Left",
    wxString::FromUTF8("Align selected item to the left"), wxITEM_CHECK);
    menu_item8->SetBitmap(GetImgFromHdr(alignleft_png, sizeof(alignleft_png)));
    submenu2->Append(menu_item8);

    auto menu_item10 = new wxMenuItem(submenu2, id_AlignCenterHorizontal, wxString::FromUTF8("Center &Horizontal") + '\t' + "Alt+Shift+H",
    wxString::FromUTF8("Align selected item to the center horizontally"), wxITEM_CHECK);
    menu_item10->SetBitmap(GetImgFromHdr(aligncenter_png, sizeof(aligncenter_png)));
    submenu2->Append(menu_item10);
    menu_item10->Check();

    auto menu_item9 = new wxMenuItem(submenu2, id_AlignRight, wxString::FromUTF8("&Right") + '\t' + "Alt+Shift+Right",
    wxString::FromUTF8("Align selected item to the right"), wxITEM_CHECK);
    menu_item9->SetBitmap(GetImgFromHdr(alignright_png, sizeof(alignright_png)));
    submenu2->Append(menu_item9);

    submenu2->AppendSeparator();

    auto menu_item11 = new wxMenuItem(submenu2, id_AlignTop, wxString::FromUTF8("&Top") + '\t' + "Alt+Shift+Up",
    wxString::FromUTF8("Align selected item to the top"), wxITEM_CHECK);
    menu_item11->SetBitmap(GetImgFromHdr(aligntop_png, sizeof(aligntop_png)));
    submenu2->Append(menu_item11);

    auto menu_item12 = new wxMenuItem(submenu2, id_AlignCenterVertical, wxString::FromUTF8("Center &Vertical") + '\t' + "Alt+Shift+V",
    wxString::FromUTF8("Align selected item to the center vertically"), wxITEM_CHECK);
    menu_item12->SetBitmap(GetImgFromHdr(alignvertcenter_png, sizeof(alignvertcenter_png)));
    submenu2->Append(menu_item12);

    auto menu_item13 = new wxMenuItem(submenu2, id_AlignBottom, wxString::FromUTF8("&Bottom") + '\t' + "Alt+Shift+Down",
    wxString::FromUTF8("Align selected item to the bottom"), wxITEM_CHECK);
    menu_item13->SetBitmap(GetImgFromHdr(alignbottom_png, sizeof(alignbottom_png)));
    submenu2->Append(menu_item13);
    m_menuEdit->AppendSubMenu(submenu2, wxString::FromUTF8("Align"));

    auto submenu4 = new wxMenu();

    auto menu_item14 = new wxMenuItem(submenu4, id_BorderLeft, wxString::FromUTF8("&Left"),
    wxString::FromUTF8("Toggle border on the left side of the item"), wxITEM_CHECK);
    submenu4->Append(menu_item14);

    auto menu_item15 = new wxMenuItem(submenu4, id_BorderRight, wxString::FromUTF8("&Right"),
    wxString::FromUTF8("Toggle border on the right side of the item"), wxITEM_CHECK);
    submenu4->Append(menu_item15);

    auto menu_item16 = new wxMenuItem(submenu4, id_BorderTop, wxString::FromUTF8("&Top"),
    wxString::FromUTF8("Toggle border on the top side of the item"), wxITEM_CHECK);
    submenu4->Append(menu_item16);

    auto menu_item17 = new wxMenuItem(submenu4, id_BorderBottom, wxString::FromUTF8("&Bottom"),
    wxString::FromUTF8("Toggle border on the bottom side of the item"), wxITEM_CHECK);
    submenu4->Append(menu_item17);
    m_menuEdit->AppendSubMenu(submenu4, wxString::FromUTF8("Borders"));

    auto menu_item18 = new wxMenuItem(m_menuEdit, id_Expand, wxString::FromUTF8("&Expand") + '\t' + "Alt+E",
    wxString::FromUTF8("Toggle the wxEXPAND flag"), wxITEM_CHECK);
    m_menuEdit->Append(menu_item18);
    m_menubar->Append(m_menuEdit, wxString::FromUTF8("&Edit"));

    m_menuTools = new wxMenu();

    auto menu_item19 = new wxMenuItem(m_menuTools, id_GenerateCode, wxString::FromUTF8("&Generate Base Code"),
    wxString::FromUTF8("Generates C++ Code for each top level form"), wxITEM_NORMAL);
    menu_item19->SetBitmap(wxImage(generate_xpm).Scale(16, 16));
    m_menuTools->Append(menu_item19);

    auto menu_item20 = new wxMenuItem(m_menuTools, id_GenerateDerived, wxString::FromUTF8("Create &Derived Code"),
    wxString::FromUTF8("Creates the files and classes that derive from the generated base classes"), wxITEM_NORMAL);
    m_menuTools->Append(menu_item20);

    m_menuTools->AppendSeparator();

    auto menu_item21 = new wxMenuItem(m_menuTools, id_ConvertImage, wxString::FromUTF8("&Convert Image..."),
    wxString::FromUTF8("Convert images into an XPM or PNG header file"), wxITEM_NORMAL);
    m_menuTools->Append(menu_item21);
    m_menubar->Append(m_menuTools, wxString::FromUTF8("&Tools"));

    m_menuHelp = new wxMenu();

    auto menu_help = new wxMenuItem(m_menuHelp, wxID_ABOUT, wxEmptyString);
    menu_help->SetBitmap(wxArtProvider::GetBitmap(wxART_HELP, wxART_MENU));
    m_menuHelp->Append(menu_help);
    m_menubar->Append(m_menuHelp, wxString::FromUTF8("&Help"));

	SetMenuBar(m_menubar);

    m_toolbar = CreateToolBar(wxTB_FLAT|wxTB_HORIZONTAL);

    m_toolbar->AddTool(id_NewProject, wxString::FromUTF8("New"), wxArtProvider::GetBitmap(wxART_NEW, wxART_TOOLBAR),
    wxString::FromUTF8("New Project (Ctrl+N)"));

    m_toolbar->AddTool(id_OpenProject, wxString::FromUTF8("Open"), wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR),
    wxString::FromUTF8("Open Project (Ctrl+O)"));

    m_toolbar->AddTool(wxID_SAVE, wxString::FromUTF8("Save"), wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR),
    wxString::FromUTF8("Save current project"));

    m_toolbar->AddTool(id_GenerateCode, wxEmptyString, wxImage(generate_xpm),
    wxString::FromUTF8("Generate base class code"));

    m_toolbar->AddSeparator();

    m_toolbar->AddTool(wxID_UNDO, wxEmptyString, wxArtProvider::GetBitmap(wxART_UNDO, wxART_TOOLBAR),
    wxString::FromUTF8("Undo"));

    m_toolbar->AddTool(wxID_REDO, wxEmptyString, wxArtProvider::GetBitmap(wxART_REDO, wxART_TOOLBAR),
    wxString::FromUTF8("Redo"));

    m_toolbar->AddSeparator();

    m_toolbar->AddTool(wxID_CUT, wxEmptyString, wxArtProvider::GetBitmap(wxART_CUT, wxART_TOOLBAR),
    wxString::FromUTF8("Cut"));

    m_toolbar->AddTool(wxID_COPY, wxEmptyString, wxArtProvider::GetBitmap(wxART_COPY, wxART_TOOLBAR),
    wxString::FromUTF8("Copy"));

    m_toolbar->AddTool(wxID_PASTE, wxEmptyString, wxArtProvider::GetBitmap(wxART_PASTE, wxART_TOOLBAR),
    wxString::FromUTF8("Paste"));

    m_toolbar->AddTool(wxID_DELETE, wxEmptyString, wxArtProvider::GetBitmap(wxART_DELETE, wxART_TOOLBAR),
    wxString::FromUTF8("Delete selected object without using clipboard."));

    m_toolbar->AddSeparator();

    m_toolbar->AddTool(id_AlignLeft, wxEmptyString, GetImgFromHdr(alignleft_png, sizeof(alignleft_png)),
    wxString::FromUTF8("Align left"), wxITEM_CHECK);

    m_toolbar->AddTool(id_AlignCenterHorizontal, wxEmptyString, GetImgFromHdr(aligncenter_png, sizeof(aligncenter_png)),
    wxString::FromUTF8("Center horizontally"), wxITEM_CHECK);

    m_toolbar->AddTool(id_AlignRight, wxEmptyString, GetImgFromHdr(alignright_png, sizeof(alignright_png)),
    wxString::FromUTF8("Align right"), wxITEM_CHECK);

    m_toolbar->AddSeparator();

    m_toolbar->AddTool(id_AlignTop, wxEmptyString, GetImgFromHdr(aligntop_png, sizeof(aligntop_png)),
    wxString::FromUTF8("Align top"), wxITEM_CHECK);

    m_toolbar->AddTool(id_AlignCenterVertical, wxEmptyString, GetImgFromHdr(alignvertcenter_png, sizeof(alignvertcenter_png)),
    wxString::FromUTF8("Center vertically"), wxITEM_CHECK);

    m_toolbar->AddTool(id_AlignBottom, wxEmptyString, GetImgFromHdr(alignbottom_png, sizeof(alignbottom_png)),
    wxString::FromUTF8("Align bottom"), wxITEM_CHECK);

    m_toolbar->AddSeparator();

    m_toolbar->AddTool(id_BorderLeft, wxEmptyString, wxImage(left_xpm),
    wxString::FromUTF8("Left border"), wxITEM_CHECK);

    m_toolbar->AddTool(id_BorderRight, wxEmptyString, wxImage(right_xpm),
    wxString::FromUTF8("Right border"), wxITEM_CHECK);

    m_toolbar->AddTool(id_BorderTop, wxEmptyString, wxImage(top_xpm),
    wxString::FromUTF8("Top border"), wxITEM_CHECK);

    m_toolbar->AddTool(id_BorderBottom, wxEmptyString, wxImage(bottom_xpm),
    wxString::FromUTF8("Bottom border"), wxITEM_CHECK);

    m_toolbar->AddSeparator();

    m_toolbar->AddTool(id_Expand, wxEmptyString, wxImage(expand_xpm),
    wxString::FromUTF8("Expand to fill the space"), wxITEM_CHECK);

    m_toolbar->AddSeparator();

    m_toolbar->AddTool(id_ShowHidden, wxEmptyString, wxImage(hidden_xpm),
    wxString::FromUTF8("Show hidden controls in Mockup panel"), wxITEM_CHECK);

    m_toolbar->AddTool(id_Magnify, wxEmptyString, wxImage(magnify_xpm),
    wxString::FromUTF8("Magnify the size of the Mockup window"), wxITEM_CHECK);

	m_toolbar->Realize();

    Centre(wxBOTH);

    // Event handlers
    Bind(wxEVT_CLOSE_WINDOW, &MainFrameBase::OnClose, this);
    Bind(wxEVT_MENU,
        [](wxCommandEvent&) { wxGetApp().NewProject(); },
        id_NewProject);
    Bind(wxEVT_MENU, &MainFrameBase::OnOpenProject, this, id_OpenProject);
    Bind(wxEVT_MENU, &MainFrameBase::OnSaveProject, this, wxID_SAVE);
    Bind(wxEVT_UPDATE_UI,
        [](wxUpdateUIEvent& event) { event.Enable(wxGetFrame().IsModified()); },
        wxID_SAVE);
    Bind(wxEVT_MENU, &MainFrameBase::OnSaveAsProject, this, id_SaveProjectAs);
    Bind(wxEVT_MENU, &MainFrameBase::OnAppendFormBuilder, this, id_AppendFormBuilder);
    Bind(wxEVT_MENU, &MainFrameBase::OnAppendGlade, this, id_AppendGlade);
    Bind(wxEVT_MENU, &MainFrameBase::OnAppendSmith, this, id_AppendSmith);
    Bind(wxEVT_MENU, &MainFrameBase::OnAppendXRC, this, id_AppendXRC);
    Bind(wxEVT_MENU, &MainFrameBase::OnOptionsDlg, this, id_OptionsDlg);
    Bind(wxEVT_MENU,
        [](wxCommandEvent&) { wxGetFrame().Undo(); },
        wxID_UNDO);
    Bind(wxEVT_UPDATE_UI,
        [](wxUpdateUIEvent& event) { event.Enable(wxGetFrame().CanUndo()); },
        wxID_UNDO);
    Bind(wxEVT_MENU,
        [](wxCommandEvent&) { wxGetFrame().Redo(); },
        wxID_REDO);
    Bind(wxEVT_UPDATE_UI,
        [](wxUpdateUIEvent& event) { event.Enable(wxGetFrame().CanRedo()); },
        wxID_REDO);
    Bind(wxEVT_MENU, &MainFrameBase::OnCut, this, wxID_CUT);
    Bind(wxEVT_UPDATE_UI,
        [](wxUpdateUIEvent& event) { event.Enable(wxGetFrame().CanCopyNode()); },
        wxID_CUT);
    Bind(wxEVT_MENU, &MainFrameBase::OnCopy, this, wxID_COPY);
    Bind(wxEVT_UPDATE_UI,
        [](wxUpdateUIEvent& event) { event.Enable(wxGetFrame().CanCopyNode()); },
        wxID_COPY);
    Bind(wxEVT_MENU, &MainFrameBase::OnPaste, this, wxID_PASTE);
    Bind(wxEVT_UPDATE_UI,
        [](wxUpdateUIEvent& event) { event.Enable(wxGetFrame().CanPasteNode()); },
        wxID_PASTE);
    Bind(wxEVT_MENU, &MainFrameBase::OnDelete, this, wxID_DELETE);
    Bind(wxEVT_UPDATE_UI,
        [](wxUpdateUIEvent& event) { event.Enable(wxGetFrame().CanCopyNode()); },
        wxID_DELETE);
    Bind(wxEVT_MENU, &MainFrameBase::OnFindDialog, this, wxID_FIND);
    Bind(wxEVT_MENU, &MainFrameBase::OnInsertWidget, this, id_insert_widget);
    Bind(wxEVT_MENU,
        [](wxCommandEvent&) { wxGetFrame().MoveNode(MoveDirection::Up); },
        id_MoveUp);
    Bind(wxEVT_MENU,
        [](wxCommandEvent&) { wxGetFrame().MoveNode(MoveDirection::Down); },
        id_MoveDown);
    Bind(wxEVT_MENU,
        [](wxCommandEvent&) { wxGetFrame().MoveNode(MoveDirection::Left); },
        id_MoveLeft);
    Bind(wxEVT_MENU,
        [](wxCommandEvent&) { wxGetFrame().MoveNode(MoveDirection::Right); },
        id_MoveRight);
    Bind(wxEVT_MENU, &MainFrameBase::OnChangeAlignment, this, id_AlignLeft);
    Bind(wxEVT_MENU, &MainFrameBase::OnChangeAlignment, this, id_AlignCenterHorizontal);
    Bind(wxEVT_MENU, &MainFrameBase::OnChangeAlignment, this, id_AlignRight);
    Bind(wxEVT_MENU, &MainFrameBase::OnChangeAlignment, this, id_AlignTop);
    Bind(wxEVT_MENU, &MainFrameBase::OnChangeAlignment, this, id_AlignCenterVertical);
    Bind(wxEVT_MENU, &MainFrameBase::OnChangeAlignment, this, id_AlignBottom);
    Bind(wxEVT_MENU, &MainFrameBase::OnChangeBorder, this, id_BorderLeft);
    Bind(wxEVT_MENU, &MainFrameBase::OnChangeBorder, this, id_BorderRight);
    Bind(wxEVT_MENU, &MainFrameBase::OnChangeBorder, this, id_BorderTop);
    Bind(wxEVT_MENU, &MainFrameBase::OnChangeBorder, this, id_BorderBottom);
    Bind(wxEVT_MENU, &MainFrameBase::OnToggleExpandLayout, this, id_Expand);
    Bind(wxEVT_MENU, &MainFrameBase::OnGenerateCode, this, id_GenerateCode);
    Bind(wxEVT_MENU, &MainFrameBase::OnGenInhertedClass, this, id_GenerateDerived);
    Bind(wxEVT_MENU, &MainFrameBase::OnEmbedImageConverter, this, id_ConvertImage);
    Bind(wxEVT_MENU, &MainFrameBase::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_TOOL, &MainFrameBase::OnGenerateCode, this, id_GenerateCode);
}
