#pragma once

#include "TMXL/System/Color.h"
#include "TMXL/Tools.h"

#include <memory>
#include <vector>
#include <string>
#include <map>

namespace TMXL {

    enum class MapOrientation {
        Undefined = -1,
        Orthogonal,
        Isometric,
        Staggered,
        Hexagonal
    };

    enum class MapRenderOrder {
        Undefined = -1,
        RightDown,
        RightUp,
        LeftDown,
        LeftUp
    };

    enum class ObjectAlignment {
        Unspecified,
        TopLeft,
        Top,
        TopRight,
        Left,
        Center,
        Right,
        BottomLeft,
        Bottom,
        BottomRight
    };

    enum class TileRenderSize {
        Tile,
        Grid
    };

    enum class FillMode {
        Stretch,
        PreserveAspectFit
    };

    /**
     * @details TMEProperty - Структура хранящая одну единица параметра в разделе properties
     */
    struct TMEProperty {
        std::string name;
        std::string value;
        TMXLTypes type;
    };
    using TMEProperties = std::vector<TMEProperty>;

    struct TMEWangColor {
        std::string name;
        std::string class_name;
        std::string color;
        int tile;
        int probability;

        TMEProperties properties;
    };
    using TMEWangColors = std::vector<TMEWangColor>;

    struct TMEWangTile {
        std::size_t tileid;
        std::size_t wangid;
    };
    using TMEWangTiles = std::vector<TMEWangTile>;

    struct TMEWangset {
        std::string name;
        std::string class_name;
        int tile;

        TMEProperties properties;
        TMEWangColors wangColors;
        TMEWangTiles wangTiles;
    };
    using TMEWangsets = std::vector<TMEWangset>;

    struct TMETransformations {
        bool hFlip = false;
        bool vFlip = false;
        double rotate = 0.0;
        int preferuntransformed = 0;
    };

    struct TMETileOffset {
        std::size_t x = 0;
        std::size_t y = 0;
    };

    struct TMEGrid {
        MapOrientation orientation;
        std::size_t width;
        std::size_t height;
    };

    /**
     * @brief Информация о изображении 
     */
    struct TMEImage {
        std::string transparentMask;
        std::size_t width = 0;
        std::size_t height = 0;
        std::string source;
    };
    using TMEImages = std::vector<TMEImage>;

    struct TMETileset {
        std::string source;
        std::string name;
        std::size_t firstGID = 0;
        std::size_t tileWidth = 0;
        std::size_t tileHeight = 0;
        std::size_t tileCount = 0;
        std::size_t columns = 0;
        ObjectAlignment objectAlignment = ObjectAlignment::BottomLeft;
        TileRenderSize tileRenderSize = TileRenderSize::Tile;
        FillMode fillMode = FillMode::Stretch;

        TMETileOffset tileOffset;
        TMEGrid grid;

        int spacing = 0;
        int margin = 0;
    };
    using TMETilesets = std::vector<TMETileset>;
    
    /**
     * @brief TMELayer - Содержит параметры слоя и список ID тайлов
     */
    struct TMELayer {
        std::size_t id = 0;
        std::size_t width = 0;
        std::size_t height = 0;
        std::size_t offsetx = 0;
        std::size_t offsety = 0;
        float opacity = 1;
        int x = 0;
        int y = 0;
        bool visible = true;
        std::string name;
        std::vector<std::size_t> data;
        std::map<std::string, TMEProperty> properties;
    };
    using TMELayers = std::vector<TMELayer>;

    /**
     * @details TMEMap - Структура хранящая основную информацию карты.
     * staggerIndex хранит вместо строки со значением even или odd, первые символы этой строки.
     *              e = even
     *              o = odd
     */
    struct TMEMap {
        std::size_t width = 0;
        std::size_t height = 0;
        MapOrientation orientation = MapOrientation::Undefined;
        MapRenderOrder renderOrder = MapRenderOrder::Undefined;

        std::string backgroundColor;
        std::size_t nextObjectId = 0;
        std::size_t nextLayerId = 0;
        std::size_t hexSideLength = 0;
        std::size_t tileWidth = 0;
        std::size_t tileHeight = 0;
        int compressionLevel = -1;
        int parallaxOriginX = 0;
        int parallaxOriginY = 0;
        char staggerIndex = '-';
        char staggerAxis = '-';
        bool infinite = false;

        TMEProperties properties;
    };
    using TMEMapPtr = std::shared_ptr<TMEMap>;

}
