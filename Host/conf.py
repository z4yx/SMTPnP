
SERIAL_NAME = '/dev/cu.usbmodem621'
SERIAL_BAUD = 115200

MACH_MAX_X = 350000
MACH_MAX_Y = 350000

FEEDER_SIZE = 20 * 1000  # (um)
FEEDER_DRAG_Z = 800

BOARD_Z = 220

COMPONENTS_PARAM = [
    {
        "name": "LED",
        "number": 100,
        "z_pos": 800,
        "tap": {
            "hole_pitch": 4000,  # (um)
            "chip_pitch": 4000,
            "hole_to_chip": (2000, 3500),
            "chips_per_hole": 1
        },
        "base": (21500, 136300)
    },{
        "name": "LED1 test",
        "number": 100,
        "z_pos": 800,
        "tap": {
            "hole_pitch": 4000,  # (um)
            "chip_pitch": 4000,
            "hole_to_chip": (2000, 3500),
            "chips_per_hole": 1
        },
        "base": (21500, 11000)
    },{
        "name": "Res Semi test",
        "number": 100,
        "z_pos": 800,
        "tap": {
            "hole_pitch": 4000,  # (um)
            "chip_pitch": 2000,
            "hole_to_chip": (0, 3500),
            "chips_per_hole": 2
        },
        "base": (21500, 21000)
    }
]
