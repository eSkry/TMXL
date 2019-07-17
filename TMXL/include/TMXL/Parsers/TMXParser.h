#ifndef TMXL_TMXPARSER_H
#define TMXL_TMXPARSER_H

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

namespace TMXL {

    class TMXParser : public IParser {
    public:
        bool parse() override;

        TMXParser();

        /**
         * @brief Возвращает карту
         * @return
         */
        std::shared_ptr<NodeObject> getRoot() override;

    protected:

        void parseNode(pugi::xml_node *pNode, std::shared_ptr<NodeObject> pNodeObject);

        void parseAttributes(pugi::xml_node *pNodeWithAttributes, std::shared_ptr<NodeObject> pToObject) _TMXL_NOEXCEPT;

    private:
        std::shared_ptr<NodeObject>      mRootNode;
    };

}

#endif //TMXL_TMXPARSER_H
