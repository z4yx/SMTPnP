import serial
import threading
import conf
import wx
import wx.lib.newevent

_com = None
_thread = None
RecvEvent, EVT_RECV = wx.lib.newevent.NewEvent()
# _evt_type = wx.NewEventType()
# EVT_RECV = wx.PyEventBinder(_evt_type, 1)


# class RecvEvent(wx.PyCommandEvent):

#     def __init__(self, etype, eid, value=None):
#         wx.PyCommandEvent.__init__(self, etype, eid)
#         self._value = value

#     def GetValue(self):
#         return self._value

def DecodeReport(line):
    line = line.strip()
    if line.startswith('!I#'):
        d = line[3:].split('#')
        if len(d) == 2 and len(d[0]):
            return d[0], d[1]
    return None, None


class RecvThread(threading.Thread):

    def __init__(self, win):
        super(RecvThread, self).__init__()
        self.win = win

    def run(self):
        global _com, _evt_type
        while True:
            line = None
            try:
                line = _com.readline()
            except Exception, e:
                pass
            if not line:
                break
            print "recv: %s" % line.strip()
            info, content = DecodeReport(line)
            if info:
                # evt = RecvEvent(_evt_type, -1, line)
                evt = RecvEvent(info=info, content=content)
                wx.PostEvent(self.win, evt)


def Init(win=None):
    global _com, _thread
    _com = serial.Serial(conf.SERIAL_NAME, conf.SERIAL_BAUD)
    _thread = RecvThread(win)
    _thread.start()


def Write(data):
    _com.write(data)


def SendCommand(name, param):
    Write("!{}#{}\r\n".format(name, param))


def SendDebugCommand(target, param):
    SendCommand("DBG", '{}{}'.format(target, param))


def SendSetCoordinateCommand(x, y):
    SendCommand("SETC", '{},{}'.format(x, y))


def SendGetCoordinateCommand():
    SendCommand("GETC", '')
    
# def SendRelativeMove(axis, distance):
#     SendCommand(axis, distance)

# def SetCallbackWindow(win):
#     global _callback_win
#     _callback_win = win


def Close():
    global _com
    _com.close()
