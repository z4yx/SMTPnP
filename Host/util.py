import wx


def CreateCloseShortcut(win):
    randomId = wx.NewId()

    f = lambda e: win.Close()
    win.Bind(wx.EVT_MENU, f, id=randomId)
    accel_tbl = wx.AcceleratorTable(
        [(wx.ACCEL_CTRL,  ord('W'), randomId)])
    win.SetAcceleratorTable(accel_tbl)
