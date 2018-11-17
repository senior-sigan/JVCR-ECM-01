import jvcr
import random

time = 0


def update(dt):
    global time

    time += dt
    for i in range(4800):
        x = random.randrange(jvcr.DISPLAY_WIDTH)
        y = random.randrange(jvcr.DISPLAY_HEIGHT)
        jvcr.pset(x, y, int(time) % 16)
