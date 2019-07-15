#ifndef TMXL_IPARSER_H
#define TMXL_IPARSER_H

#include "TMXL/Config.h"
#include "TMXL/Map/TMEMap.h"

namespace TMXL {

    /**
     * @brief IParser class
     * @details This class declare interface for parsers.
     */
    class IParser {
    public:

        virtual ~IParser();

        /**
         * @brief virtual bool run();
         * @details Функция запускает парсинг карты, в данной функции необходимо реализовать работу парсера
         * @return
         */
        virtual bool parse() = 0;

        /**
         * @brief virtual std::shared_ptr<TMEMap> getMap()ж
         * @details Возвращает структуру карты
         * @return
         */
        virtual std::shared_ptr<TMEMap> getMap() = 0;

        /**
         * @brief void setFileName(const TLString_t& fileName) [NOEXCEPT]
         * @param fileName
         */
        void setFileName(const sf::String& fileName) _TMXL_NOEXCEPT;

        /**
         * @brief const TLString_t& getFileName() const [NOEXCEPT]
         * @return
         */
        const sf::String& getFileName() const _TMXL_NOEXCEPT;

    protected:
        sf::String  m_fileName;
    };

}

#endif // TMXL_IPARSER_H