/////////////////////////////////////////////////////////////////////////////
// Purpose:   Maps wxWidgets constants to their numerical value
// Author:    Ralph Walden
// Copyright: Copyright (c) 2020-2021 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
    #pragma warning(push)

    #pragma warning(disable : 4267)  // conversion from 'size_t' to 'int', possible loss of data
#endif

#include <wx/animate.h>                // wxAnimation and wxAnimationCtrl
#include <wx/anybutton.h>              // wxAnyButtonBase class
#include <wx/aui/auibar.h>             // wxaui: wx advanced user interface - docking window manager
#include <wx/aui/auibook.h>            // wxaui: wx advanced user interface - notebook
#include <wx/calctrl.h>                // date-picker control
#include <wx/checkbox.h>               // wxCheckBox class interface
#include <wx/choicebk.h>               // wxChoicebook: wxChoice and wxNotebook combination
#include <wx/clrpicker.h>              // wxColourPickerCtrl base header
#include <wx/collpane.h>               // wxCollapsiblePane
#include <wx/dataview.h>               // wxDataViewCtrl base classes
#include <wx/datectrl.h>               // implements wxDatePickerCtrl
#include <wx/defs.h>                   // Declarations/definitions common to all wx source files
#include <wx/dirctrl.h>                // Directory control base header
#include <wx/editlbox.h>               // ListBox with editable items
#include <wx/filectrl.h>               // Header for wxFileCtrlBase and other common functions used by
#include <wx/filepicker.h>             // wxFilePickerCtrl, wxDirPickerCtrl base header
#include <wx/fontpicker.h>             // wxFontPickerCtrl base header
#include <wx/frame.h>                  // wxFrame class interface
#include <wx/gauge.h>                  // wxGauge interface
#include <wx/generic/grid.h>           // wxGrid and related classes
#include <wx/html/htmlwin.h>           // wxHtmlWindow class for parsing & displaying HTML
#include <wx/htmllbox.h>               // wxHtmlListBox is a listbox whose items are wxHtmlCells
#include <wx/hyperlink.h>              // Hyperlink control
#include <wx/listbase.h>               // wxListCtrl class
#include <wx/listbook.h>               // wxListbook: wxListCtrl and wxNotebook combination
#include <wx/notebook.h>               // wxNotebook interface
#include <wx/propgrid/propgrid.h>      // wxPropertyGrid
#include <wx/ribbon/art.h>             // Art providers for ribbon-bar-style interface
#include <wx/ribbon/bar.h>             // Top-level component of the ribbon-bar-style interface
#include <wx/richtext/richtextctrl.h>  // A rich edit control
#include <wx/sizer.h>                  // provide wxSizer class for layout
#include <wx/slider.h>                 // wxSlider interface
#include <wx/splitter.h>               // Base header for wxSplitterWindow
#include <wx/stattext.h>               // wxStaticText base header
#include <wx/statusbr.h>               // wxStatusBar class interface
#include <wx/stc/stc.h>                // A wxWidgets implementation of Scintilla.  This class is the
#include <wx/textctrl.h>               // wxTextAttr and wxTextCtrlBase class - the interface of wxTextCtrl
#include <wx/timectrl.h>               // Declaration of wxTimePickerCtrl class.
#include <wx/toolbar.h>                // wxToolBar interface declaration
#include <wx/toplevel.h>               // declares wxTopLevelWindow class, the base class for all
#include <wx/treebase.h>               // wxTreeCtrl base classes and types
#include <wx/treelist.h>               // wxTreeListCtrl class declaration.
#include <wx/wizard.h>                 // wxWizard class: a GUI control presenting the user with a
#include <wx/wrapsizer.h>              // provide wrapping sizer for layout (wxWrapSizer)

#ifdef _MSC_VER
    #pragma warning(pop)
#endif

#include "node_creator.h"

// ADD_CONSTANT makes it possible to call g_NodeCreator.GetConstantAsInt(name) and have it return it's value (or zero if
// not defined)

#define ADD_CONSTANT(name) m_map_constants[#name] = name;

