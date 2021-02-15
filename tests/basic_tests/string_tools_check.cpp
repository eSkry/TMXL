#include "gtest/gtest.h"

#include "TMXL/System/StringTools.h"

TEST(tmxl_stringTools_compare, test_eq) {
    using namespace TMXL;

    ASSERT_EQ(compare("val", "val"), true);
    ASSERT_EQ(compare("val", "Val"), false);

    ASSERT_EQ(compare("val", "val", StringComparison::IgnoreCase), true);
    ASSERT_EQ(compare("val", "VAL", StringComparison::IgnoreCase), true);
}

TEST(tmxl_stringTools_compareChar, test_eq) {
    using namespace TMXL;

    ASSERT_EQ(compare("val", "val", StringComparison::Normal), true);
    ASSERT_EQ(compare("val", "vall", StringComparison::Normal), false);
    ASSERT_EQ(compare("val", "VAL", StringComparison::Normal), false);

    ASSERT_EQ(compare("val", "VAL", StringComparison::IgnoreCase), true);
    ASSERT_EQ(compare("Val", "val", StringComparison::IgnoreCase), true);
    ASSERT_EQ(compare("VAL", "value", StringComparison::IgnoreCase), false);
}

TEST(tmxl_stringTools_endsWith, test_eq) {
    using namespace TMXL;

    std::string str = "hello TMXL test!";
    ASSERT_EQ(stringEndsWith(str, "test!"), true);
    ASSERT_EQ(stringEndsWith(str, "test"), false);

    ASSERT_EQ(stringEndsWith("TMXL", "XL"), true);
    ASSERT_EQ(stringEndsWith("TMXL", "MX"), false);

    ASSERT_EQ(stringEndsWith(str, str), true);
}
