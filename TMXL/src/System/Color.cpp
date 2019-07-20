//
// Created by depish on 20.07.19.
//

#include "TMXL/System/Color.h"

namespace TMXL {

    const Color Color::Black(0, 0, 0);
    const Color Color::White(255, 255, 255);
    const Color Color::Red(255, 0, 0);
    const Color Color::Green(0, 255, 0);
    const Color Color::Blue(0, 0, 255);
    const Color Color::Yellow(255, 255, 0);
    const Color Color::Magenta(255, 0, 255);
    const Color Color::Cyan(0, 255, 255);
    const Color Color::Transparent(0, 0, 0, 0);
    const Color Color::Orange(255, 165, 0);
    const Color Color::Gold(255, 215, 0);
    const Color Color::Gray(128, 128, 128);
    const Color Color::Pink(155, 192, 203);
    const Color Color::Purple(128, 0, 128);

    bool operator==(const Color& left, const Color& right) {
        return left.r == right.r && left.g == right.g && left.b == right.b && left.a == right.a;
    }

    bool operator!=(const Color& left, const Color& right) {
        return !(left == right);
    }

    Color operator+(const Color& left, const Color& right) {
        return Color( std::min(left.r + right.r, 255)
                    , std::min(left.g + right.g, 255)
                    , std::min(left.b + right.b, 255)
                    , std::min(left.a + right.a, 255));
    }

    Color operator-(const Color& left, const Color& right) {
        return Color( std::max(left.r - right.r, 0)
                    , std::max(left.g - right.g, 0)
                    , std::max(left.b - right.b, 0)
                    , std::max(left.a - right.a, 0));
    }

    Color operator*(const Color& left, const Color& right) {
        return Color( left.r * right.r / 255
                    , left.g * right.g / 255
                    , left.b * right.b / 255
                    , left.a * right.a / 255);
    }

    Color& operator+=(Color& left, const Color& right) {
        return left = left + right;
    }

    Color& operator-=(Color& left, const Color& right) {
        return left = left - right;
    }

    Color& operator*=(Color& left, const Color& right) {
        return left = left * right;
    }

    Color::Color(std::uint8_t _r, std::uint8_t _g, std::uint8_t _b, std::uint8_t _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    Color::Color() {
        r = g = b = a = 255;
    }

}