void NodeCreator::AddAllConstants()
{
    // Note that this isn't a complete list of constants -- it's just the values that we *think* we might need to be
    // able to switch between string and value.

    ADD_CONSTANT(wxALIGN_BOTTOM)
    ADD_CONSTANT(wxALIGN_CENTER)
    ADD_CONSTANT(wxALIGN_CENTER_HORIZONTAL)
    ADD_CONSTANT(wxALIGN_CENTER_VERTICAL)
    ADD_CONSTANT(wxALIGN_LEFT)
    ADD_CONSTANT(wxALIGN_RIGHT)
    ADD_CONSTANT(wxALIGN_TOP)

    ADD_CONSTANT(wxALL)
    ADD_CONSTANT(wxBOTTOM)
    ADD_CONSTANT(wxBOTTOM)
    ADD_CONSTANT(wxLEFT)
    ADD_CONSTANT(wxRIGHT)
    ADD_CONSTANT(wxTOP)

    ADD_CONSTANT(wxEXPAND)
    ADD_CONSTANT(wxFIXED_MINSIZE)
    ADD_CONSTANT(wxRESERVE_SPACE_EVEN_IF_HIDDEN)
    ADD_CONSTANT(wxSHAPED)

    // wxStaticText
    ADD_CONSTANT(wxST_ELLIPSIZE_END)
    ADD_CONSTANT(wxST_ELLIPSIZE_MIDDLE)
    ADD_CONSTANT(wxST_ELLIPSIZE_START)
    ADD_CONSTANT(wxST_NO_AUTORESIZE)

    // wxTextCtrl, wxSearchCtrl
    ADD_CONSTANT(wxTE_AUTO_URL)
    ADD_CONSTANT(wxTE_BESTWRAP)
    ADD_CONSTANT(wxTE_CAPITALIZE)
    ADD_CONSTANT(wxTE_CENTER)
    ADD_CONSTANT(wxTE_CHARWRAP)
    ADD_CONSTANT(wxTE_DONTWRAP)
    ADD_CONSTANT(wxTE_LEFT)
    ADD_CONSTANT(wxTE_LEFT);
    ADD_CONSTANT(wxTE_MULTILINE)
    ADD_CONSTANT(wxTE_NOHIDESEL)
    ADD_CONSTANT(wxTE_NO_VSCROLL)
    ADD_CONSTANT(wxTE_PASSWORD)
    ADD_CONSTANT(wxTE_PROCESS_ENTER)
    ADD_CONSTANT(wxTE_PROCESS_TAB)
    ADD_CONSTANT(wxTE_READONLY)
    ADD_CONSTANT(wxTE_RICH)
    ADD_CONSTANT(wxTE_RICH2)
    ADD_CONSTANT(wxTE_RIGHT)
    ADD_CONSTANT(wxTE_WORDWRAP)

    // wxRichTextCtrl
    ADD_CONSTANT(wxRE_CENTRE_CARET)
    ADD_CONSTANT(wxRE_READONLY)

    // wxAnimation
    ADD_CONSTANT(wxAC_DEFAULT_STYLE)
    ADD_CONSTANT(wxAC_NO_AUTORESIZE)

    // wxButton
    ADD_CONSTANT(wxBU_LEFT)
    ADD_CONSTANT(wxBU_TOP)
    ADD_CONSTANT(wxBU_RIGHT)
    ADD_CONSTANT(wxBU_BOTTOM)
    ADD_CONSTANT(wxBU_EXACTFIT)
    ADD_CONSTANT(wxBU_NOTEXT)

    // wxStaticLine
    ADD_CONSTANT(wxLI_HORIZONTAL)
    ADD_CONSTANT(wxLI_VERTICAL)

    // wxListBox
    ADD_CONSTANT(wxLB_SINGLE)
    ADD_CONSTANT(wxLB_MULTIPLE)
    ADD_CONSTANT(wxLB_EXTENDED)
    ADD_CONSTANT(wxLB_HSCROLL)
    ADD_CONSTANT(wxLB_ALWAYS_SB)
    ADD_CONSTANT(wxLB_NEEDED_SB)
    ADD_CONSTANT(wxLB_NO_SB)
    ADD_CONSTANT(wxLB_SORT)

    // wxEditableListBox
    ADD_CONSTANT(wxEL_ALLOW_NEW)
    ADD_CONSTANT(wxEL_ALLOW_EDIT)
    ADD_CONSTANT(wxEL_ALLOW_DELETE)
    ADD_CONSTANT(wxEL_NO_REORDER)

    // wxSimpleHtmlListBox
    ADD_CONSTANT(wxHLB_DEFAULT_STYLE)
    ADD_CONSTANT(wxHLB_MULTIPLE)

    // wxRadioBox
    ADD_CONSTANT(wxRA_SPECIFY_ROWS)
    ADD_CONSTANT(wxRA_SPECIFY_COLS)

    // wxRadioButton
    ADD_CONSTANT(wxRB_GROUP)
    ADD_CONSTANT(wxRB_SINGLE)

    // wxStatusBar
    ADD_CONSTANT(wxSTB_SIZEGRIP)
    ADD_CONSTANT(wxSTB_SHOW_TIPS)
    ADD_CONSTANT(wxSTB_ELLIPSIZE_START)
    ADD_CONSTANT(wxSTB_ELLIPSIZE_MIDDLE)
    ADD_CONSTANT(wxSTB_ELLIPSIZE_END)
    ADD_CONSTANT(wxSTB_DEFAULT_STYLE)

    // wxMenuItem & wxTool
    ADD_CONSTANT(wxITEM_NORMAL)
    ADD_CONSTANT(wxITEM_CHECK)
    ADD_CONSTANT(wxITEM_RADIO)

    // wxToolBar
    ADD_CONSTANT(wxTB_BOTTOM)
    ADD_CONSTANT(wxTB_DEFAULT_STYLE)
    ADD_CONSTANT(wxTB_DOCKABLE)
    ADD_CONSTANT(wxTB_FLAT)
    ADD_CONSTANT(wxTB_HORIZONTAL)
    ADD_CONSTANT(wxTB_HORZ_LAYOUT)
    ADD_CONSTANT(wxTB_HORZ_TEXT)
    ADD_CONSTANT(wxTB_NOALIGN)
    ADD_CONSTANT(wxTB_NODIVIDER)
    ADD_CONSTANT(wxTB_NOICONS)
    ADD_CONSTANT(wxTB_NO_TOOLTIPS)
    ADD_CONSTANT(wxTB_RIGHT)
    ADD_CONSTANT(wxTB_TEXT)
    ADD_CONSTANT(wxTB_VERTICAL)
    // wxSlider
    ADD_CONSTANT(wxSL_AUTOTICKS)
    ADD_CONSTANT(wxSL_BOTTOM)
    ADD_CONSTANT(wxSL_HORIZONTAL)
    ADD_CONSTANT(wxSL_INVERSE)
    ADD_CONSTANT(wxSL_MIN_MAX_LABELS)
    ADD_CONSTANT(wxSL_VALUE_LABEL)
    ADD_CONSTANT(wxSL_LABELS)
    ADD_CONSTANT(wxSL_LEFT)
    ADD_CONSTANT(wxSL_RIGHT)
    ADD_CONSTANT(wxSL_SELRANGE)
    ADD_CONSTANT(wxSL_TOP)
    ADD_CONSTANT(wxSL_VERTICAL)
    ADD_CONSTANT(wxSL_BOTH)

    // wxComboBox
    ADD_CONSTANT(wxCB_DROPDOWN)
    ADD_CONSTANT(wxCB_READONLY)
    ADD_CONSTANT(wxCB_SIMPLE)
    ADD_CONSTANT(wxCB_SORT)

    // wxCheckBox
    ADD_CONSTANT(wxCHK_2STATE)
    ADD_CONSTANT(wxCHK_3STATE)
    ADD_CONSTANT(wxCHK_ALLOW_3RD_STATE_FOR_USER)

    // wxGauge
    ADD_CONSTANT(wxGA_HORIZONTAL)
    ADD_CONSTANT(wxGA_SMOOTH)
    ADD_CONSTANT(wxGA_VERTICAL)
    ADD_CONSTANT(wxGA_TEXT)
    ADD_CONSTANT(wxGA_PROGRESS)

    // wxInfoBar
    ADD_CONSTANT(wxSHOW_EFFECT_NONE)
    ADD_CONSTANT(wxSHOW_EFFECT_ROLL_TO_LEFT)
    ADD_CONSTANT(wxSHOW_EFFECT_ROLL_TO_RIGHT)
    ADD_CONSTANT(wxSHOW_EFFECT_ROLL_TO_TOP)
    ADD_CONSTANT(wxSHOW_EFFECT_ROLL_TO_BOTTOM)
    ADD_CONSTANT(wxSHOW_EFFECT_SLIDE_TO_LEFT)
    ADD_CONSTANT(wxSHOW_EFFECT_SLIDE_TO_RIGHT)
    ADD_CONSTANT(wxSHOW_EFFECT_SLIDE_TO_TOP)
    ADD_CONSTANT(wxSHOW_EFFECT_SLIDE_TO_BOTTOM)
    ADD_CONSTANT(wxSHOW_EFFECT_BLEND)
    ADD_CONSTANT(wxSHOW_EFFECT_EXPAND)

    // wxColourPickerCtrl
    ADD_CONSTANT(wxCLRP_DEFAULT_STYLE)
    ADD_CONSTANT(wxCLRP_USE_TEXTCTRL)
    ADD_CONSTANT(wxCLRP_SHOW_LABEL)

    // wxFontPickerCtrl
    ADD_CONSTANT(wxFNTP_DEFAULT_STYLE)
    ADD_CONSTANT(wxFNTP_USE_TEXTCTRL)
    ADD_CONSTANT(wxFNTP_FONTDESC_AS_LABEL)
    ADD_CONSTANT(wxFNTP_USEFONT_FOR_LABEL)

    // wxFilePickerCtrl
    ADD_CONSTANT(wxFLP_DEFAULT_STYLE)
    ADD_CONSTANT(wxFLP_USE_TEXTCTRL)
    ADD_CONSTANT(wxFLP_OPEN)
    ADD_CONSTANT(wxFLP_SAVE)
    ADD_CONSTANT(wxFLP_OVERWRITE_PROMPT)
    ADD_CONSTANT(wxFLP_FILE_MUST_EXIST)
    ADD_CONSTANT(wxFLP_CHANGE_DIR)
    ADD_CONSTANT(wxFLP_SMALL)

    // wxDirPickerCtrl
    ADD_CONSTANT(wxDIRP_DEFAULT_STYLE)
    ADD_CONSTANT(wxDIRP_USE_TEXTCTRL)
    ADD_CONSTANT(wxDIRP_DIR_MUST_EXIST)
    ADD_CONSTANT(wxDIRP_CHANGE_DIR)
    ADD_CONSTANT(wxDIRP_SMALL)

    // wxHyperlinkCtrl
    ADD_CONSTANT(wxHL_ALIGN_LEFT)
    ADD_CONSTANT(wxHL_ALIGN_RIGHT)
    ADD_CONSTANT(wxHL_ALIGN_CENTRE)
    ADD_CONSTANT(wxHL_CONTEXTMENU)
    ADD_CONSTANT(wxHL_DEFAULT_STYLE)

    // wxDataViewCtrl
    ADD_CONSTANT(wxDV_SINGLE)
    ADD_CONSTANT(wxDV_MULTIPLE)
    ADD_CONSTANT(wxDV_ROW_LINES)
    ADD_CONSTANT(wxDV_HORIZ_RULES)
    ADD_CONSTANT(wxDV_VERT_RULES)
    ADD_CONSTANT(wxDV_VARIABLE_LINE_HEIGHT)
    ADD_CONSTANT(wxDV_NO_HEADER)
    ADD_CONSTANT(wxDATAVIEW_CELL_INERT)
    ADD_CONSTANT(wxDATAVIEW_CELL_ACTIVATABLE)
    ADD_CONSTANT(wxDATAVIEW_CELL_EDITABLE)
    ADD_CONSTANT(wxDATAVIEW_COL_RESIZABLE)
    ADD_CONSTANT(wxDATAVIEW_COL_SORTABLE)
    ADD_CONSTANT(wxDATAVIEW_COL_REORDERABLE)
    ADD_CONSTANT(wxDATAVIEW_COL_HIDDEN)

    ADD_CONSTANT(wxELLIPSIZE_NONE)
    ADD_CONSTANT(wxELLIPSIZE_START)
    ADD_CONSTANT(wxELLIPSIZE_MIDDLE)
    ADD_CONSTANT(wxELLIPSIZE_END)

    // wxRibbonBar
    ADD_CONSTANT(wxRIBBON_BAR_DEFAULT_STYLE)
    ADD_CONSTANT(wxRIBBON_BAR_FOLDBAR_STYLE)
    ADD_CONSTANT(wxRIBBON_BAR_SHOW_PAGE_LABELS)
    ADD_CONSTANT(wxRIBBON_BAR_SHOW_PAGE_ICONS)
    ADD_CONSTANT(wxRIBBON_BAR_FLOW_HORIZONTAL)
    ADD_CONSTANT(wxRIBBON_BAR_FLOW_VERTICAL)
    ADD_CONSTANT(wxRIBBON_BAR_SHOW_PANEL_EXT_BUTTONS)
    ADD_CONSTANT(wxRIBBON_BAR_SHOW_PANEL_MINIMISE_BUTTONS)
    ADD_CONSTANT(wxRIBBON_BAR_SHOW_TOGGLE_BUTTON)
    ADD_CONSTANT(wxRIBBON_BAR_SHOW_HELP_BUTTON)

    // wxRibbonPanel
    ADD_CONSTANT(wxRIBBON_PANEL_DEFAULT_STYLE)
    ADD_CONSTANT(wxRIBBON_PANEL_NO_AUTO_MINIMISE)
    ADD_CONSTANT(wxRIBBON_PANEL_EXT_BUTTON)
    ADD_CONSTANT(wxRIBBON_PANEL_MINIMISE_BUTTON)
    ADD_CONSTANT(wxRIBBON_PANEL_STRETCH)
    ADD_CONSTANT(wxRIBBON_PANEL_FLEXIBLE)

    // wxCalendarCtrl
    ADD_CONSTANT(wxCAL_SUNDAY_FIRST)
    ADD_CONSTANT(wxCAL_MONDAY_FIRST)
    ADD_CONSTANT(wxCAL_SHOW_HOLIDAYS)
    ADD_CONSTANT(wxCAL_NO_YEAR_CHANGE)
    ADD_CONSTANT(wxCAL_NO_MONTH_CHANGE)
    ADD_CONSTANT(wxCAL_SHOW_SURROUNDING_WEEKS)
    ADD_CONSTANT(wxCAL_SEQUENTIAL_MONTH_SELECTION)
    ADD_CONSTANT(wxCAL_SHOW_WEEK_NUMBERS)

    // wxDatePickerCtrl
    ADD_CONSTANT(wxDP_SPIN)
    ADD_CONSTANT(wxDP_DROPDOWN)
    ADD_CONSTANT(wxDP_SHOWCENTURY)
    ADD_CONSTANT(wxDP_ALLOWNONE)
    ADD_CONSTANT(wxDP_DEFAULT)

    // wxTimePickerCtrl
    ADD_CONSTANT(wxTP_DEFAULT)

    // wxHtmlWindow
    ADD_CONSTANT(wxHW_SCROLLBAR_NEVER)
    ADD_CONSTANT(wxHW_SCROLLBAR_AUTO)
    ADD_CONSTANT(wxHW_NO_SELECTION)

    // wxTreeCtrl
    ADD_CONSTANT(wxTR_EDIT_LABELS)
    ADD_CONSTANT(wxTR_NO_BUTTONS)
    ADD_CONSTANT(wxTR_HAS_BUTTONS)
    ADD_CONSTANT(wxTR_TWIST_BUTTONS)
    ADD_CONSTANT(wxTR_NO_LINES)
    ADD_CONSTANT(wxTR_FULL_ROW_HIGHLIGHT)
    ADD_CONSTANT(wxTR_LINES_AT_ROOT)
    ADD_CONSTANT(wxTR_HIDE_ROOT)
    ADD_CONSTANT(wxTR_ROW_LINES)
    ADD_CONSTANT(wxTR_HAS_VARIABLE_ROW_HEIGHT)
    ADD_CONSTANT(wxTR_SINGLE)
    ADD_CONSTANT(wxTR_MULTIPLE)
    ADD_CONSTANT(wxTR_DEFAULT_STYLE)

    // wxListView
    ADD_CONSTANT(wxLC_LIST)
    ADD_CONSTANT(wxLC_REPORT)
    ADD_CONSTANT(wxLC_VIRTUAL)
    ADD_CONSTANT(wxLC_ICON)
    ADD_CONSTANT(wxLC_SMALL_ICON)
    ADD_CONSTANT(wxLC_ALIGN_TOP)
    ADD_CONSTANT(wxLC_ALIGN_LEFT)
    ADD_CONSTANT(wxLC_AUTOARRANGE)
    ADD_CONSTANT(wxLC_EDIT_LABELS)
    ADD_CONSTANT(wxLC_NO_SORT_HEADER)
    ADD_CONSTANT(wxLC_NO_HEADER)
    ADD_CONSTANT(wxLC_SINGLE_SEL)
    ADD_CONSTANT(wxLC_SORT_ASCENDING)
    ADD_CONSTANT(wxLC_SORT_DESCENDING)
    ADD_CONSTANT(wxLC_HRULES)
    ADD_CONSTANT(wxLC_VRULES)

    // wxScrollBar
    ADD_CONSTANT(wxSB_HORIZONTAL)
    ADD_CONSTANT(wxSB_VERTICAL)

    // wxSpinCtrl and wxSpinButton
    ADD_CONSTANT(wxSP_ARROW_KEYS)
    ADD_CONSTANT(wxSP_WRAP)
    ADD_CONSTANT(wxSP_HORIZONTAL)
    ADD_CONSTANT(wxSP_VERTICAL)

    // wxFileCtrl
    ADD_CONSTANT(wxFC_OPEN)
    ADD_CONSTANT(wxFC_SAVE)
    ADD_CONSTANT(wxFC_MULTIPLE)
    ADD_CONSTANT(wxFC_NOSHOWHIDDEN)

    // wxGenericDirCtrl
    ADD_CONSTANT(wxDIRCTRL_DIR_ONLY)
    ADD_CONSTANT(wxDIRCTRL_3D_INTERNAL)
    ADD_CONSTANT(wxDIRCTRL_SELECT_FIRST)
    ADD_CONSTANT(wxDIRCTRL_EDIT_LABELS)
    ADD_CONSTANT(wxDIRCTRL_MULTIPLE)

    // wxPropertyGrid
    ADD_CONSTANT(wxPGMAN_DEFAULT_STYLE)
    ADD_CONSTANT(wxPG_ALPHABETIC_MODE)
    ADD_CONSTANT(wxPG_AUTO_SORT)
    ADD_CONSTANT(wxPG_BOLD_MODIFIED)
    ADD_CONSTANT(wxPG_DEFAULT_STYLE)
    ADD_CONSTANT(wxPG_DESCRIPTION)
    ADD_CONSTANT(wxPG_EX_AUTO_UNSPECIFIED_VALUES)
    ADD_CONSTANT(wxPG_EX_ENABLE_TLP_TRACKING)
    ADD_CONSTANT(wxPG_EX_HELP_AS_TOOLTIPS)
    ADD_CONSTANT(wxPG_EX_HIDE_PAGE_BUTTONS)
    ADD_CONSTANT(wxPG_EX_INIT_NOCAT)
    ADD_CONSTANT(wxPG_EX_MODE_BUTTONS)
    ADD_CONSTANT(wxPG_EX_MULTIPLE_SELECTION)
    ADD_CONSTANT(wxPG_EX_NATIVE_DOUBLE_BUFFERING)
    ADD_CONSTANT(wxPG_EX_NO_FLAT_TOOLBAR)
    ADD_CONSTANT(wxPG_EX_NO_TOOLBAR_DIVIDER)
    ADD_CONSTANT(wxPG_EX_TOOLBAR_SEPARATOR)
    ADD_CONSTANT(wxPG_EX_WRITEONLY_BUILTIN_ATTRIBUTES)
    ADD_CONSTANT(wxPG_HIDE_CATEGORIES)
    ADD_CONSTANT(wxPG_HIDE_MARGIN)
    ADD_CONSTANT(wxPG_LIMITED_EDITING)
    ADD_CONSTANT(wxPG_NO_INTERNAL_BORDER)
    ADD_CONSTANT(wxPG_SPLITTER_AUTO_CENTER)
    ADD_CONSTANT(wxPG_STATIC_LAYOUT)
    ADD_CONSTANT(wxPG_STATIC_SPLITTER)
    ADD_CONSTANT(wxPG_TOOLBAR)
    ADD_CONSTANT(wxPG_TOOLTIPS)

    // wxTreeListCtrl
    ADD_CONSTANT(wxTL_SINGLE)
    ADD_CONSTANT(wxTL_MULTIPLE)
    ADD_CONSTANT(wxTL_CHECKBOX)
    ADD_CONSTANT(wxTL_3STATE)
    ADD_CONSTANT(wxTL_USER_3STATE)
    ADD_CONSTANT(wxTR_DEFAULT_STYLE)
    ADD_CONSTANT(wxCOL_RESIZABLE)
    ADD_CONSTANT(wxCOL_SORTABLE)
    ADD_CONSTANT(wxCOL_REORDERABLE)
    ADD_CONSTANT(wxCOL_HIDDEN)

    // wxCollapsiblePane
    ADD_CONSTANT(wxCP_DEFAULT_STYLE)
    ADD_CONSTANT(wxCP_NO_TLW_RESIZE)

    // wxSplitterWindow
    ADD_CONSTANT(wxSP_3D)
    ADD_CONSTANT(wxSP_3DSASH)
    ADD_CONSTANT(wxSP_3DBORDER)
    ADD_CONSTANT(wxSP_BORDER)
    ADD_CONSTANT(wxSP_NOBORDER)
    ADD_CONSTANT(wxSP_NOSASH)
    ADD_CONSTANT(wxSP_THIN_SASH)
    ADD_CONSTANT(wxSP_NO_XP_THEME)
    ADD_CONSTANT(wxSP_PERMIT_UNSPLIT)
    ADD_CONSTANT(wxSP_LIVE_UPDATE)

    ADD_CONSTANT(wxSPLIT_VERTICAL)
    ADD_CONSTANT(wxSPLIT_HORIZONTAL)

    // wxScrolledWindow
    ADD_CONSTANT(wxHSCROLL);
    ADD_CONSTANT(wxVSCROLL);

    // Books
    ADD_CONSTANT(wxBK_DEFAULT)
    ADD_CONSTANT(wxBK_TOP)
    ADD_CONSTANT(wxBK_BOTTOM)
    ADD_CONSTANT(wxBK_LEFT)
    ADD_CONSTANT(wxBK_RIGHT)

    // wxNotebook
    ADD_CONSTANT(wxNB_TOP)
    ADD_CONSTANT(wxNB_LEFT)
    ADD_CONSTANT(wxNB_RIGHT)
    ADD_CONSTANT(wxNB_BOTTOM)
    ADD_CONSTANT(wxNB_FIXEDWIDTH)
    ADD_CONSTANT(wxNB_MULTILINE)
    ADD_CONSTANT(wxNB_NOPAGETHEME)

    // wxListbook
    ADD_CONSTANT(wxLB_TOP)
    ADD_CONSTANT(wxLB_LEFT)
    ADD_CONSTANT(wxLB_RIGHT)
    ADD_CONSTANT(wxLB_BOTTOM)
    ADD_CONSTANT(wxLB_DEFAULT)

    // wxChoicebook
    ADD_CONSTANT(wxCHB_TOP)
    ADD_CONSTANT(wxCHB_LEFT)
    ADD_CONSTANT(wxCHB_RIGHT)
    ADD_CONSTANT(wxCHB_BOTTOM)
    ADD_CONSTANT(wxCHB_DEFAULT)

    // wxAuiNotebook
    ADD_CONSTANT(wxAUI_NB_DEFAULT_STYLE)
    ADD_CONSTANT(wxAUI_NB_TAB_SPLIT)
    ADD_CONSTANT(wxAUI_NB_TAB_MOVE)
    ADD_CONSTANT(wxAUI_NB_TAB_EXTERNAL_MOVE)
    ADD_CONSTANT(wxAUI_NB_TAB_FIXED_WIDTH)
    ADD_CONSTANT(wxAUI_NB_SCROLL_BUTTONS)
    ADD_CONSTANT(wxAUI_NB_WINDOWLIST_BUTTON)
    ADD_CONSTANT(wxAUI_NB_CLOSE_BUTTON)
    ADD_CONSTANT(wxAUI_NB_CLOSE_ON_ACTIVE_TAB)
    ADD_CONSTANT(wxAUI_NB_CLOSE_ON_ALL_TABS)
    ADD_CONSTANT(wxAUI_NB_MIDDLE_CLICK_CLOSE)
    ADD_CONSTANT(wxAUI_NB_TOP)
    ADD_CONSTANT(wxAUI_NB_BOTTOM)

    // wxFrame style macros
    ADD_CONSTANT(wxDEFAULT_FRAME_STYLE)
    ADD_CONSTANT(wxICONIZE)
    ADD_CONSTANT(wxCAPTION)
    ADD_CONSTANT(wxMINIMIZE)
    ADD_CONSTANT(wxMINIMIZE_BOX)
    ADD_CONSTANT(wxMAXIMIZE)
    ADD_CONSTANT(wxMAXIMIZE_BOX)
    ADD_CONSTANT(wxCLOSE_BOX)
    ADD_CONSTANT(wxSTAY_ON_TOP)
    ADD_CONSTANT(wxSYSTEM_MENU)
    ADD_CONSTANT(wxRESIZE_BORDER)
    ADD_CONSTANT(wxFRAME_TOOL_WINDOW)
    ADD_CONSTANT(wxFRAME_NO_TASKBAR)
    ADD_CONSTANT(wxFRAME_FLOAT_ON_PARENT)
    ADD_CONSTANT(wxFRAME_SHAPED)
    ADD_CONSTANT(wxFRAME_EX_CONTEXTHELP)
    ADD_CONSTANT(wxFRAME_EX_METAL)

    // wxDialog style ADD_MACROs
    ADD_CONSTANT(wxCAPTION)
    ADD_CONSTANT(wxDEFAULT_DIALOG_STYLE)
    ADD_CONSTANT(wxRESIZE_BORDER)
    ADD_CONSTANT(wxSYSTEM_MENU)
    ADD_CONSTANT(wxCLOSE_BOX)
    ADD_CONSTANT(wxMAXIMIZE_BOX)
    ADD_CONSTANT(wxMINIMIZE_BOX)
    ADD_CONSTANT(wxSTAY_ON_TOP)
    ADD_CONSTANT(wxDIALOG_NO_PARENT)

    // wxDialog
    ADD_CONSTANT(wxBOTH)

    // wxMenuBar
    ADD_CONSTANT(wxMB_DOCKABLE)

    // wxWindow style macros
    ADD_CONSTANT(wxBORDER_DEFAULT)
    ADD_CONSTANT(wxBORDER_SIMPLE)
    ADD_CONSTANT(wxBORDER_DOUBLE)
    ADD_CONSTANT(wxBORDER_SUNKEN)
    ADD_CONSTANT(wxBORDER_RAISED)
    ADD_CONSTANT(wxBORDER_STATIC)
    ADD_CONSTANT(wxBORDER_THEME)
    ADD_CONSTANT(wxBORDER_NONE)
    ADD_CONSTANT(wxTRANSPARENT_WINDOW)
    ADD_CONSTANT(wxTAB_TRAVERSAL)
    ADD_CONSTANT(wxWANTS_CHARS)
    ADD_CONSTANT(wxVSCROLL)
    ADD_CONSTANT(wxHSCROLL)
    ADD_CONSTANT(wxALWAYS_SHOW_SB)
    ADD_CONSTANT(wxCLIP_CHILDREN)
    ADD_CONSTANT(wxFULL_REPAINT_ON_RESIZE)
    ADD_CONSTANT(wxNO_FULL_REPAINT_ON_RESIZE)
    ADD_CONSTANT(wxWS_EX_VALIDATE_RECURSIVELY)
    ADD_CONSTANT(wxWS_EX_BLOCK_EVENTS)
    ADD_CONSTANT(wxWS_EX_TRANSIENT)
    ADD_CONSTANT(wxWS_EX_CONTEXTHELP)
    ADD_CONSTANT(wxWS_EX_PROCESS_IDLE)
    ADD_CONSTANT(wxWS_EX_PROCESS_UI_UPDATES)

    // wxAuiManager
    ADD_CONSTANT(wxAUI_MGR_ALLOW_FLOATING)
    ADD_CONSTANT(wxAUI_MGR_ALLOW_ACTIVE_PANE)
    ADD_CONSTANT(wxAUI_MGR_TRANSPARENT_DRAG)
    ADD_CONSTANT(wxAUI_MGR_TRANSPARENT_HINT)
    ADD_CONSTANT(wxAUI_MGR_VENETIAN_BLINDS_HINT)
    ADD_CONSTANT(wxAUI_MGR_RECTANGLE_HINT)
    ADD_CONSTANT(wxAUI_MGR_HINT_FADE)
    ADD_CONSTANT(wxAUI_MGR_NO_VENETIAN_BLINDS_FADE)
    ADD_CONSTANT(wxAUI_MGR_LIVE_RESIZE)
    ADD_CONSTANT(wxAUI_MGR_DEFAULT)

    // wxAuiToolBar
    ADD_CONSTANT(wxAUI_TB_TEXT)
    ADD_CONSTANT(wxAUI_TB_NO_TOOLTIPS)
    ADD_CONSTANT(wxAUI_TB_NO_AUTORESIZE)
    ADD_CONSTANT(wxAUI_TB_GRIPPER)
    ADD_CONSTANT(wxAUI_TB_OVERFLOW)
    ADD_CONSTANT(wxAUI_TB_VERTICAL)
    ADD_CONSTANT(wxAUI_TB_HORZ_LAYOUT)
    ADD_CONSTANT(wxAUI_TB_HORIZONTAL)
    ADD_CONSTANT(wxAUI_TB_PLAIN_BACKGROUND)
    ADD_CONSTANT(wxAUI_TB_HORZ_TEXT)
    ADD_CONSTANT(wxAUI_TB_DEFAULT_STYLE)

    // wxBoxSizer
    ADD_CONSTANT(wxHORIZONTAL)
    ADD_CONSTANT(wxVERTICAL)

    // wxWrapSizer
    ADD_CONSTANT(wxEXTEND_LAST_ON_EACH_LINE)
    ADD_CONSTANT(wxREMOVE_LEADING_SPACES)
    ADD_CONSTANT(wxWRAPSIZER_DEFAULT_FLAGS)

    // wxFlexGridSizer
    ADD_CONSTANT(wxFLEX_GROWMODE_NONE)
    ADD_CONSTANT(wxFLEX_GROWMODE_SPECIFIED)
    ADD_CONSTANT(wxFLEX_GROWMODE_ALL)

    // wxWizard
    ADD_CONSTANT(wxWIZARD_EX_HELPBUTTON)
    m_map_constants["wxWIZARD_DEFAULT_PLACEMENT"] = 0;  // wxWidgets doesn't actually have this value
    ADD_CONSTANT(wxWIZARD_VALIGN_TOP)
    ADD_CONSTANT(wxWIZARD_VALIGN_CENTRE)
    ADD_CONSTANT(wxWIZARD_VALIGN_BOTTOM)
    ADD_CONSTANT(wxWIZARD_HALIGN_LEFT)
    ADD_CONSTANT(wxWIZARD_HALIGN_CENTRE)
    ADD_CONSTANT(wxWIZARD_HALIGN_RIGHT)
    ADD_CONSTANT(wxWIZARD_TILE)

    // wxStyledText (Scintilla)

    ADD_CONSTANT(wxSTC_WRAP_NONE)
    ADD_CONSTANT(wxSTC_WRAP_WORD)
    ADD_CONSTANT(wxSTC_WRAP_CHAR)
    ADD_CONSTANT(wxSTC_WRAP_WHITESPACE)
    ADD_CONSTANT(wxSTC_WRAPVISUALFLAG_END)
    ADD_CONSTANT(wxSTC_WRAPVISUALFLAG_START)
    ADD_CONSTANT(wxSTC_WRAPVISUALFLAG_MARGIN)
    ADD_CONSTANT(wxSTC_WRAPVISUALFLAGLOC_END_BY_TEXT)
    ADD_CONSTANT(wxSTC_WRAPVISUALFLAGLOC_START_BY_TEXT)
    ADD_CONSTANT(wxSTC_WRAPINDENT_FIXED)
    ADD_CONSTANT(wxSTC_WRAPINDENT_SAME)
    ADD_CONSTANT(wxSTC_WRAPINDENT_INDENT)

    ADD_CONSTANT(wxSTC_MARGIN_SYMBOL)
    ADD_CONSTANT(wxSTC_MARGIN_NUMBER)
    ADD_CONSTANT(wxSTC_MARGIN_BACK)
    ADD_CONSTANT(wxSTC_MARGIN_FORE)
    ADD_CONSTANT(wxSTC_MARGIN_TEXT)
    ADD_CONSTANT(wxSTC_MARGIN_RTEXT)
    ADD_CONSTANT(wxSTC_MARGIN_COLOUR)

    ADD_CONSTANT(wxSTC_IV_NONE)
    ADD_CONSTANT(wxSTC_IV_REAL)
    ADD_CONSTANT(wxSTC_IV_LOOKFORWARD)
    ADD_CONSTANT(wxSTC_IV_LOOKBOTH)

    // Ribbon macros
    ADD_CONSTANT(wxRIBBON_BUTTON_NORMAL)
    ADD_CONSTANT(wxRIBBON_BUTTON_DROPDOWN)
    ADD_CONSTANT(wxRIBBON_BUTTON_HYBRID)
    ADD_CONSTANT(wxRIBBON_BUTTON_TOGGLE)

    // The following stock ids are taken from wxWidgets/src/common/stockitem.cpp

    ADD_CONSTANT(wxID_ABOUT)
    ADD_CONSTANT(wxID_ADD)
    ADD_CONSTANT(wxID_APPLY)
    ADD_CONSTANT(wxID_BACKWARD)
    ADD_CONSTANT(wxID_BOLD)
    ADD_CONSTANT(wxID_BOTTOM)
    ADD_CONSTANT(wxID_CANCEL)
    ADD_CONSTANT(wxID_CDROM)
    ADD_CONSTANT(wxID_CLEAR)
    ADD_CONSTANT(wxID_CLOSE)
    ADD_CONSTANT(wxID_CONVERT)
    ADD_CONSTANT(wxID_COPY)
    ADD_CONSTANT(wxID_CUT)
    ADD_CONSTANT(wxID_DELETE)
    ADD_CONSTANT(wxID_DOWN)
    ADD_CONSTANT(wxID_EDIT)
    ADD_CONSTANT(wxID_EXECUTE)
    ADD_CONSTANT(wxID_EXIT)
    ADD_CONSTANT(wxID_FILE)
    ADD_CONSTANT(wxID_FIND)
    ADD_CONSTANT(wxID_FIRST)
    ADD_CONSTANT(wxID_FLOPPY)
    ADD_CONSTANT(wxID_FORWARD)
    ADD_CONSTANT(wxID_HARDDISK)
    ADD_CONSTANT(wxID_HELP)
    ADD_CONSTANT(wxID_HOME)
    ADD_CONSTANT(wxID_INDENT)
    ADD_CONSTANT(wxID_INDEX)
    ADD_CONSTANT(wxID_INFO)
    ADD_CONSTANT(wxID_ITALIC)
    ADD_CONSTANT(wxID_JUMP_TO)
    ADD_CONSTANT(wxID_JUSTIFY_CENTER)
    ADD_CONSTANT(wxID_JUSTIFY_FILL)
    ADD_CONSTANT(wxID_JUSTIFY_LEFT)
    ADD_CONSTANT(wxID_JUSTIFY_RIGHT)
    ADD_CONSTANT(wxID_LAST)
    ADD_CONSTANT(wxID_NETWORK)
    ADD_CONSTANT(wxID_NEW)
    ADD_CONSTANT(wxID_NO)
    ADD_CONSTANT(wxID_OK)
    ADD_CONSTANT(wxID_OPEN)
    ADD_CONSTANT(wxID_PASTE)
    ADD_CONSTANT(wxID_PREFERENCES)
    ADD_CONSTANT(wxID_PREVIEW)
    ADD_CONSTANT(wxID_PRINT)
    ADD_CONSTANT(wxID_PROPERTIES)
    ADD_CONSTANT(wxID_REDO)
    ADD_CONSTANT(wxID_REFRESH)
    ADD_CONSTANT(wxID_REMOVE)
    ADD_CONSTANT(wxID_REPLACE)
    ADD_CONSTANT(wxID_REVERT_TO_SAVED)
    ADD_CONSTANT(wxID_SAVE)
    ADD_CONSTANT(wxID_SAVEAS)
    ADD_CONSTANT(wxID_SELECTALL)
    ADD_CONSTANT(wxID_SELECT_COLOR)
    ADD_CONSTANT(wxID_SELECT_FONT)
    ADD_CONSTANT(wxID_SORT_ASCENDING)
    ADD_CONSTANT(wxID_SORT_DESCENDING)
    ADD_CONSTANT(wxID_SPELL_CHECK)
    ADD_CONSTANT(wxID_STOP)
    ADD_CONSTANT(wxID_STRIKETHROUGH)
    ADD_CONSTANT(wxID_TOP)
    ADD_CONSTANT(wxID_UNDELETE)
    ADD_CONSTANT(wxID_UNDERLINE)
    ADD_CONSTANT(wxID_UNDO)
    ADD_CONSTANT(wxID_UNINDENT)
    ADD_CONSTANT(wxID_UP)
    ADD_CONSTANT(wxID_YES)
    ADD_CONSTANT(wxID_ZOOM_100)
    ADD_CONSTANT(wxID_ZOOM_FIT)
    ADD_CONSTANT(wxID_ZOOM_IN)
    ADD_CONSTANT(wxID_ZOOM_OUT)

    // wxGrid

    m_map_constants["wxGridSelectCells"] = wxGrid::wxGridSelectCells;
    m_map_constants["wxGridSelectRows"] = wxGrid::wxGridSelectRows;
    m_map_constants["wxGridSelectColumns"] = wxGrid::wxGridSelectColumns;
    m_map_constants["wxGridSelectRowsOrColumns"] = wxGrid::wxGridSelectRowsOrColumns;
    m_map_constants["wxGridSelectNone"] = wxGrid::wxGridSelectNone;

    m_map_constants["Tab_Stop"] = wxGrid::Tab_Stop;
    m_map_constants["Tab_Wrap"] = wxGrid::Tab_Wrap;
    m_map_constants["Tab_Leave"] = wxGrid::Tab_Leave;
}
