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

    bool operator==(const Color& left, const Color& right) {
        return left.r == right.r && left.g == right.g && left.b == right.b && left.a == right.a;
    }

    bool operator!=(const Color& left, const Color& right) {
        return !(left == right);
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