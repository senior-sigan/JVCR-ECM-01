#ifndef JVCR_ECM_01_API_H
#define JVCR_ECM_01_API_H

#include <jvcr_ecm_01/types.h>
#include <jvcr_ecm_01/machine.h>

void jvcr_memcpy(JvcrRam *machine, ptr_t dest, ptr_t src, u32 len); // copy bytes
void jvcr_memset(JvcrRam *machine, ptr_t dest, byte value, u32 len); // set len bytes to val
byte jvcr_peek(JvcrRam *machine, ptr_t address); // read a byte in ram address
void jvcr_poke(JvcrRam *machine, ptr_t address, byte value); // write a byte in ram address

#endif //JVCR_ECM_01_API_H
