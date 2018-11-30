#include <jvcr_ecm_01/import_sprites.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <jvcr_ecm_01/ram.h>

void import_sprites(Jvcr *machine, const char *path, ptr_t offset) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    perror("File opening failed");
    exit(-1);
  }
  unsigned char header[8];
  fread(header, 1, 8, file);
  if (png_sig_cmp(header, 0, 8)) {
    printf("File %s is not recognized as a PNG file", path);
    exit(-1);
  }
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (png == NULL) {
    perror("png_create_read_struct failed");
    exit(-1);
  }
  png_infop info = png_create_info_struct(png);
  if (info == NULL) {
    perror("png_create_info_struct failed");
    exit(-1);
  }
  if (setjmp(png_jmpbuf(png))) {
    perror("[read_png_file] Error during init_io");
    exit(-1);
  }
  png_init_io(png, file);
  png_set_sig_bytes(png, 8);
  png_read_info(png, info);

  png_uint_32 width = png_get_image_width(png, info);
  png_uint_32 height = png_get_image_height(png, info);
  png_byte color_type = png_get_color_type(png, info);
  png_byte bit_depth = png_get_bit_depth(png, info);

  printf("width=%lu height=%lu color_type=%d bit_depth=%d\n", width, height, color_type, bit_depth);

  if (color_type != PNG_COLOR_TYPE_PALETTE) {
    printf("Image should be with palette color type\n");
    exit(-1);
  }

  png_bytepp row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height);
  size_t row_size = png_get_rowbytes(png, info);
  printf("row_size = %lu\n", row_size);
  for (png_uint_32 y = 0; y < height; y++) {
    row_pointers[y] = (png_byte *) malloc(row_size);
    for (png_uint_32 x = 0; x < row_size; x++) {
      row_pointers[y][x] = 0;
    }
  }
  png_read_image(png, row_pointers);


  printf("\n======================\n");
  byte palette[256];
  for (int i = 0; i < 256; i++) palette[i] = 255;
  byte index = 0;
  for (png_uint_32 y = 0; y < height; y++) {
    png_bytep row = row_pointers[y];
    for (png_uint_32 x = 0; x < width; x++) {
      png_byte pyxel = row[x];
      if (palette[pyxel] == 255) {
        printf("%d = %d\n", pyxel, index);
        palette[pyxel] = index;
        index++;
      }
    }
  }
  printf("======================\n");

  for (png_uint_32 y = 0; y < height; y++) {
    png_bytep row = row_pointers[y];
    for (png_uint_32 x = 0; x < width; x++) {
      png_byte pyxel = row[x];
      jvcr_poke(machine->ram, SPRITES_START + offset + width * x + y, pyxel);
      printf("%2d ", pyxel);
    }
    printf("\n");
  }

  printf("SUCCESS. File was read %s\n", path);
  for (png_uint_32 y = 0; y < height; y++) {
    free(row_pointers[y]);
  }
  free(row_pointers);
  fclose(file);
}
