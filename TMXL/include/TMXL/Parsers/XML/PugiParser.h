#ifndef TMXL_PUGIPARSER_H
#define TMXL_PUGIPARSER_H

/**
 * @details XML Структура карты описана в оффициальной документации Tiled Map Editor
 * url: https://doc.mapeditor.org/en/stable/reference/tmx-map-format/
 */

#include "TMXL/System/StringTools.h"
#include "TMXL/Parsers/IParser.h"
#include "TMXL/Map/NodeObject.h"
#include "TMXL/System/Logger.h"
#include "TMXL/TypeConvert.h"

#include "pugixml.hpp"

#include <memory>
#include <string>

namespace TMXL {

    class PugiParser : public IParser {
    public:

        PugiParser();
        explicit PugiParser(const std::string& fileName);

        /**
         * @brief Start parsing file
         * @return result parse
         */
        bool parse() override;

        /**
         * @brief Возвращает карту
         * @return
         */
        std::shared_ptr<NodeObject> getRoot() noexcept override;

        /**
         * @brief Clean loaded data on parser
         * @details Не удаляет дерево объектов если на него есть другие ссылки
         */
        void clean() noexcept override;

    protected:

        void parseNode(pugi::xml_node *pNode, NodeObject& pNodeObject) noexcept;

        void parseAttributes(pugi::xml_node *pNodeWithAttributes, NodeObject& pToObject) noexcept;

    private:
        std::shared_ptr<NodeObject>      mRootNode;
        std::size_t mIdCounter;
    };

}

#endif //TMXL_PUGIPARSER_H
