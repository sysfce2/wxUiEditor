###############################################################################
# Code generated by wxUiEditor -- see https://github.com/KeyWorksRW/wxUiEditor/
#
# Do not edit any code above the "End of generated code" comment block.
# Any changes before that block will be lost if it is re-generated!
###############################################################################

"""MainFrame class generated by wxUiEditor."""

import wx
import wx.grid
import wx.propgrid
import main_test_dlg
import booktest_dlg
import wizard
import python_dlg
import tools_dlg
import dlgissue_956
import dlgissue_960

import images
from wx.lib.embeddedimage import PyEmbeddedImage

wxToolBar_png = PyEmbeddedImage(
    b"iVBORw0KGgoAAAANSUhEUgAAABYAAAAWCAYAAADEtGw7AAAACXBIWXMAAAsTAAALEwEAmpwYAAAB3ElE"
    b"QVQ4y+2UMWgTURjHf69pcnI2BYPeIukiGoQGBIcMthDCG8RBp7aDkw4VS6AdnJ0llHSQDgWXCiGgi2AT"
    b"LJih5yAHtqU26ZacOlgK0iKXco1HeQ5pGo9r3TIU+t/ee9/7f///933vwTmOIHK5nOoJcbVa7QlxX69K"
    b"0Q8gZYpo1GBp6QMASimEEAB4nue7MDIyTCgUIZN5ECCzLAshBKVSif7p6cdsb8/gODdJp+8Ch8AecAnb"
    b"/sH6+jeazebx5aEh0LSLvL7zPUB866vG/r7TUdwALhCNfmJ1dQZoAXXgGuPjc6cYVYTGFjh8+8S3Ozj4"
    b"C03baxMLcQXwgOs0Gj+pVD4Dt4H32PZVisUiuq6jlEJK2ek5AKGxBX++QqZbY6VagODgoEk+b1OrmYAJ"
    b"wMAALC9/AWBjA6SsohSMTpk8f1kI+BidMvk4l+yUogX0MTu7g+O8IZ0OGq/XIZV62tbaFsufxMP/T4UQ"
    b"l1lc9NjaKpBIBAN2dyEcvs/k5DNc10UdTX3+UfI4Jh6Pk81m2THudYktq4GuvyKZ/H1i5s3NG8zPv8B1"
    b"XZ/if2EYho+00wWlaRCJnGzJNNcIh/2HExPD1GrddSwWQ0pJpfKOlZW1s/qky+Xy+R9/RvEX3wKaS6uF"
    b"TSQAAAAASUVORK5CYII=")

