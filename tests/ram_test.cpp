#include <gtest/gtest.h>

#ifdef __cplusplus
extern "C" {
#endif
#include <jvcr_ecm_01/machine.h>
#include <jvcr_ecm_01/ram.h>
#ifdef __cplusplus
}  // End of extern "C" block
#endif

TEST(ram_test, new_ram) {
  JvcrRam *ram = NewJvcrRam();
  for (size_t i = 0; i < RAM_SIZE; i++) {
    ASSERT_EQ(ram->memory[i], 0);
  }
}

TEST(ram_test, jvcr_memcpy) {
  JvcrRam *ram = NewJvcrRam();
  for (byte i = 0; i < 10; i++) {
    ram->memory[i] = static_cast<byte>(i+1);
  }
  jvcr_memcpy(ram, 42, 0, 10);
  for (int i = 0; i < 10; i++) {
    ASSERT_EQ(ram->memory[i], ram->memory[i + 42]);
  }
  ASSERT_EQ(ram->memory[42+10], 0);
  ASSERT_EQ(ram->memory[42-1], 0);
}

TEST(ram_test, jvcr_memset) {
  JvcrRam *ram = NewJvcrRam();
  u32 dest = 42;
  u32 len = 10;
  jvcr_memset(ram, dest, 128, len);
  for (int i = 0; i < len; i++) {
    ASSERT_EQ(128, ram->memory[i + dest]);
  }
  ASSERT_EQ(ram->memory[42+10], 0);
  ASSERT_EQ(ram->memory[42-1], 0);
}

TEST(ram_test, ram_peek_poke) {
  JvcrRam *ram = NewJvcrRam();
  jvcr_poke(ram, 42, 128);
  ASSERT_EQ(jvcr_peek(ram, 42), 128);
}