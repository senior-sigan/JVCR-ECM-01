#include "gtest/gtest.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <jvcr_ecm_01/machine.h>
#ifdef __cplusplus
}  // End of extern "C" block
#endif

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}