wxWizard_png = PyEmbeddedImage(
    b"iVBORw0KGgoAAAANSUhEUgAAABYAAAAWCAYAAADEtGw7AAAACXBIWXMAAAsTAAALEwEAmpwYAAADyUlE"
    b"QVQ4y9WVTWhcVRTHf+8jM+8lqXmTqJ0nVoy6meAmARW6DIISLaLd1EaKCIJQi9WmiG03UkEEN0oHRFo/"
    b"aRei1YXUBmXsxpQWO5FojaBt2qSkTa2Z5mMyk5l3z3Hx3kwdtHXlwguHx3v3vt8595x7/hf+b8M68cvv"
    b"evTUFbq6A1ZqigCoggIqqGqLAagk30nWiCKqtNmKLXUevi/EPfrDPH6nDyh+W9MfAJuyJ5kaK3Lirq0k"
    b"yGsh6T+FCVKv8/l3M7hqu5RXhXJtFSsBNkZwcA/ZgZCF8rM32HPrq0SGurFwjShBu02n5zQnt4w+RHVg"
    b"K956j8zFIi9kvqTEYb659cN/yaxSqwkzS+B6Dgzc2cG963yMxNNXR/vJ8hrV9X14ZOCz58lk9rGhv+uG"
    b"WNexWFyp88XSMq4FtKcsejod5n78iuDgHqo5qA724QVvAgXIeVSn8gSv5xnvfQKvd4COu3MtUC/tsaan"
    b"G9IWrgMuqogKK5Ualck8ARAwRZWw9cfJ+JnLhFRDmC1X/gYGqBvBiOAqSiO7nQ8eZOKe89zxydtkOUz1"
    b"kZF44shFDkwGHAn6+PTxZ0gDGQvSnt8CLy8txAU0gq0iRBInVyQ5qwcOcby6A6/wM2NbixzOT5IrVenv"
    b"y7Ft50583yedTl831yKCLapESdUUi3Taoz4xzf3PvUphX0hf7xDD9LJxcorjhSP0hiEjIyNEUXRdqIpg"
    b"owoSR+u2uWSza/F9n3K5HK8c3sjC3DgAxWKR4liBTCbD9hdfYmFhscUisZpdaasKIgIIKdeh3fdItTmg"
    b"EX2T45S8HI4FF6bPAVAYi+FhGLJ79y5cW1vMGBODG1DbdqisRsz+UWPmSo0LV+qUvr/Emq5bKF1dpB4Z"
    b"ps6eacILhQJBEPDOu/s5MxexWLXjVCSnzDbGQCw9TF+ucejbEvuPzrN/dJ73vy5x+nwFVWnmsAEvFotx"
    b"poaH+enkKKfPlZvdZyKDraJIUry0C7d1O6y7Obbbe2w6PAv5Cxjg1MRvDA4OEoYh2WyWoaEhLv9aSJQP"
    b"1BhcFcEYpbxSoecmmw0PdDaly7btRrPS5l7TkrUBfPTBe7z8yg7y+TwAT295KgYncmo3JNCxIeVCylVS"
    b"rkXKtXAsBTHUVissLZep1aPYotj27n2D8fFxNm/eRC2KMFGElQTlLi6tcPZSGrGspEEE1diZqDRVUaSK"
    b"SEOVkwUKjz65nWPFWVDFsS1WVg1Xl018g7z18THaO3zESHLAFRVBNHkagzQcQuxcBCTeelwDjS8eUXZt"
    b"e+y/u/P+BD1fHlfoCgy7AAAAAElFTkSuQmCC")

wxDialog_png = PyEmbeddedImage(
    b"iVBORw0KGgoAAAANSUhEUgAAABYAAAAWCAYAAADEtGw7AAAACXBIWXMAAAsTAAALEwEAmpwYAAACLklE"
    b"QVQ4y7WVQWsTURDHf7vZLompaVPQg+jFa8DiqQe/gMceetNCEQX9Bl5ERBD8AF4qKt562EPqKQfpPSJK"
    b"MBEEb8FcckmTGmmzb8bDvt1skm6bUjqwzHs7782b+c9/3oMLEicevNrtqACoggIqqOrEB6Bi/2PXiCKq"
    b"LLiKKyOeb95yAFyAFzu/tLAA4fdtir5D2HhLMZ/D/HiPND9wuejDz4+UFn2WSnmWSwXKpQLlpSIr5UX8"
    b"zcc4955QLJV4+u6bAngA6nrsf9kGiHRlK5lT2aJvx/2/o4x8I+n/M4yMMzY92/mt11f8TLCcaQ/HinJ0"
    b"FNLu7PP60W3HA8jn4M7VzrkL1nVvcjg4IIEijieo1thYv5voWCqra6c6bTXqXPIdvBxjx9iKp50G1Vry"
    b"709nvmxEBSNCwgpLnnNLDhAj44jVnhJHmNYAvW57LsehCJKOWFTPhGfWmtBIEqSbxjjeEOugWku+aafT"
    b"ayKQSTo0giJqZlqNOpXVNVqN+gwc6epnrRHb7mMoUhjHG06jVgYvEE0VzxgzYV6+cmNmS1zAk2wgmNCk"
    b"WTFLt8+NyXuhuRewdX/jRJsYQW2Q7jTd5pG8by8ah6TToszHHeEdt7HXbdPcC8iyfa0FWfdQIl5WVHHa"
    b"Z7VNOO4PhrSH11CViNIa9b2TopHYOkTJxq+MnauScx2GhwN6B2byqn7w8pOKRE+NiiBqtTFIfKDlvIok"
    b"zRDRS6MXTZTdNw8dLlL+A4iuUQ4KRZVvAAAAAElFTkSuQmCC")

