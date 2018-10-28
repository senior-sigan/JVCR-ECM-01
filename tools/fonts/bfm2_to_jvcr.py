import json
import pprint

def parse(line):
    return line[4:12]


def convert(file_path):
    font = json.load(open(file_path))
    res = [[]] * 256
    for i in range(0, 256):
        glyph = font.get(str(i), None)
        if glyph is None:
            res[i] = [0] * 8
        else:
            res[i] = parse(glyph)
    return res


def print_c_header(data):
    return pprint.pformat(data).replace('[', '{').replace(']', '}')


def main(file_path):
    data = convert(file_path)
    print(print_c_header(data))


if __name__ == '__main__':
    main("jvcr_ecm_01_font.json")
