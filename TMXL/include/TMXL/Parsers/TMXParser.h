#ifndef TMXL_TMXPARSER_H
#define TMXL_TMXPARSER_H

/**
 * @details XML Структура карты описана в оффициальной документации Tiled Map Editor
 * url: https://doc.mapeditor.org/en/stable/reference/tmx-map-format/
 */

#include "TMXL/System/StringTools.h"
#include "TMXL/TypeConvert.h"
#include "TMXL/Map/TMEMap.h"
#include "TMXL/TMXLType.h"
#include "TMXL/Config.h"
#include "IParser.h"

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
        std::shared_ptr<TMEMap> getMap() override;

    protected:

        /**
         * @details Парсит корневую ноду карты - map и возвращает указатель на объект содержащий данные карты.
         * @param pMapNode
         * @return
         */
        std::shared_ptr<TMEMap> parseMap(pugi::xml_node *pMapNode);

        static void parseTileset(pugi::xml_node *pTilesetNode, std::shared_ptr<TMEMap> pMap);

        /**
         * @details Принимает на вход ноду properties и вектор со строками по ссылке, парсит все properties
         * @param pNodeProperties
         * @param a_vectorTo
         */
        static void parseProperties(pugi::xml_node *pNodeProperties, std::vector<TMEProperty>& vectorTo) _TMXL_NOEXCEPT;

        static void parseAttributes(pugi::xml_node *pNodeWithAttributes, std::map<sf::String, TMXLType> &to) _TMXL_NOEXCEPT;

        static void parseImage(pugi::xml_node *pNodeImage, std::shared_ptr<TMEMap> map) _TMXL_NOEXCEPT;

        MapRenderOrder spotRenderOrder(const sf::String &str) const _TMXL_NOEXCEPT;
        MapOrientation spotMapOrientation(const sf::String& str) const _TMXL_NOEXCEPT;

    private:
        std::shared_ptr<TMEMap>      m_tmeMap;
    };

}

#endif //TMXL_TMXPARSER_H
