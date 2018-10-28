#ifndef PROJECT_FONTS_H
#define PROJECT_FONTS_H

#include <jvcr_ecm_01/types.h>

typedef struct {
  byte lines[8];
} Font;

const Font DEFAULT_FONT[256];

#endif //PROJECT_FONTS_H
