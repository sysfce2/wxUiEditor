/////////////////////////////////////////////////////////////////////////////
// Purpose:   Main window
// Author:    Ralph Walden
// Copyright: Copyright (c) 2020 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include "mainframe.h"  // auto-generated: ui/mainframe_base.h and ui/mainframe_base.cpp

#include "commonctrls.h"
#include "other_ctrls.h"
#include "ribbondlg.h"
#include "wizard.h"

#include "ui/notebook_base.h"
#include "ui/listbook_base.h"
#include "ui/treebook_base.h"

MainFrame::MainFrame(wxWindow* parent) : MainFrameBase(parent) {}

void MainFrame::OnCommonDialog(wxCommandEvent& WXUNUSED(event))
{
    CommonCtrls dlg(this);
    dlg.ShowModal();
}

void MainFrame::OnOtherCtrls(wxCommandEvent& WXUNUSED(event))
{
    OtherCtrlsDlg dlg(this);
    dlg.ShowModal();
}

void MainFrame::OnRibbonDialog(wxCommandEvent& WXUNUSED(event))
{
    RibbonDlg dlg(this);
    dlg.ShowModal();
}

void MainFrame::OnWizard(wxCommandEvent& WXUNUSED(event))
{
    Wizard wizard(this);
    wizard.Run();
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true forces the frame to close
    Close(true);
}

void MainFrame::OnNotebook(wxCommandEvent& WXUNUSED(event))
{
    NotebookBase dlg(this);
    dlg.ShowModal();
}

void MainFrame::OnListbook(wxCommandEvent& WXUNUSED(event))
{
    ListbookBase dlg(this);
    dlg.ShowModal();
}

void MainFrame::OnTreebook(wxCommandEvent& WXUNUSED(event))
{
    TreebookBase dlg(this);
    dlg.ShowModal();
}
