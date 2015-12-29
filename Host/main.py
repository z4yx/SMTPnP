#!/usr/bin/env python
# encoding: utf-8
import csv_reader
import comm
import feeder
import move
import conf
import time

move.Init()
move.HomeAndWait()

def Material2BoardPos(m_x, m_y):
    return (conf.BOARD_ORIGIN[0] + m_x, conf.BOARD_ORIGIN[1] - m_y)

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
