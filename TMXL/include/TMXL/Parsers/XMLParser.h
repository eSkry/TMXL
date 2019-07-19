#ifndef TMXL_XMLPARSER_H
#define TMXL_XMLPARSER_H

/**
 * @details XML Структура карты описана в оффициальной документации Tiled Map Editor
 * url: https://doc.mapeditor.org/en/stable/reference/tmx-map-format/
 */

#include "TMXL/System/StringTools.h"
#include "TMXL/Map/NodeObject.h"
#include "TMXL/TypeConvert.h"
#include "TMXL/TMXLType.h"
#include "TMXL/Config.h"
#include "IParser.h"

#include <SFML/System/String.hpp>

#include "pugixml.hpp"

#include <memory>
#include <string>

namespace TMXL {

    class XMLParser : public IParser {
    public:
        bool parse() override;

        XMLParser();

        /**
         * @brief Возвращает карту
         * @return
         */
        std::shared_ptr<NodeObject> getRoot() override;

    protected:

        void parseNode(pugi::xml_node *pNode, std::shared_ptr<NodeObject> pNodeObject) noexcept;

        void parseAttributes(pugi::xml_node *pNodeWithAttributes, std::shared_ptr<NodeObject> pToObject) noexcept;

    private:
        std::shared_ptr<NodeObject>      mRootNode;
    };

}

#endif //TMXL_XMLPARSER_H
