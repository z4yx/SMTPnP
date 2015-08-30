import glob
SERIAL_NAME = glob.glob('/dev/cu.usbmodem1421')[0]
SERIAL_BAUD = 115200

MACH_MAX_X = 250000
MACH_MAX_Y = 120000

FEEDER_SIZE = 16 * 1000  # (um)
FEEDER_DRAG_Z = 320

BOARD_Z = 80
BOARD_ORIGIN = (106000-5092, 94750+63024)

TIP_TO_DRAG = (5000, 34500)

COMPONENTS_PARAM = [
    {
        "name": "LED",
        "number": 100,
        "z_pos": 180,
        "tap": {
            "hole_pitch": 4000,  # (um)
            "chip_pitch": 4000,
            "hole_to_chip": (2000, 3500),
            "chips_per_hole": 1
        },
        "base": (26550, 84200)
    },{
        "name": "LED1 test",
        "number": 100,
        "z_pos": 150,
        "tap": {
            "hole_pitch": 4000,  # (um)
            "chip_pitch": 4000,
            "hole_to_chip": (2000, 3500),
            "chips_per_hole": 1
        },
        "base": (25150, 64300-18000)
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