class MainFrame(wx.Frame):

    def __init__(self, parent, id=wx.ID_ANY, title="SDI Tests", pos=
                wx.DefaultPosition, size=wx.Size(500, 300),
                style=wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL,
                name=wx.FrameNameStr):
        wx.Frame.__init__(self)

        if not self.Create(parent, id, title, pos, size, style, name):
            return

        self.splitter = wx.SplitterWindow(self, wx.ID_ANY, wx.DefaultPosition,
            wx.DefaultSize, wx.SP_3D)
        self.splitter.SetSashGravity(0.0)
        self.splitter.SetMinimumPaneSize(150)
        self.splitter.SetMinSize(self.ConvertDialogToPixels(wx.Size(200, 200)))

        self.propertyGridManager = wx.propgrid.PropertyGridManager(self.splitter, wx.ID_ANY,
            wx.DefaultPosition, wx.DefaultSize, wx.propgrid.PG_AUTO_SORT|
            wx.propgrid.PG_BOLD_MODIFIED|wx.propgrid.PG_SPLITTER_AUTO_CENTER|
            wx.propgrid.PG_DESCRIPTION|wx.propgrid.PG_TOOLBAR|
            wx.propgrid.PG_NO_INTERNAL_BORDER)
        self.propertyGridManager.SetExtraStyle(wx.propgrid.PG_EX_MODE_BUTTONS)

        self.propertyGridPage = self.propertyGridManager.AddPage("Animal Page", wx.BitmapBundle.FromBitmap(
            images.wxPython_1_5x_png.Bitmap))

        self.propertyGridItem_7 = self.propertyGridPage.Append(
            wx.propgrid.PropertyCategory("Pets", "Pets"))

        self.propertyGridItem_2 = self.propertyGridPage.Append(wx.propgrid.StringProperty(
        "dog", "Woof!"))

        self.propertyGridItem = self.propertyGridPage.Append(wx.propgrid.StringProperty(
        "cat", "Meow!"))

        self.propertyGridItem_5 = self.propertyGridPage.Append(
            wx.propgrid.PropertyCategory("Big Animals", "Big Animals"))

        self.propertyGridItem_8 = self.propertyGridPage.Append(wx.propgrid.StringProperty(
        "horses", ""))

        self.propertyGridPage_2 = self.propertyGridManager.AddPage("Number Page", wx.BitmapBundle.FromBitmap(
            images.english_png.Bitmap))

        self.propertyGridItem_6 = self.propertyGridPage_2.Append(
            wx.propgrid.PropertyCategory("Numbers", "Numbers"))

        self.propertyGridItem_3 = self.propertyGridPage_2.Append(wx.propgrid.IntProperty(
        "1", ""))

        self.propertyGridItem_4 = self.propertyGridPage_2.Append(wx.propgrid.IntProperty(
        "2", ""))

        self.grid = wx.grid.Grid(self.splitter, wx.ID_ANY)
        self.grid.CreateGrid(5, 5)
        self.grid.EnableDragGridSize(False)
        self.grid.SetMargins(0, 0)
        self.grid.SetDefaultCellAlignment(wx.ALIGN_LEFT, wx.ALIGN_TOP)
        self.grid.SetColLabelAlignment(wx.ALIGN_CENTER, wx.ALIGN_CENTER)
        self.grid.SetColLabelSize(wx.grid.GRID_AUTOSIZE)
        self.grid.SetRowLabelAlignment(wx.ALIGN_CENTER, wx.ALIGN_CENTER)
        self.grid.SetRowLabelSize(wx.grid.GRID_AUTOSIZE)
        self.splitter.SplitHorizontally(self.propertyGridManager, self.grid)

        menubar = wx.MenuBar()

        self.menu = wx.Menu()
        menuQuit = wx.MenuItem(self.menu, wx.ID_EXIT)
        entry = wx.AcceleratorEntry()
        if entry.FromString("ALT+X") :
            menuQuit.AddExtraAccel(entry)

        menuQuit.SetBitmap(wx.ArtProvider.GetBitmapBundle(wx.ART_QUIT, wx.ART_MENU))
        self.menu.Append(menuQuit)
        menubar.Append(self.menu, wx.GetStockLabel(wx.ID_FILE))

        menuDialogs = wx.Menu()
        menu_item_3 = wx.MenuItem(menuDialogs, wx.ID_ANY, "MainTestDlg")
        menu_item_3.SetBitmap(wx.BitmapBundle.FromBitmap(images.debug_32_png.Bitmap))
        menuDialogs.Append(menu_item_3)
        menu_item_4 = wx.MenuItem(menuDialogs, wx.ID_ANY, "BookTestDlg")
        menu_item_4.SetBitmap(wx.BitmapBundle.FromBitmap(images.wxNotebook_png.Bitmap))
        menuDialogs.Append(menu_item_4)
        menu_item_2 = wx.MenuItem(menuDialogs, wx.ID_ANY, "PythonDlg")
        bitmaps = [ images.wxPython_png.Bitmap,
                    images.wxPython_1_5x_png.Bitmap,
                    images.wxPython_2x_png.Bitmap ]
        menu_item_2.SetBitmap(wx.BitmapBundle.FromBitmaps(bitmaps))
        menuDialogs.Append(menu_item_2)
        menu_tools_dlg2 = wx.MenuItem(menuDialogs, wx.ID_ANY, "Tools Dialog",
            "Dialog for testing different types of toolbars", wx.ITEM_NORMAL)
        menu_tools_dlg2.SetBitmap(wx.BitmapBundle.FromBitmap(wxToolBar_png.Bitmap))
        menuDialogs.Append(menu_tools_dlg2)
        menuItem3 = wx.MenuItem(menuDialogs, wx.ID_ANY, "Wizard")
        menuItem3.SetBitmap(wx.BitmapBundle.FromBitmap(wxWizard_png.Bitmap))
        menuDialogs.Append(menuItem3)
        menuDialogs.AppendSeparator()
        menuItem_2 = wx.MenuItem(menuDialogs, wx.ID_ANY, "Common Controls...",
            "Common controls", wx.ITEM_NORMAL)
        menuItem_2.SetBitmap(wx.ArtProvider.GetBitmapBundle(wx.ART_TIP, wx.ART_MENU))
        menuDialogs.Append(menuItem_2)
        menuDialogs.AppendSeparator()

        submenu = wx.Menu()
        menu_item_5 = wx.MenuItem(submenu, wx.ID_ANY, "DlgIssue_956")
        menu_item_5.SetBitmap(wx.BitmapBundle.FromBitmap(images.debug_32_png.Bitmap))
        submenu.Append(menu_item_5)
        menu_item_6 = wx.MenuItem(submenu, wx.ID_ANY, "DlgIssue_960")
        menu_item_6.SetBitmap(wx.BitmapBundle.FromBitmap(images.Ainsi_c3_a_se_passe_png.Bitmap))
        submenu.Append(menu_item_6)
        submenu_item = menuDialogs.AppendSubMenu(submenu, "Issue Dialogs")
        submenu_item.SetBitmap(wx.BitmapBundle.FromBitmap(wxDialog_png.Bitmap))
        menubar.Append(menuDialogs, "&Dialogs")

        self.SetMenuBar(menubar)

        self.toolBar = self.CreateToolBar()

        tool_dropdown = self.toolBar.AddTool(wx.ID_ANY, "", wx.ArtProvider.GetBitmapBundle(
            wx.ART_EXECUTABLE_FILE, wx.ART_MENU), wx.EmptyString, wx.ITEM_DROPDOWN)
        tool_dropdown_menu = wx.Menu()
        menu_item = wx.MenuItem(tool_dropdown_menu, wx.ID_ANY, "Wizard...")
        menu_item.SetBitmap(wx.ArtProvider.GetBitmapBundle(wx.ART_FIND, wx.ART_MENU))
        tool_dropdown_menu.Append(menu_item)
        menu_tools_dlg = wx.MenuItem(tool_dropdown_menu, wx.ID_ANY, "Tools Dialog",
            "Dialog for testing different types of toolbars", wx.ITEM_NORMAL)
        tool_dropdown_menu.Append(menu_tools_dlg)
        tool_dropdown.SetDropdownMenu(tool_dropdown_menu)
        tool_4 = self.toolBar.AddTool(wx.ID_ANY, "MainTestDlg", images.debug_32_png.Bitmap)

        tool_5 = self.toolBar.AddTool(wx.ID_ANY, "BookTestDlg", images.wxNotebook_png.Bitmap)

        self.toolBar.AddSeparator()
        tool_3 = self.toolBar.AddTool(wx.ID_ANY, "PythonDlg", images.wxPython_1_5x_png.Bitmap)

        self.toolBar.AddStretchableSpace()

        tool_2 = self.toolBar.AddTool(wx.ID_ANY, "Common Controls...", wx.ArtProvider.GetBitmapBundle(
            wx.ART_TIP, wx.ART_TOOLBAR))

        self.toolBar.Realize()

        self.statusBar = self.CreateStatusBar(2)
        self.statusBar.SetStatusWidths([100, -1])
        self.statusBar.SetStatusStyles([wx.SB_FLAT, wx.SB_FLAT])

        self.Centre(wx.BOTH)

        # Bind Event handlers
        self.Bind(wx.EVT_MENU, self.on_quit, id=wx.ID_EXIT)
        self.Bind(wx.EVT_MENU, self.OnMainTestDlg, id=menu_item_3.GetId())
        self.Bind(wx.EVT_MENU, self.OnBookTestDlg, id=menu_item_4.GetId())
        self.Bind(wx.EVT_MENU, self.OnPythonDlg, id=menu_item_2.GetId())
        self.Bind(wx.EVT_MENU, self.on_tools_dlg, id=menu_tools_dlg2.GetId())
        self.Bind(wx.EVT_MENU, self.OnWizard, id=menuItem3.GetId())
        self.Bind(wx.EVT_MENU, self.OnCommonDialog, id=menuItem_2.GetId())
        self.Bind(wx.EVT_MENU, self.OnDlgIssue_956, id=menu_item_5.GetId())
        self.Bind(wx.EVT_MENU, self.OnDlgIssue_960, id=menu_item_6.GetId())
        self.Bind(wx.EVT_MENU, self.OnWizard, id=menu_item.GetId())
        self.Bind(wx.EVT_MENU, self.on_tools_dlg, id=menu_tools_dlg.GetId())
        self.Bind(wx.EVT_TOOL, self.OnMainTestDlg, id=tool_4.GetId())
        self.Bind(wx.EVT_TOOL, self.OnBookTestDlg, id=tool_5.GetId())
        self.Bind(wx.EVT_TOOL, self.OnPythonDlg, id=tool_3.GetId())
        self.Bind(wx.EVT_TOOL, self.OnCommonDialog, id=tool_2.GetId())

    # Unimplemented Event handler functions
    # Copy any listed and paste them below the comment block, or to your inherited class.
    """
    """

