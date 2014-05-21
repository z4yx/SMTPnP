import csv_reader
import comm
import feeder
import move
import conf
import time

move.Init()

print "Set to zero..."
comm.SendSetCoordinateCommand(0,0)
time.sleep(0.2)

board_origin = (344392, -3224)


def Material2BoardPos(m_x, m_y):
    return (board_origin[0] - m_x, m_y + board_origin[1])

field_info, data = csv_reader.ParseCSV("LED.csv")
material_list = csv_reader.MakeMaterialList(field_info, data)

for i in material_list:
    c = feeder.FindComponentByName(i.Mark)
    if not c:
        continue
    print i.Designator
    if c.NeedTapeMoving():
        s, e, z = c.TapeMoving()
        move.DoTapeMove(s, e, z)

    pos, comp_z = c.GetComponentPos()
    move.DoPlace(pos, comp_z, Material2BoardPos(i.X, i.Y), conf.BOARD_Z, i.Rotation)
