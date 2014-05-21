import conf


class Component:

    def __init__(self, param):
        self.param = param
        self.current = 0
        self.num_holes = int(
            conf.FEEDER_SIZE / self.param["tap"]["hole_pitch"])
        self.available = self.__calc_available()

    def __calc_available(self):
        return self.num_holes * self.param["tap"]["chips_per_hole"]

    def NeedTapeMoving(self):
        return self.available == 0

    def TapeMoving(self):
        self.available = self.__calc_available()
        self.current = 0
        to = self.param["base"]
        frm = (to[0] - (self.num_holes - 1) *
               self.param["tap"]["hole_pitch"], to[1])
        return (frm, to, conf.FEEDER_DRAG_Z)

    def GetComponentPos(self):
        if self.available == 0:
            raise ValueError, "No available component"
        base = self.param["base"]
        pos = (base[0] - self.param["tap"]["hole_to_chip"][0] -
               self.current * self.param["tap"]["chip_pitch"], 
               base[1] + self.param["tap"]["hole_to_chip"][1])

        self.available -= 1
        self.current += 1
        return (pos, self.param["z_pos"])

    def GetName(self):
        return self.param["name"]

    def __str__(self):
        return "Component '{}'".format(self.GetName())

components = [ Component(i) for i in conf.COMPONENTS_PARAM]

def FindComponentByName(name):
    for x in components:
        if x.GetName() == name:
            return x

    return None

if __name__ == '__main__':
    c = FindComponentByName("Cap Semi")
    for x in xrange(100):
        if c.NeedTapeMoving():
            print "Moving: {}".format(c.TapeMoving())
        print "Got one: {}".format(c.GetComponentPos())
