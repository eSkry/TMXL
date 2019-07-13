
#include "gtest/gtest.h"

#include "TMXL/SFMLSugar.h"

TEST(tmxl_sfml_sugar_to_const_char_check, test_eq) {
    ASSERT_STREQ(TMXL::sfStringToChar({"Test string"}), "Test string");
}