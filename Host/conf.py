#!/usr/bin/env python
#--coding: utf-8
import glob

USE_NET = False;True

NETWORK_IP = '192.168.1.1'
NETWORK_PORT = 2001

SERIAL_NAME = glob.glob('/dev/cu.usbmodem1421')[0]
SERIAL_BAUD = 115200

MACH_MAX_X = 148000
MACH_MAX_Y = 121000

FEEDER_SIZE = 16 * 1000  # (um)
FEEDER_DRAG_Z = 660

#坐标以贴片头为准

BOARD_Z = 185
BOARD_ORIGIN = (49336, 16156)

TIP_TO_DRAG = (119276-115292, 106722-75988)

MACH_X_DIR = 1
MACH_Y_DIR = 1

COMPONENTS_PARAM = [
    {
        "name": "LED",
        "number": 100,
        "z_pos": 150,
        "tap": {
            "hole_pitch": 4000,  # (um)
            "chip_pitch": 4000,
            "hole_to_chip": (2000, 3500),
            "chips_per_hole": 1
        },
        "base": (25150, 64300)
    },{
        "name": "LED1 test",
        "number": 100,
        "z_pos": 160,
        "tap": {
            "hole_pitch": 4000,  # (um)
            "chip_pitch": 4000,
            "hole_to_chip": (2000, 3500),
            "chips_per_hole": 1
        },
        "base": (116552, 80067) #hole coord
    },{
        "name": "Res Semi test",
        "number": 100,
        "z_pos": 150,
        "tap": {
            "hole_pitch": 4000,  # (um)
            "chip_pitch": 2000,
            "hole_to_chip": (0, 3500),
            "chips_per_hole": 2
        },
        "base": (25150, 64300+18000)
    }
]
