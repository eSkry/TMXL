
#include "gtest/gtest.h"

#include "TMXL/Tools.h"

TEST(tmxl_tools_tolowercase_check, test_eq) {
    using namespace TMXL;
    ASSERT_STREQ(strToLowerCase("WwWwW").c_str(), "wwwww");
    ASSERT_STREQ(strToLowerCase("HellO, WorlD! =) 1234567890").c_str(), "hello, world! =) 1234567890");
    ASSERT_STREQ(strToLowerCase("AZ").c_str(), "az");
}

TEST(tmxl_tools_snn_check, test_eq) {
    using namespace TMXL;
    bool *_test = new bool();

    snn(_test, true);
    ASSERT_EQ(*_test, true);

    snn(_test, false);
    ASSERT_EQ(*_test, false);

    delete _test;
    _test = nullptr;

    snn(_test, true);
    ASSERT_EQ(_test, nullptr);
}

TEST(tmxl_tools_char_to_lower_case, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(charToLowerCase('A'), 'a');
    ASSERT_EQ(charToLowerCase('Z'), 'z');
    ASSERT_EQ(charToLowerCase('G'), 'g');
    ASSERT_EQ(charToLowerCase('0'), '0');
    ASSERT_EQ(charToLowerCase('9'), '9');
}