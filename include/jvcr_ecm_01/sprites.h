#ifndef PROJECT_SPRITES_H
#define PROJECT_SPRITES_H

#include <jvcr_ecm_01/types.h>

typedef struct Sprite {
  u32 index;
  i32 x;
  i32 y;
  u32 w;
  u32 h;
  byte scale;
  byte flip;
  byte rotation;
} Sprite;

/**
 * Draw a sprite on the scene at location
 * @param index of the sprite in the sprite sheet
 * @param x coordinate on the screen where to draw the sprite
 * @param y coordinate on the screen where to draw the sprite
 * @param scale factor that will be applied on the sprite before drawing
 * @param flip flip the sprite vertically or horizontally or both: [0=no flip, 1=horizontal, 2=vertical, 3=both]
 * @param rotation rotates the sprite by 0, 90, 180 or 270 degrees. [0=0, 1=90, 2=180, 3=270]
 * @param w width of composite sprite
 * @param h height of composite sprite
 */
void spr(u32 index, i32 x, i32 y, byte scale, byte flip, byte rotation, u32 w, u32 h);

/**
 * Loads entire sprite sheet to the memory
 * @param sheet indexed image. Each pixel is the color index from the pallet
 */
void load_sprite_sheet(byte *sheet);

#endif //PROJECT_SPRITES_H
