#include <gtest/gtest.h>

#ifdef __cplusplus
extern "C" {
#endif
#include <jvcr_ecm_01/fonts.h>
#ifdef __cplusplus
}  // End of extern "C" block
#endif

TEST(fonts_test, default_fonts) {
  EXPECT_EQ(4, DEFAULT_FONT[0].lines[0]);
  EXPECT_EQ(4, DEFAULT_FONT[0].lines[7]);
  EXPECT_EQ(8, DEFAULT_FONT[1].lines[0]);
  EXPECT_EQ(8, DEFAULT_FONT[1].lines[7]);
}