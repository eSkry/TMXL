
#include "gtest/gtest.h"

#include "TMXL/TypeConvert.h"

TEST(tmxl_typeConvert_strToBoolCheck, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(strToBool("t"), true);
    ASSERT_EQ(strToBool("True"), true);
    ASSERT_EQ(strToBool("1"), true);

    ASSERT_EQ(strToBool("f", true), false);
    ASSERT_EQ(strToBool("False", true), false);
    ASSERT_EQ(strToBool("0", true), false);

    ASSERT_EQ(strToBool("q", true), true);
    ASSERT_EQ(strToBool("e", false), false);
    ASSERT_EQ(strToBool("e"), false);
}

TEST(tmxl_typeConvert_charToUint8, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(charToUint8('1', '1'), std::uint8_t(0b00010001));
    ASSERT_EQ(charToUint8('3', '1'), std::uint8_t(0b00110001));
    ASSERT_EQ(charToUint8('F', 'F'), std::uint8_t(0b11111111));
    ASSERT_EQ(charToUint8('A', '0'), std::uint8_t(0b10100000));
    ASSERT_EQ(charToUint8('0', '0'), std::uint8_t(0b00000000));
}

TEST(tmxl_typeConvert_strToColorARGB, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(TMXL::Color::Black, strToColorARGB("#FF000000")); // AARRGGBB
    ASSERT_EQ(TMXL::Color::Black, strToColorARGB("FF000000"));

    ASSERT_EQ(TMXL::Color::Black, strToColorARGB("000000")); // RRGGBB
    ASSERT_EQ(TMXL::Color::Black, strToColorARGB("#000000"));

    ASSERT_EQ(TMXL::Color::White, strToColorARGB("#FFFFFF"));
    ASSERT_EQ(TMXL::Color::White, strToColorARGB("FFFFFF"));

    ASSERT_EQ(TMXL::Color::Red, strToColorARGB("#FF0000"));
    ASSERT_EQ(TMXL::Color::Red, strToColorARGB("FF0000"));

    ASSERT_EQ(TMXL::Color::Red, strToColorARGB("#FFFF0000"));
    ASSERT_EQ(TMXL::Color::Red, strToColorARGB("FFFF0000"));

    ASSERT_EQ(TMXL::Color::Green, strToColorARGB("FF00FF00"));

    ASSERT_EQ(TMXL::Color::Blue, strToColorARGB("FF0000FF"));
    ASSERT_EQ(TMXL::Color::Blue, strToColorARGB("0000FF"));

    // RETURN DEFAULT
    ASSERT_EQ(TMXL::Color(), strToColorARGB(""));
    ASSERT_EQ(TMXL::Color(), strToColorARGB("df"));
    ASSERT_EQ(TMXL::Color(), strToColorARGB("sdfgs"));
}

TEST(tmxl_typeConvert_colorToStr, test_eq){
    using namespace TMXL;
    ASSERT_STREQ(colorToStringARGB(TMXL::Color::Blue).c_str(), "#ff0000ff");
    ASSERT_STREQ(colorToStringARGB(TMXL::Color::Red).c_str(), "#ffff0000");
}

TEST(tmxl_typeConvert_intToBool, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(intToBool(0), false);
    ASSERT_EQ(intToBool(1), true);
    ASSERT_EQ(intToBool(2341), true);
    ASSERT_EQ(intToBool(-1), false);
}

TEST(tmxl_typeConvert_boolToInt, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(boolToInt(true), 1);
    ASSERT_EQ(boolToInt(false), 0);
}

TEST(tmxl_typeCinvert_boolToString, test_eq) {
    using namespace TMXL;
    ASSERT_STREQ(boolToString(true).c_str(), "true");
    ASSERT_STREQ(boolToString(false).c_str(), "false");
}

TEST(tmxl_typeConvert_strToInt, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(strToInt("15"), 15);
    ASSERT_EQ(strToInt("6342"), 6342);
    ASSERT_EQ(strToInt("-421314"), -421314);
}

TEST(tmxl_typeConvert_colorToInt, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(colorToInt(TMXL::Color::Black), 0xFF000000);
    ASSERT_EQ(colorToInt(TMXL::Color::White), 0xFFFFFFFF);
    ASSERT_EQ(colorToInt(TMXL::Color::Red), 0xFFFF0000);
    ASSERT_EQ(colorToInt(TMXL::Color::Green), 0xFF00FF00);
    ASSERT_EQ(colorToInt(TMXL::Color::Blue), 0xFF0000FF);
    ASSERT_EQ(colorToInt(TMXL::Color::Transparent), 0x00000000);
}

TEST(tmxl_typeConvert_intToColor, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(intToColor(0xFF000000), TMXL::Color::Black);
    ASSERT_EQ(intToColor(0xFFFFFFFF), TMXL::Color::White);
    ASSERT_EQ(intToColor(0xFFFF0000), TMXL::Color::Red);
    ASSERT_EQ(intToColor(0xFF00FF00), TMXL::Color::Green);
    ASSERT_EQ(intToColor(0xFF0000FF), TMXL::Color::Blue);
    ASSERT_EQ(intToColor(0x00000000), TMXL::Color::Transparent);
}
