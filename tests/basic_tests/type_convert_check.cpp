
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
    ASSERT_EQ(charToUint8('1', '1'), sf::Uint8(0b00010001));
    ASSERT_EQ(charToUint8('3', '1'), sf::Uint8(0b00110001));
    ASSERT_EQ(charToUint8('F', 'F'), sf::Uint8(0b11111111));
    ASSERT_EQ(charToUint8('A', '0'), sf::Uint8(0b10100000));
    ASSERT_EQ(charToUint8('0', '0'), sf::Uint8(0b00000000));
}

TEST(tmxl_typeConvert_strToColorARGB, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(sf::Color::Black, strToColorARGB("#FF000000")); // AARRGGBB
    ASSERT_EQ(sf::Color::Black, strToColorARGB("FF000000"));

    ASSERT_EQ(sf::Color::Black, strToColorARGB("000000")); // RRGGBB
    ASSERT_EQ(sf::Color::Black, strToColorARGB("#000000"));

    ASSERT_EQ(sf::Color::White, strToColorARGB("#FFFFFF"));
    ASSERT_EQ(sf::Color::White, strToColorARGB("FFFFFF"));

    ASSERT_EQ(sf::Color::Red, strToColorARGB("#FF0000"));
    ASSERT_EQ(sf::Color::Red, strToColorARGB("FF0000"));

    ASSERT_EQ(sf::Color::Red, strToColorARGB("#FFFF0000"));
    ASSERT_EQ(sf::Color::Red, strToColorARGB("FFFF0000"));

    ASSERT_EQ(sf::Color::Green, strToColorARGB("FF00FF00"));

    ASSERT_EQ(sf::Color::Blue, strToColorARGB("FF0000FF"));
    ASSERT_EQ(sf::Color::Blue, strToColorARGB("0000FF"));

    // RETURN DEFAULT
    ASSERT_EQ(sf::Color(), strToColorARGB(""));
    ASSERT_EQ(sf::Color(), strToColorARGB("df"));
    ASSERT_EQ(sf::Color(), strToColorARGB("sdfgs"));
}

TEST(tmxl_typeConvert_colorToStr, test_eq){
    using namespace TMXL;
    ASSERT_STREQ(colorToStringARGB(sf::Color::Blue).toAnsiString().c_str(), "#ff0000ff");
    ASSERT_STREQ(colorToStringARGB(sf::Color::Red).toAnsiString().c_str(), "#ffff0000");
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
    ASSERT_STREQ(boolToString(true).toAnsiString().c_str(), "true");
    ASSERT_STREQ(boolToString(true, false).toAnsiString().c_str(), "t");
    ASSERT_STREQ(boolToString(true, true, "YES", "NO").toAnsiString().c_str(), "YES");
    ASSERT_STREQ(boolToString(true, false, "YES", "NO").toAnsiString().c_str(), "Y");

    ASSERT_STREQ(boolToString(false).toAnsiString().c_str(), "false");
    ASSERT_STREQ(boolToString(false, false).toAnsiString().c_str(), "f");
    ASSERT_STREQ(boolToString(false, true, "YES", "NO").toAnsiString().c_str(), "NO");
    ASSERT_STREQ(boolToString(false, false, "YES", "NO").toAnsiString().c_str(), "N");
}

TEST(tmxl_typeConvert_strToInt, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(strToInt("15"), 15);
    ASSERT_EQ(strToInt("6342"), 6342);
    ASSERT_EQ(strToInt("-421314"), -421314);
}

TEST(tmxl_typeConvert_colorToInt, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(colorToInt(sf::Color::Black), 0xFF000000);
    ASSERT_EQ(colorToInt(sf::Color::White), 0xFFFFFFFF);
    ASSERT_EQ(colorToInt(sf::Color::Red), 0xFFFF0000);
    ASSERT_EQ(colorToInt(sf::Color::Green), 0xFF00FF00);
    ASSERT_EQ(colorToInt(sf::Color::Blue), 0xFF0000FF);
    ASSERT_EQ(colorToInt(sf::Color::Transparent), 0x00000000);
}

TEST(tmxl_typeConvert_intToColor, test_eq) {
    using namespace TMXL;
    ASSERT_EQ(intToColor(0xFF000000), sf::Color::Black);
    ASSERT_EQ(intToColor(0xFFFFFFFF), sf::Color::White);
    ASSERT_EQ(intToColor(0xFFFF0000), sf::Color::Red);
    ASSERT_EQ(intToColor(0xFF00FF00), sf::Color::Green);
    ASSERT_EQ(intToColor(0xFF0000FF), sf::Color::Blue);
    ASSERT_EQ(intToColor(0x00000000), sf::Color::Transparent);
}
