#include "TMXL/Parsers/TMXParser.h"

namespace TMXL {

    bool TMXParser::parse() {
        if (m_fileName.isEmpty()){
            return false;
        }

        using pugi::xml_parse_result;
        using pugi::xml_document;
        using pugi::xml_node;

        xml_document        l_document;
        xml_parse_result    l_result = l_document.load_file(m_fileName.toAnsiString().c_str());

        if (!l_result){
            tmxlDebug(l_result.description());
            return false;
        }

        xml_node mapNode = l_document.child("Map");
        std::shared_ptr<TMEMap> pRootNode = parseMap(&mapNode);

        xml_node tilesetNode = mapNode.child("tileset");
//        parseTilesetNode(&tilesetNode, pRootNode);

        return true;
    }

    std::shared_ptr<TMEMap> TMXParser::parseMap(pugi::xml_node *pMapNode) {
        if (pMapNode == nullptr) {
            tmxlDebug("Map node is not exists")
            return nullptr;
        }

        m_tmeMap = std::make_shared<TMEMap>();

        m_tmeMap->mapSize.x = static_cast<TLSize_t>(pMapNode->attribute("width").as_ullong(0));
        m_tmeMap->mapSize.y = static_cast<TLSize_t>(pMapNode->attribute("height").as_ullong(0));
        m_tmeMap->tileSize.x = static_cast<TLSize_t>(pMapNode->attribute("tilewidth").as_ullong(0));
        m_tmeMap->tileSize.y = static_cast<TLSize_t>(pMapNode->attribute("tileheight").as_ullong(0));
        m_tmeMap->backgroundColor = strToColorARGB(pMapNode->attribute("backgroundcolor").as_string());
        m_tmeMap->nextObjectId = static_cast<TLSize_t>(pMapNode->attribute("nextobjectid").as_ullong(0));
        m_tmeMap->nextLayerId = static_cast<TLSize_t>(pMapNode->attribute("nextlayerid").as_ullong(0));
        m_tmeMap->renderOrder = spotRenderOrder(pMapNode->attribute("renderorder").as_string());
        m_tmeMap->mapOrientation = spotMapOrientation(pMapNode->attribute("orientation").as_string());
        m_tmeMap->staggerAxis = pMapNode->attribute("staggeraxis").as_string("-")[0];
        m_tmeMap->staggerIndex = pMapNode->attribute("staggerindex").as_string("-")[0];
        m_tmeMap->hexSideLength = static_cast<TLSize_t>(pMapNode->attribute("hexsidelength").as_ullong(0));

        {
            pugi::xml_node properties = pMapNode->child("properties");
            parseProperties(&properties, m_tmeMap->properties);
        }

        pugi::xml_node node = pMapNode->first_child();
        while (node){
            sf::String nodeName = node.name();
            if ( compare(nodeName, "tileset") ) {

            } else if (compare(nodeName, "image", StringComparison::IgnoreCase)) {

            } else if (compare(nodeName, "terraintypes", StringComparison::IgnoreCase)) {

            } else if (compare(nodeName, "tile", StringComparison::IgnoreCase)) {

            } else if (compare(nodeName, "wangsets", StringComparison::IgnoreCase)) {

            }

            node = node.next_sibling();
        }

        //TODO: Парсинг специфичных для данного загрузчика возможностей
        return m_tmeMap;
    }

    void TMXParser::parseTileset(pugi::xml_node *pTilesetNode, std::shared_ptr<TMEMap> pMap) {
        if (pTilesetNode == nullptr) {
            return;
        }

        auto tileset = std::make_shared<TMETileset>();
        tileset->firstGID = pTilesetNode->attribute("firstgid").as_ullong();
        tileset->source = pTilesetNode->attribute("source").as_string();

//        auto temp = std::make_shared<MapNode>(pParent);
//        fillAttributes(pTilesetNode, temp);
    }

    std::shared_ptr<TMEMap> TMXParser::getMap() {
        return m_tmeMap;
    }

    TMXParser::TMXParser() {
        m_tmeMap = std::make_shared<TMEMap>();
    }

    MapRenderOrder TMXParser::spotRenderOrder(const sf::String &str) const {
        if (str == "right-down")    return MapRenderOrder::RightDown;
        if (str == "right-up")      return MapRenderOrder::RightUp;
        if (str == "left-down")     return MapRenderOrder::LeftDown;
        if (str == "left-up")       return MapRenderOrder::LeftUp;

        return MapRenderOrder::Undefined;
    }

    MapOrientation TMXParser::spotMapOrientation(const sf::String &str) const {
        if (str == "hexagonal")      return MapOrientation::Hexagonal;
        if (str == "orthogonal")     return MapOrientation::Orthogonal;
        if (str == "isometric")      return MapOrientation::Isometric;
        if (str == "staggered")      return MapOrientation::Staggered;

        return MapOrientation::Undefined;
    }

    void TMXParser::parseAttributes(pugi::xml_node *pNodeWithAttributes, std::map<sf::String, TMXLType> &to) _TMXL_NOEXCEPT {
        if (pNodeWithAttributes == nullptr) return;

        for (auto & pNodeWithAttribute : *pNodeWithAttributes){
            TMXLType temp;
            temp = pNodeWithAttribute.value();
            to.insert({ pNodeWithAttribute.name(), temp });
        }
    }

    void TMXParser::parseProperties(pugi::xml_node *pNodeProperties, std::vector<TMEProperty>& vectorTo) _TMXL_NOEXCEPT {
        if (pNodeProperties == nullptr) return;

        for (auto & pNodePropertie : *pNodeProperties){
            TMEProperty temp;
            temp.name = pNodePropertie.attribute("name").as_string();
            temp.type = stringToType(pNodePropertie.attribute("type").as_string());
            temp.value = pNodePropertie.attribute("value").as_string();
            vectorTo.push_back(temp);
        }
    }

    void TMXParser::parseImage(pugi::xml_node *pNodeImage, std::shared_ptr<TMEMap> map) _TMXL_NOEXCEPT {
        auto temp = std::make_shared<TMEImage>();
        temp->trans =  strToColorARGB(pNodeImage->attribute("trans").as_string());
        temp->size.x = pNodeImage->attribute("width").as_uint();
        temp->size.y = pNodeImage->attribute("height").as_uint();

        sf::String source = pNodeImage->attribute("source").as_string();
        temp->image = std::make_shared<sf::Image>();
        temp->image->loadFromFile(source);

        //map->images[source] = temp;
    }

}