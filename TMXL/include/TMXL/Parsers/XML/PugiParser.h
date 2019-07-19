#ifndef TMXL_PUGIPARSER_H
#define TMXL_PUGIPARSER_H

/**
 * @details XML Структура карты описана в оффициальной документации Tiled Map Editor
 * url: https://doc.mapeditor.org/en/stable/reference/tmx-map-format/
 */

#include "TMXL/System/StringTools.h"
#include "TMXL/Parsers/IParser.h"
#include "TMXL/Map/NodeObject.h"
#include "TMXL/TypeConvert.h"
#include "TMXL/Config.h"

#include <SFML/System/String.hpp>

#include "pugixml.hpp"

#include <memory>
#include <string>

namespace TMXL {

    class PugiParser : public IParser {
    public:
        bool parse() override;

        PugiParser();

        /**
         * @brief Возвращает карту
         * @return
         */
        std::shared_ptr<NodeObject> getRoot() override;

    protected:

        void parseNode(pugi::xml_node *pNode, NodeObject& pNodeObject) noexcept;

        void parseAttributes(pugi::xml_node *pNodeWithAttributes, NodeObject& pToObject) noexcept;

    private:
        std::shared_ptr<NodeObject>      mRootNode;
    };

}

#endif //TMXL_PUGIPARSER_H
