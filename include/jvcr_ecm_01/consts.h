#ifndef JVCR_ECM_01_CONSTS_H
#define JVCR_ECM_01_CONSTS_H

#define DISPLAY_WIDTH 256u
#define DISPLAY_HEIGHT 144u
#define DISPLAY_CHANNELS 4u

#define SCREEN_START 0x0
// To avoid 4bit settings, and simplify code we allocate 8 bits for color instead of 4 bits.
#define SCREEN_SIZE 0x9000 // 256x144 4-bit screen.
#define SCREEN_END (SCREEN_START+SCREEN_SIZE)

#define PALETTE_START SCREEN_END
#define PALETTE_LEN 16u // colors count
#define PALETTE_UNIT 4u // color size in bytes
#define PALETTE_SIZE (PALETTE_LEN*PALETTE_UNIT) // 16 x 24-bit RGBA color values
#define PALETTE_END (PALETTE_START+PALETTE_SIZE)

#define PALETTE_MAP_START PALETTE_END
#define PALETTE_MAP_SIZE 0x0008 // 16 x 4-bit color indexes
#define PALETTE_MAP_END (PALETTE_MAP_START+PALETTE_MAP_SIZE)

#define TILES_START PALETTE_MAP_END
#define TILES_SIZE 0x2000 // 256 8x8 4bit bg sprites - #0 to #255
#define TILES_END (TILES_START+TILES_SIZE)

#define SPRITES_START TILES_END
#define SPRITES_SIZE 0x2000 // 256 8x8 4bit fg sprites (tiles) - #256 to #511
#define SPRITES_END (SPRITES_START+SPRITES_SIZE)

#define MAP_START SPRITES_END
#define MAP_SIZE 0x9000 // 8x8 240x136 map cells
#define MAP_END (MAP_START+MAP_SIZE)

#define FONTS_START MAP_END
#define FONT_WIDTH 5
#define FONT_HEIGHT 7
#define FONT_SPACING 1
#define FONTS_UNIT 8u // 8 bytes
#define FONTS_LEN 256u
#define FONTS_SIZE (FONTS_UNIT*FONTS_LEN) // 8 bytes per symbol, 256 symbols
#define FONTS_END (FONTS_START+FONTS_SIZE)

#define GAMEPADS_START FONTS_END
#define GAMEPADS_SIZE 0x0004 // 4 gamepads x 8 buttons (Up Down Left Right A B X Y)
#define GAMEPADS_END (GAMEPADS_START+GAMEPADS_SIZE)

#define KEYBOARD_START GAMEPADS_END
#define KEYBOARD_SIZE 0x0004
#define KEYBOARD_END (KEYBOARD_START + KEYBOARD_SIZE)

#define RAM_SIZE (KEYBOARD_END-SCREEN_START)

#endif //JVCR_ECM_01_CONSTS_H
