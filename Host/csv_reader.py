import re


def split_line(line):
    l = re.split(',', line)
    # for i in xrange(0, len(l)):
    #     l[i] = l[i][1:-1]
    return l


def ParseCSV(filename):
    try:
        f = open(filename)
        ln = 0
        field_info = None
        data = None
        if not f:
            return None
        for line in f.readlines():
            line = line.strip()
            ln += 1
            if ln == 1:
                field_info = split_line(line)
                data = []
                # data = [[] for i in xrange(len(field_info))]
            elif len(line) <= 2:
                continue
            else:
                data_line = split_line(line)
                if len(field_info) != len(data_line):
                    raise ValueError, 'column size error at line {}'.format(ln)
                data.append(data_line)
                # for i in xrange(len(data_line)):
                    # data[i].append(data_line[i])
    except Exception, e:
        print "%s" % e
        return None
    # t = {}
    # for i in xrange(len(field_info)):
    #     t[field_info[i]] = data[i]
    return field_info, data

def StripUnit(s):
    if s.endswith('mm'):
        return int(float(s[0:-2])*1000) #mm->um
    raise ValueError, "Unknown unit: {}".format(s)

class MaterialItem:

    def __init__(self, x, y, rotation, mark, designator):
        self.X = StripUnit(x)
        self.Y = StripUnit(y)
        self.Rotation = int(float(rotation))
        self.Mark = mark
        self.Designator = designator

def MakeMaterialList(field_info, data):
    col_x = field_info.index("Mid X")
    col_y = field_info.index("Mid Y")
    col_r = field_info.index("Rotation")
    col_mark = field_info.index("Comment")
    col_d = field_info.index("Designator")

    t = []
    for i in data:
        if i[col_x] and i[col_y] and i[col_r]:
            t.append(MaterialItem(i[col_x], i[col_y], i[col_r], i[col_mark], i[col_d]))

    return t

if __name__ == '__main__':
    print ParseCSV("test.csv")
