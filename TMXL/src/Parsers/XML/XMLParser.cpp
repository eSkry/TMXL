#include "TMXL/Parsers/XML/XMLParser.h"
#include <pugixml.hpp>

#include <iostream>

#include "TMXL/TypeConvert.h"

namespace {

    /**
     * Синтаксический сахар для извлечения значений из строковых атрибутов
     * @tparam T
     */
    template <typename T>
    struct AttributeByTypeGetter {
        T operator()(pugi::xml_attribute& attr) {
            return T{}; // Заглушка; Эта функция не должна никогда вызываться!
        }
    };

    template <>
    struct AttributeByTypeGetter<std::size_t> {
        std::size_t operator()(pugi::xml_attribute& attr) {
            return attr.as_uint();
        }
    };

    template<>
    struct AttributeByTypeGetter<std::string> {
        std::string operator()(pugi::xml_attribute& attr) {
            return attr.as_string();
        }
    };

    template<>
    struct AttributeByTypeGetter<double> {
        double operator()(pugi::xml_attribute& attr) {
            return attr.as_double();
        }
    };

    template<>
    struct AttributeByTypeGetter<int> {
        int operator()(pugi::xml_attribute& attr) {
            return attr.as_int();
        }
    };

    template<>
    struct AttributeByTypeGetter<bool> {
        bool operator()(pugi::xml_attribute& attr) {
            std::string str = attr.as_string();
            return TMXL::strToBool(str);
        }
    };

    template<>
    struct AttributeByTypeGetter<char> {
        char operator()(pugi::xml_attribute& attr) {
            std::string str = attr.as_string();
            if (!str.empty())
                return str[0];

            return '-';
        }
    };

    template<>
    struct AttributeByTypeGetter<TMXL::TMXLTypes> {
        TMXL::TMXLTypes operator()(pugi::xml_attribute& attr) {
            std::string str = attr.as_string();
            return TMXL::stringToType(str);
        }
    };

    template<>
    struct AttributeByTypeGetter<TMXL::MapOrientation> {
        TMXL::MapOrientation operator()(pugi::xml_attribute& attr) {
            std::string orientation = attr.as_string();
            return TMXL::strToMapOrientation(orientation);
        }
    };

    template<>
    struct AttributeByTypeGetter<TMXL::MapRenderOrder> {
        TMXL::MapRenderOrder operator()(pugi::xml_attribute& attr) {
            std::string order = attr.as_string();
            return TMXL::strToMapRenderOrder(order);
        }
    };

    template <>
    struct AttributeByTypeGetter<TMXL::ObjectAlignment> {
        TMXL::ObjectAlignment operator()(pugi::xml_attribute& attr) {
            std::string alignment = attr.as_string();
            return TMXL::strToObjectAlignment(alignment);
        }
    };

    template <>
    struct AttributeByTypeGetter<TMXL::TileRenderSize> {
        TMXL::TileRenderSize operator()(pugi::xml_attribute& attr) {
            std::string size = attr.as_string();
            return TMXL::strToTileRenderSize(size);
        }
    };

    template <>
    struct AttributeByTypeGetter<TMXL::FillMode> {
        TMXL::FillMode operator()(pugi::xml_attribute& attr) {
            std::string mode = attr.as_string();
            return TMXL::strToFillMode(mode);
        }
    };

    template<typename T>
    void getAttribute(const std::string& name, pugi::xml_node& node, T& val) {
        auto attr = node.attribute(name.c_str());

        if (attr) {
            AttributeByTypeGetter<T> getter;
            val = getter(attr);
        }
    }

    /**
     * @brief Парсит xml элемент <tileoffset>
     * @param propertyTileOffset
     * @param tileOffset
     */
    void parseTileOffset(pugi::xml_node& propertyTileOffset, TMXL::TMETileOffset& tileOffset) {
        getAttribute("x", propertyTileOffset, tileOffset.x);
        getAttribute("y", propertyTileOffset, tileOffset.y);
    }

    /**
     * @brief Парсит xml элемент <wangset>
     * @param wangsetNode
     * @param wangset
     */
    void parseWangset(pugi::xml_node& wangsetNode, TMXL::TMEWangset& wangset) {
        getAttribute("name", wangsetNode, wangset.name);
        getAttribute("class", wangsetNode, wangset.class_name);
        getAttribute("tile", wangsetNode, wangset.tile);

        // TODO: parse properties, wangcolor, wangtile
    }

    /**
     * @brief Парсит xml элемент <transformations>
     * @param transformationsNode
     * @param transformations
     */
    void parseTransformations(pugi::xml_node& transformationsNode, TMXL::TMETransformations& transformations) {
        getAttribute("hflip", transformationsNode, transformations.hFlip);
        getAttribute("vflip", transformationsNode, transformations.vFlip);
        getAttribute("rotate", transformationsNode, transformations.rotate);
        getAttribute("preferuntransformed", transformationsNode, transformations.preferuntransformed);
    }

    /**
     * @brief Парсит xml элемент <wangtile>
     * @param wangtileNode
     * @param wangtile
     */
    void parseWangtile(pugi::xml_node& wangtileNode, TMXL::TMEWangTile& wangtile) {
        getAttribute("tileid", wangtileNode, wangtile.tileid);
        getAttribute("wangid", wangtileNode, wangtile.wangid);
    }

