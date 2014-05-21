import Queue
import comm
import time
import conf

reply_queue = Queue.Queue()


def Init():
    comm.Init(queue=reply_queue)


def WaitMoveDone(type):
    flag = True
    while flag:
        print "Waiting for move"
        item = reply_queue.get()
        print "Done {}".format(item)
        if item[0] == 'DONE' and item[1] == type:
            flag = False
        reply_queue.task_done()


def DoTapeMove(start, end, z):
    print "DoTapeMove... {} {} {}".format(start, end, z)
    comm.SendAbsoluteXYMove(start[0], start[1])
    WaitMoveDone("move")
    comm.SendAbsoluteZMove(z)
    WaitMoveDone("toolhead")
    comm.SendAbsoluteXYMove(end[0], end[1])
    WaitMoveDone("move")
    comm.SendAbsoluteZMove(0)
    WaitMoveDone("toolhead")


def DoPlace(CompPos, CompZ, BoardPos, BoardZ, Rotation):
    print "DoPlace... {} {} {} {}".format(CompPos, CompZ, BoardPos, BoardZ)
    comm.SendAbsoluteXYMove(CompPos[0], CompPos[1])
    WaitMoveDone("move")
    comm.SendAbsoluteZMove(CompZ)
    WaitMoveDone("toolhead")
    # vacuum on
    comm.SendAbsoluteZMove(0)
    WaitMoveDone("toolhead")
    comm.SendToolheadRotate(Rotation)
    #
    comm.SendAbsoluteXYMove(BoardPos[0], BoardPos[1])
    WaitMoveDone("move")
    comm.SendAbsoluteZMove(BoardZ)
    WaitMoveDone("toolhead")
    # vacuum off
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