# ************* End of generated code ***********
# DO NOT EDIT THIS COMMENT BLOCK!
#
# Code below this comment block will be preserved
# if the code for this class is re-generated.
# ***********************************************

    # Event handler functions
    def OnChoicebook(self, event):
        event.Skip()

    def OnCommonDialog(self, event):
        event.Skip()

    def OnImportTest(self, event):
        event.Skip()

    def OnListbook(self, event):
        event.Skip()

    def OnMultiTestDialog(self, event):
        event.Skip()

    def OnNotebook(self, event):
        event.Skip()

    def OnOtherCtrls(self, event):
        event.Skip()

    def on_quit(self, event):
        self.Close()

    def OnRibbonDialog(self, event):
        event.Skip()

    def OnToolbook(self, event):
        event.Skip()

    def OnTreebook(self, event):
        event.Skip()

    def OnMainTestDlg(self, event):
        dlg = main_test_dlg.MainTestDialog(self, title="Main Dialog Tests")
        dlg.ShowModal()
        dlg.Destroy()

    def OnBookTestDlg(self, event):
        dlg = booktest_dlg.BookTestDlg(self)
        dlg.ShowModal()
        dlg.Destroy()

    def OnWizard(self, event):
        my_wizard = wizard.Wizard(self)
        my_wizard.Run()
        my_wizard.Destroy()

    def OnPythonDlg(self, event):
        dlg = python_dlg.PythonDlg(self, title="PythonDlg")
        dlg.ShowModal()
        dlg.Destroy()

    def OnDlgIssue_956(self, event):
        dlg = dlgissue_956.DlgIssue_956(self)
        dlg.ShowModal()
        dlg.Destroy()

    def OnDlgIssue_960(self, event):
        dlg = dlgissue_960.DlgIssue_960(self)
        dlg.ShowModal()
        dlg.Destroy()

    def on_tools_dlg(self, event):
        event.Skip()

class MyApp(wx.App):
    def OnInit(self):
        frame = MainFrame(None)
        self.SetTopWindow(frame)

        frame.Show(True)
        return True

app = MyApp()
app.MainLoop()
