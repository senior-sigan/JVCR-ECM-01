from jvcr import btn, print_symbol, cls
import jvcr


def update(dt):
    cls(0)

    if btn(jvcr.BTN_UP, 0):
        print_symbol('W', 10, 1, 8)
    if btn(jvcr.BTN_DOWN, 0):
        print_symbol('S', 10, 10, 8)
    if btn(jvcr.BTN_LEFT, 0):
        print_symbol('A', 1, 10, 8)
    if btn(jvcr.BTN_RIGHT, 0):
        print_symbol('D', 20, 10, 8)
    if btn(jvcr.BTN_A, 0):
        print_symbol('Z', 1, 30, 8)
    if btn(jvcr.BTN_B, 0):
        print_symbol('X', 10, 30, 8)
    if btn(jvcr.BTN_X, 0):
        print_symbol('C', 20, 30, 8)
    if btn(jvcr.BTN_Y, 0):
        print_symbol('V', 30, 30, 8)
