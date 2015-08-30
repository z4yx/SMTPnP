import Queue
import comm
import time
import conf

reply_queue = Queue.Queue()


def Init():
    comm.Init(queue=reply_queue)


def WaitForReply(token, type):
    flag = True
    while flag:
        item = reply_queue.get()
        print "WaitForReply {}".format(item)
        if item[0] == token and (type == None or item[1] == type):
            flag = False
        reply_queue.task_done()

def VacuumPrepare():
    comm.SendCommand("DBG", "v1")
    WaitForReply("RE", None)

def VacuumOn():
    comm.SendCommand("DBG", "f1")
    WaitForReply("RE", None)

def VacuumOff():
    comm.SendCommand("DBG", "f0")
    WaitForReply("RE", None)
    comm.SendCommand("DBG", "v0")
    WaitForReply("RE", None)

def WaitMoveDone(type):
    WaitForReply("DONE", type)

def HomeAndWait():
    comm.SendHomeZ()
    WaitMoveDone("toolhead")
    comm.SendHomeXY()
    WaitMoveDone("move")

def DoTapeMove(start, end, z):
    print "DoTapeMove... {} {} {}".format(start, end, z)
    comm.SendAbsoluteXYMove(start[0], start[1])
    WaitMoveDone("move")
    comm.SendAbsoluteZMove(-z)
    WaitMoveDone("toolhead")
    comm.SendAbsoluteXYMove(end[0], end[1])
    WaitMoveDone("move")
    comm.SendAbsoluteZMove(0)
    WaitMoveDone("toolhead")


def DoPlace(CompPos, CompZ, BoardPos, BoardZ, Rotation):
    CompPos = (CompPos[0]+conf.TIP_TO_DRAG[0], CompPos[1]-conf.TIP_TO_DRAG[1])
    BoardPos = (BoardPos[0]+conf.TIP_TO_DRAG[0], BoardPos[1]-conf.TIP_TO_DRAG[1])
    print "DoPlace... {} {} {} {}".format(CompPos, CompZ, BoardPos, BoardZ)
    comm.SendAbsoluteXYMove(CompPos[0], CompPos[1])
    WaitMoveDone("move")
    VacuumPrepare()
    comm.SendAbsoluteZMove(CompZ)
    WaitMoveDone("toolhead")
    VacuumOn()

    comm.SendAbsoluteZMove(0)
    WaitMoveDone("toolhead")
    comm.SendToolheadRotate(Rotation)
    WaitMoveDone("toolhead")

    comm.SendAbsoluteXYMove(BoardPos[0], BoardPos[1])
    WaitMoveDone("move")
    comm.SendAbsoluteZMove(BoardZ)
    WaitMoveDone("toolhead")
    VacuumOff()

    comm.SendAbsoluteZMove(0)
    WaitMoveDone("toolhead")

if __name__ == '__main__':
    import feeder
    Init()
    c = feeder.FindComponentByName("Cap Semi")
    for x in xrange(3):
        # s, e, z = c.TapeMoving()
        # DoTapeMove(s, e, z)
        pos, z = c.GetComponentPos()
        DoPlace(pos, z, (230000,76000), conf.BOARD_Z, 45)
        time.sleep(1)
