#ifndef TMXL_IPARSER_H
#define TMXL_IPARSER_H

#include "TMXL/Map/NodeObject.h"

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
         * @brief virtual std::shared_ptr<TMEMap> getMap()
         * @details Возвращает структуру карты
         * @return
         */
        virtual std::shared_ptr<NodeObject> getRoot() = 0;

        /**
         * @brief void setFileName(const TLString_t& fileName)
         * @param fileName
         */
        void setFileName(const std::string& fileName) noexcept;

        /**
         * @brief const TLString_t& getFileName() const
         * @return
         */
        const std::string& getFileName() const noexcept;

    protected:
        std::string  mfileName;
    };

}

#endif // TMXL_IPARSER_H