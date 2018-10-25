#include <gtest/gtest.h>
#include <jvcr_ecm_01/machine.h>
#include <jvcr_ecm_01/ram.h>

TEST(ram_test, jvcr_memcpy) {
  JvcrRam* ram = NewJvcrRam();
  for (byte i = 0; i < 10; i++) {
    ram->memory[i] = i;
  }
  jvcr_memcpy(ram, 42, 0, 10);
  for (int i = 0; i < 10;i++) {
    ASSERT_EQ(ram->memory[i], ram->memory[i+42]);
  }
}