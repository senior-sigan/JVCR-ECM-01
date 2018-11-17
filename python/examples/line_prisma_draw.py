import jvcr
import math

base = jvcr.DISPLAY_HEIGHT - 1
PI_8 = math.pi / 8
PI_2 = math.pi * 2
t = 0

GREEN = 11
RED = 8
GREY = 6
BLACK = 0


def update(dt):
    global t

    jvcr.cls(BLACK)
    i = math.fmod(t, 8.0)
    while i < base:
        jvcr.line(i, 0, 0, base - i, RED)
        jvcr.line(i, base, base, 143 - i, GREY)
        t += 0.005
        i += 8

    i = math.fmod(t / 16.0, PI_8)
    while i < PI_2:
        x = base / 2.0 + (base / 4.0) * math.cos(i)
        y = base / 2.0 + (base / 4.0) * math.cos(i)
        jvcr.line(base, 0, x, y, GREEN)
        jvcr.line(0, base, x, y, GREEN)
        i += PI_8

    jvcr.line(0, 0, base, 0, 8)
    jvcr.line(0, 0, 0, base, 8)
    jvcr.line(base, 0, base, base, 6)
    jvcr.line(0, base, base, base, 6)
