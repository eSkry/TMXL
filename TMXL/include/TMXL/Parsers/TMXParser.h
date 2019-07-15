#ifndef TMXL_TMXPARSER_H
#define TMXL_TMXPARSER_H

/**
 * @details XML Структура карты описана в оффициальной документации Tiled Map Editor
 * url: https://doc.mapeditor.org/en/stable/reference/tmx-map-format/
 */

#include "IParser.h"
#include "TMXL/TypeConvert.h"
#include "TMXL/Config.h"
#include "TMXL/Map/TMEMap.h"
#include "TMXL/TMXLType.h"
#include "TMXL/System/StringTools.h"

#include "pugixml.hpp"

#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

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
        std::shared_ptr<TMEMap> parseMapNode(pugi::xml_node *pMapNode);

        void parseTilesetNode(pugi::xml_node *pTilesetNode, std::shared_ptr<TMEMap> pParent);

//        void parseProperties(pugi::xml_node *pProperties, std::shared_ptr<MapNode> pParent);

        /**
         * @details Парсит и записывает все атрибуты в ноду.
         * @param pNodeFrom
         * @param pNodeTo
         */
//        void fillAttributes(pugi::xml_node *pNodeFrom, std::shared_ptr<MapNode> pNodeTo) _TMXL_NOEXCEPT;

        /**
         * @details Принимает на вход ноду properties и вектор со строками по ссылке, парсит все properties
         * @param pNodeProperties
         * @param a_vectorTo
         */
        void parseProperties(pugi::xml_node *pNodeProperties, std::vector<TMEProperty>& a_vectorTo);

        void getAttributes(pugi::xml_node *pNodeWithAttributes, std::map<sf::String, TMXLType>& to) _TMXL_NOEXCEPT;

        MapRenderOrder spotRenderOrder(const sf::String &str) const _TMXL_NOEXCEPT;
        MapOrientation spotMapOrientation(const sf::String& str) const _TMXL_NOEXCEPT;

    private:
        std::shared_ptr<TMEMap>      m_tmeMap;
    };

}

#endif //TMXL_TMXPARSER_H
