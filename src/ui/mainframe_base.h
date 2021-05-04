////////////////////////////////////////////////////////////////////////////////
// Code generated by wxUiEditor -- see https://github.com/KeyWorksRW/wxUiEditor/
//
// DO NOT EDIT THIS FILE! Your changes will be lost if it is re-generated!
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/event.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/menu.h>
#include <wx/toolbar.h>

class MainFrameBase : public wxFrame
{
public:
    MainFrameBase(wxWindow* parent, wxWindowID id = wxID_ANY,
        const wxString& title = wxEmptyString,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1000, 1000),
        long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);

    enum
    {
        id_AlignBottom = wxID_HIGHEST + 1,
        id_AlignCenterHorizontal,
        id_AlignCenterVertical,
        id_AlignLeft,
        id_AlignRight,
        id_AlignTop,
        id_AppendFormBuilder,
        id_AppendGlade,
        id_AppendSmith,
        id_AppendXRC,
        id_BorderBottom,
        id_BorderLeft,
        id_BorderRight,
        id_BorderTop,
        id_ConvertImage,
        id_Expand,
        id_GenerateCode,
        id_GenerateDerived,
        id_Magnify,
        id_MoveDown,
        id_MoveLeft,
        id_MoveRight,
        id_MoveUp,
        id_NewProject,
        id_OpenProject,
        id_OptionsDlg,
        id_SaveProjectAs,
        id_ShowHidden,
        id_insert_widget
    };

protected:

    // Class member variables

    wxMenu* m_menuEdit;
    wxMenu* m_menuFile;
    wxMenu* m_menuHelp;
    wxMenu* m_menuTools;
    wxMenu* m_submenu_recent;
    wxMenuBar* m_menubar;
    wxToolBar* m_toolbar;

    // Virtual event handlers -- override them in your derived class

    virtual void OnAbout(wxCommandEvent& event) { event.Skip(); }
    virtual void OnAppendFormBuilder(wxCommandEvent& event) { event.Skip(); }
    virtual void OnAppendGlade(wxCommandEvent& event) { event.Skip(); }
    virtual void OnAppendSmith(wxCommandEvent& event) { event.Skip(); }
    virtual void OnAppendXRC(wxCommandEvent& event) { event.Skip(); }
    virtual void OnChangeAlignment(wxCommandEvent& event) { event.Skip(); }
    virtual void OnChangeBorder(wxCommandEvent& event) { event.Skip(); }
    virtual void OnClose(wxCloseEvent& event) { event.Skip(); }
    virtual void OnCopy(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCut(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDelete(wxCommandEvent& event) { event.Skip(); }
    virtual void OnEmbedImageConverter(wxCommandEvent& event) { event.Skip(); }
    virtual void OnFindDialog(wxCommandEvent& event) { event.Skip(); }
    virtual void OnGenInhertedClass(wxCommandEvent& event) { event.Skip(); }
    virtual void OnGenerateCode(wxCommandEvent& event) { event.Skip(); }
    virtual void OnInsertWidget(wxCommandEvent& event) { event.Skip(); }
    virtual void OnOpenProject(wxCommandEvent& event) { event.Skip(); }
    virtual void OnOptionsDlg(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPaste(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSaveAsProject(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSaveProject(wxCommandEvent& event) { event.Skip(); }
    virtual void OnToggleExpandLayout(wxCommandEvent& event) { event.Skip(); }
};
