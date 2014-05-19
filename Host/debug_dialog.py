#!/usr/bin/env python
# encoding: utf-8

import wx
from wx import xrc
import comm
import util
import re

class DebugDialog(wx.Dialog):

    def __init__(self):
        wx.Dialog.__init__(self, None, -1, 'Debug Utility')

        self.res = xrc.XmlResource('debug_dialog.xrc')
        self.panel = self.res.LoadPanel(self, 'panel')
        self.panel.Fit()
        self.Fit()

        self.createText()
        self.createBtns()

        util.CreateCloseShortcut(self)
        self.Bind(comm.EVT_RECV, self.onRecv)
        self.Bind(wx.EVT_SHOW, self.onShow)


    def createText(self):
        self.text_xy = xrc.XRCCTRL(self.panel, "TextXY")
        self.text_z = xrc.XRCCTRL(self.panel, "TextZ")
        self.text_rot = xrc.XRCCTRL(self.panel, "TextR")

    def createBtns(self):
        self.Btns = {
            xrc.XRCID("YPlus"): (self.onRMoveClick, "Y", 1),
            xrc.XRCID("YMinus"): (self.onRMoveClick, "Y", -1),
            xrc.XRCID("XPlus"): (self.onRMoveClick, "X", 1),
            xrc.XRCID("XMinus"): (self.onRMoveClick, "X", -1),
            xrc.XRCID("ZPlus"): (self.onRMoveClick, "Z", 1),
            xrc.XRCID("ZMinus"): (self.onRMoveClick, "Z", -1),
            xrc.XRCID("Rotate"): (self.onRotateClick, "A"),
            xrc.XRCID("SetCur"): (self.onCoordSetClick, "cur"),
            xrc.XRCID("SetZero"): (self.onCoordSetClick, "zero"),
        }
        for (btn_id, param) in self.Btns.items():
            self.Bind(wx.EVT_BUTTON, param[0], id=btn_id)

    def onShow(self, evt):
        comm.SendGetCoordinateCommand()

    def onRecv(self, evt):
        if evt.info == "DONE":
            print "operation '%s' done!" % evt.content
        elif evt.info == "COORD":
            coord = evt.content.split()
            self.text_xy.SetValue("({},{})".format(coord[0], coord[1]))
            self.text_z.SetValue("({})".format(coord[2]))

    def onCoordSetClick(self, event):
        _id = event.GetId()
        _param = self.Btns[_id]
        if _param[1] == "cur":
            match = re.search('X=([-\d]+),Y=([-\d]+)',self.text_xy.GetValue())
            if match:
                c = match.groups()
                if len(c)==2:
                    comm.SendSetCoordinateCommand(c[0], c[1])
        elif _param[1] == "zero":
            comm.SendSetCoordinateCommand(0, 0)

    def onRotateClick(self, event):
        try:
            s = self.text_rot.GetValue()
            deg = int(s)
            comm.SendDebugCommand("A", deg)
        except Exception, e:
            raise e

    def onRMoveClick(self, event):
        _id = event.GetId()
        _param = self.Btns[_id]
        value = 100
        comm.SendDebugCommand(_param[1], _param[2] * value)

if __name__ == '__main__':
    app = wx.PySimpleApp()
    app.MainLoop()
    dialog = DebugDialog()
    comm.Init(dialog)
    dialog.ShowModal()
    # comm.SetCallbackWindow(None)
    comm.Close()
    dialog.Destroy()
