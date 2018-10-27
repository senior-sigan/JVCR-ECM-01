#include <gtest/gtest.h>

#ifdef __cplusplus
extern "C" {
#endif
#include <jvcr_ecm_01/machine.h>
#include <jvcr_ecm_01/ram.h>
#include <jvcr_ecm_01/display.h>
#ifdef __cplusplus
}  // End of extern "C" block
#endif

TEST(ram_test, default_pallet) {
  Jvcr *machine = NewJvcr();
  set_default_pallet(machine);
  for (byte i = 0; i < PALETTE_LEN; i++) {
    auto color = get_rgba(machine, i);
    printf("color=%d rgb=[%d,%d,%d]\n", i, color.red, color.green, color.blue);
  }
}