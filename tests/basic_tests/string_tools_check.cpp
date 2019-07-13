//
// Created by depish on 08.06.19.
//

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

    ASSERT_EQ(compare("val", "val", 3, StringComparison::Normal), true);
    ASSERT_EQ(compare("val", "vall", 4, StringComparison::Normal), false);
    ASSERT_EQ(compare("val", "VAL", 3, StringComparison::Normal), false);

    ASSERT_EQ(compare("val", "VAL", 3, StringComparison::IgnoreCase), true);
    ASSERT_EQ(compare("Val", "val", 3, StringComparison::IgnoreCase), true);
    ASSERT_EQ(compare("VAL", "value", 5, StringComparison::IgnoreCase), false);
}