    /**
     * @brief Парсит xml элемент <grid>
     * @param gridNode
     * @param grid
     */
    void parseGrid(pugi::xml_node& gridNode, TMXL::TMEGrid& grid) {
        getAttribute("orientation", gridNode, grid.orientation);
        getAttribute("width", gridNode, grid.width);
        getAttribute("height", gridNode, grid.height);
    }

    /**
     * @brief Парсит xml элемент <property/>
     * @param propertyNode
     * @param propertyList
     */
    void parseProperty(pugi::xml_node& propertyNode, TMXL::TMEProperties& propertyList) {
        TMXL::TMEProperty prop;

        getAttribute("name", propertyNode, prop.name);
        getAttribute("value", propertyNode, prop.value);

        auto type = propertyNode.attribute("type");
        if (type) // Для типа string атрибут type в xml не устанавливается.
            getAttribute("type", propertyNode, prop.type);
        else
            prop.type = TMXL::TMXLTypes::String_e;

        propertyList.push_back(prop);
    }

    /**
     * @brief Парсит xml элемент <properties>
     * @param properiesNode
     * @param propertyList
     */
    void parseProperties(pugi::xml_node& properiesNode, TMXL::TMEProperties& propertyList) {
        if (std::string(properiesNode.name()) != "properties")
            return;

        for (auto it : properiesNode.children())
            parseProperty(it, propertyList);
    }

    /**
     * @brief Парсит xml элемент <image>
     * @param imageNode
     * @param image
     */
    void parseImage(pugi::xml_node& imageNode, TMXL::TMEImage& image) {
        getAttribute("height", imageNode, image.height);
        getAttribute("width", imageNode, image.width);
        getAttribute("source", imageNode, image.source);
        getAttribute("trans", imageNode, image.transparentMask);

        // TODO: can contains at most one:  parse it! <data>
    }

    /**
     * Парсит xml элемент <tileset>
     * @param tilesetNode
     * @param tileset
     */
    void parseTileset(pugi::xml_node& tilesetNode, TMXL::TMETileset& tileset) {
        getAttribute("firstgid", tilesetNode, tileset.firstGID);
        getAttribute("source", tilesetNode, tileset.source);
        getAttribute("name", tilesetNode, tileset.name);
        getAttribute("tilewidth", tilesetNode, tileset.tileWidth);
        getAttribute("tileheight", tilesetNode, tileset.tileHeight);
        getAttribute("spacing", tilesetNode, tileset.spacing);
        getAttribute("margin", tilesetNode, tileset.margin);
        getAttribute("tilecount", tilesetNode, tileset.tileCount);
        getAttribute("columns", tilesetNode, tileset.columns);
        getAttribute("objectalignment", tilesetNode, tileset.objectAlignment);
        getAttribute("tilerendersize", tilesetNode, tileset.tileRenderSize);
        getAttribute("fillmode", tilesetNode, tileset.fillMode);

        // TODO: Parse: image, tileoffset, grid, properties, terraintypes, wangsets, transformations
    }

    /**
     * Парсит Парсит xml элемент <map>
     * @param mapNode
     * @param root
     */
    void parseNodeMap(pugi::xml_node& mapNode, TMXL::TMEMapPtr root) {
        getAttribute("width", mapNode, root->width);
        getAttribute("height", mapNode, root->height);
        getAttribute("orientation", mapNode, root->orientation);
        getAttribute("renderorder", mapNode, root->renderOrder);
        getAttribute("tilewidth", mapNode, root->tileWidth);
        getAttribute("tileheight", mapNode, root->tileHeight);
        getAttribute("compressionlevel", mapNode, root->compressionLevel);
        getAttribute("hexsidelength", mapNode, root->hexSideLength);
        getAttribute("staggeraxis", mapNode, root->staggerAxis);
        getAttribute("staggerindex", mapNode, root->staggerIndex);
        getAttribute("parallaxoriginx", mapNode, root->parallaxOriginX);
        getAttribute("parallaxoriginy", mapNode, root->parallaxOriginY);
        getAttribute("backgroundcolor", mapNode, root->backgroundColor);
        getAttribute("nextlayerid", mapNode, root->nextLayerId);
        getAttribute("nextobjectid", mapNode, root->nextObjectId);
        getAttribute("infinite", mapNode, root->infinite);

        auto properties = mapNode.child("properties");
        if (properties)
            for (auto it : properties.children())
                parseProperty(it, root->properties);

        // TODO: parse xml node <editorsettings> https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#tmx-editorsettings
    }

} // namespace Anon

namespace TMXL {

    TMEMapPtr XMLParser::parse(const std::string &xmlData) {
        std::stringstream data_stream;
        data_stream << xmlData;
        pugi::xml_document xml_doc;

        if (!xml_doc.load(data_stream))
            return nullptr;

        auto root = std::make_shared<TMEMap>();
        pugi::xml_node map = xml_doc.child("map");

        parseNodeMap(map, root);

        return root;
    }

} // namespace TMXL
