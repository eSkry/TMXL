#pragma once

/**
 * @details XML Структура карты описана в официальной документации Tiled Map Editor
 * url: https://doc.mapeditor.org/en/stable/reference/tmx-map-format/
 */

#include "TMXL/Map/TMENodes.h"

namespace TMXL {

    /**
     * @brief IParser class
     * @details This class declare interface for parsers.
     */
    class IParser {
    public:
        virtual ~IParser() = default;

        /**
         * @brief virtual bool run();
         * @details Функция запускает парсинг карты, в данной функции необходимо реализовать работу парсера
         * @return
         */
        virtual TMEMapPtr parse(const std::string& xmlData) = 0;
    };

}
