import jvcr

def update(dt):
    w = jvcr.DISPLAY_WIDTH // jvcr.PALETTE_LEN
    for i in range(jvcr.PALETTE_LEN):
        jvcr.rectfill(i*w, 0, w, jvcr.DISPLAY_HEIGHT, i)