#ifndef JVCR_ECM_01_API_H
#define JVCR_ECM_01_API_H

#include <jvcr_ecm_01/types.h>
#include <jvcr_ecm_01/machine.h>

void jvcr_memcpy(Jvcr *machine, u32 dest, u32 src, u32 len); // copy bytes
void jvcr_memset(Jvcr *machine, u32 dest, byte value, u32 len); // set len bytes to val
void jvcr_memseta(Jvcr *machine, u32 dest, byte *val, u32 len); // set len bytes to val
byte jvcr_peek(Jvcr *machine, u32 address); // read a byte in ram address
void jvcr_poke(Jvcr *machine, u32 address, byte value); // write a byte in ram address

#endif //JVCR_ECM_01_API_H