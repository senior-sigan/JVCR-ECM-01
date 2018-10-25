#include <jvcr_ecm_01/ram.h>

void jvcr_memcpy(JvcrRam *machine, ptr_t dest, ptr_t src, u32 len) {
  for (;len > 0; machine->memory[dest++] = machine->memory[src++], len--);
}