#include <jvcr_ecm_01/machine.h>
#include <stdlib.h>
#include <stdio.h>

Jvcr *NewJvcr() {
  Jvcr *machine = (Jvcr *) malloc(sizeof(Jvcr));
  machine->ram = NewJvcrRam();
  machine->display = NewJvcrDisplay();
  machine->time = 0;
  printf("Jvcr machine is created: allocated %d bytes\n", RAM_SIZE);
  if (machine->onInit != NULL) machine->onInit(machine);
  return machine;
}

void DestroyJvcr(Jvcr *machine) {
  if (machine->onDestroy != NULL) machine->onDestroy(machine);
  DestroyJvcrRam(machine->ram);
  DestroyJvcrDisplay(machine->display);
  free(machine);
  printf("Jvcr machine is destroyed\n");
}

JvcrRam *NewJvcrRam() {
  JvcrRam *ram = (JvcrRam *) malloc(sizeof(JvcrRam));
  ram->memory = (byte *) calloc(sizeof(byte), RAM_SIZE);
  for (size_t i = 0; i< RAM_SIZE; ram->memory[i++] = 0);
  return ram;
}
void DestroyJvcrRam(JvcrRam *ram) {
  free(ram->memory);
  free(ram);
}

JvcrDisplay *NewJvcrDisplay() {
  JvcrDisplay *display = (JvcrDisplay *) malloc(sizeof(JvcrDisplay));
  display->texture = (byte *) calloc(sizeof(byte), DISPLAY_WIDTH * DISPLAY_HEIGHT * DISPLAY_CHANNELS);
  return display;
}
void DestroyJvcrDisplay(JvcrDisplay *display) {
  free(display->texture);
  free(display);
}