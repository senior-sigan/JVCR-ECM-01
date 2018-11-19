#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include <jvcr_ecm_01/types.h>

typedef struct Tile {
  u32 index;
  i32 x;
  i32 y;
  byte scale;
  byte flip;
  byte rotation;
} Tile;

/**
 * Draw the map on the screen
 * @param x The left-most cell to start drawing the map.
 * @param y The top-most cell to start drawing the map.
 * @param w The amount of cells to draw horizontally from cellx.
 * @param h The amount of cells to draw vertically from celly.
 * @param sx The x coordinate to draw the map to the screen.
 * @param sy The y coordinate to draw the map to the screen.
 * @param scale Map scaling.
 * @param on_tile function callback called before every tile drawing, you can show/hide tiles on map rendering stage (also, you can remap tile index to make map animation or even flip/rotate)
 */
void map(i32 x, i32 y, i32 w, i32 h, i32 sx, i32 sy, byte scale, Tile *(*on_tile)(Tile *tile));

#endif //PROJECT_MAP_H
