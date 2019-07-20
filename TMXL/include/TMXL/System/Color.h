//
// Created by depish on 20.07.19.
//

#ifndef TMXL_COLOR_H
#define TMXL_COLOR_H

#include "TMXL/Config.h"

#include <cstdint>

namespace TMXL {

    struct Color {

        Color();
        Color(std::uint8_t _r, std::uint8_t _g, std::uint8_t _b, std::uint8_t _a = 255);

        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Blue;
        static const Color Green;
        static const Color Yellow;
        static const Color Magenta;
        static const Color Cyan;
        static const Color Transparent;

        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
        std::uint8_t a;
    };

    bool operator==(const Color& left, const Color& right);
    bool operator!=(const Color& left, const Color& right);
    // @todo: add operators +,-,*,/,+=,*=,-=,/=
}

#endif //TMXL_COLOR_H
