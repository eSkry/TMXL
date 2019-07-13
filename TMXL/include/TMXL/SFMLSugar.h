#ifndef TMXL_SFMLSUGAR_H
#define TMXL_SFMLSUGAR_H

#include "Config.h"

namespace TMXL {

    /**
     * @details Конвертирует sf::String в const char *
     * @param str
     * @return
     */
    static const char* sfStringToChar(const sf::String &str) _TMXL_NOEXCEPT {
        return str.toAnsiString().c_str();
    }

}

#endif //TMXL_SFMLSUGAR_H
