#include <jvcr_ecm_01/ram.h>

void jvcr_memcpy(JvcrRam *machine, ptr_t dest, ptr_t src, u32 len) {
  if (dest >= RAM_SIZE) return; // TODO: may be "throw" warning somehow?
  if (src >= RAM_SIZE) return; // TODO: may be "throw" warning somehow?
  for (;len > 0 && dest < RAM_SIZE && src < RAM_SIZE; machine->memory[dest++] = machine->memory[src++], len--);
}

void jvcr_memset(JvcrRam *machine, ptr_t dest, byte value, u32 len) {
  if (dest >= RAM_SIZE) return; // TODO: may be "throw" warning somehow?
  for (;len > 0 && dest < RAM_SIZE; machine->memory[dest++] = value, len--);
}

byte jvcr_peek(JvcrRam *machine, ptr_t address) {
  if (address >= RAM_SIZE) return 0; // TODO: may be "throw" warning somehow?
  return machine->memory[address];
}

void jvcr_poke(JvcrRam *machine, ptr_t address, byte value) {
  if (address >= RAM_SIZE) return; // TODO: may be "throw" warning somehow?
  machine->memory[address] = value;
}