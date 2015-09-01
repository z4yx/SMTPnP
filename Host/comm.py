import serial
import threading
import conf
import wx
import wx.lib.newevent
import time

_com = None
_thread = None
RecvEvent, EVT_RECV = wx.lib.newevent.NewEvent()


def DecodeReport(line):
    line = line.strip()
    if line.startswith('!I#'):
        d = line[3:].split('#')
        if len(d) == 2 and len(d[0]):
            return d[0], d[1]
    return None, None


class RecvThread(threading.Thread):

    def __init__(self):
        super(RecvThread, self).__init__()
        self.daemon = True

    def pass_message(self, info, content):
        pass

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
                self.pass_message(info, content)


class RecvThread4wx(RecvThread):

    def __init__(self, win):
        super(RecvThread4wx, self).__init__()
        self.win = win

    def pass_message(self, info, content):
        evt = RecvEvent(info=info, content=content)
        wx.PostEvent(self.win, evt)


class RecvThread4queue(RecvThread):

    def __init__(self, q):
        super(RecvThread4queue, self).__init__()
        self.q = q

    def pass_message(self, info, content):
        item = (info, content)
        self.q.put_nowait(item)


def Init(win=None, queue=None):
    global _com, _thread
    assert(win or queue)
    _com = serial.Serial(conf.SERIAL_NAME, conf.SERIAL_BAUD)
    if win:
        _thread = RecvThread4wx(win)
    elif queue:
        _thread = RecvThread4queue(queue)
    _thread.start()

last_sent = 0
def Write(data):
    global last_sent
    d = time.clock() - last_sent
    if d < 0.1:
        time.sleep(0.1 - d)
    _com.write(data)
    last_sent = time.clock()

def SendCommand(name, param):
    cmd="!{}#{}\r\n".format(name, param)
    print "Cmd: ",cmd.strip()
    Write(cmd)


def SendDebugCommand(target, param):
    SendCommand("DBG", '{}{}'.format(target, param))

def SendSetCoordinateCommand(x, y):
    SendCommand("SETC", '{},{}'.format(x, y))


def SendGetCoordinateCommand():
    SendCommand("GETC", '')


def SendAbsoluteXYMove(x, y):
    SendCommand("ABSXY", '{},{}'.format(x, y))


def SendAbsoluteZMove(z_steps):
    SendCommand("ABSZ", '{}'.format(z_steps))

def SendHomeXY():
    SendCommand("HOMEXY", '')

def SendHomeZ():
    SendCommand("HOMEZ", '')

def SendToolheadRotate(degree):
    SendCommand("ROTATE", '{}'.format(degree))


# def SendRelativeMove(axis, distance):
#     SendCommand(axis, distance)

# def SetCallbackWindow(win):
#     global _callback_win
#     _callback_win = win
def Close():
    global _com
    _com.close()
