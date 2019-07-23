#ifndef TMXL_TMENODE_H
#define TMXL_TMENODE_H

#include "TMXL/System/Color.h"
#include "TMXL/Tools.h"

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

    struct ITmeBase { };

    /**
     * @details TMEProperty - Структура хранащая одну единица параметра в разделе properties
     */
    struct TMEProperty : ITmeBase {
        std::string            name;
        std::string            value;
        TMXLTypes              type;
    };

    /**
     * @brief Информация о изображении 
     */
    struct TMEImage : ITmeBase {
        Color                  transparentMask;
        std::size_t            width        = 0;
        std::size_t            height       = 0;
        std::string            image;
    };

    struct TMETileset : ITmeBase {
        std::string            source;
        std::string            name;
        std::size_t            firstGID     = 0;
        std::size_t            tileWidth    = 0;
        std::size_t            tileHeight   = 0;
        std::size_t            tileCount    = 0;
        std::size_t            columns      = 0;
        int                    spacing      = 0;
        int                    marign       = 0;
    };
    
    /**
     * @brief TMELayer - Содержит параметры слоя и список ID тайлов
     */
    struct TMELayer : ITmeBase {
        std::size_t                             id      = 0;
        std::size_t                             width   = 0;
        std::size_t                             height  = 0;
        std::size_t                             offsetx = 0;
        std::size_t                             offsety = 0;
        float                                   opacity = 1;
        int                                     x       = 0;
        int                                     y       = 0;
        bool                                    visible = true;
        std::string                             name;
        std::vector<std::size_t>                data;
        std::map<std::string, TMEProperty>      properties;
    };

    /**
     * @details TMEMap - Структура хранящая основную информацию карты.
     * staggerIndex хранит вместо строки со значением even или odd, первые символы этой строки.
     *              e = even
     *              o = odd
     */
    struct TMEMap : ITmeBase {
        std::size_t            mapWidth              = 0;
        std::size_t            mapHeight             = 0;
        MapOrientation         mapOrientation        = MapOrientation::Undefined;
        MapRenderOrder         renderOrder           = MapRenderOrder::Undefined;

        Color                  backgroundColor       = Color::White;
        std::size_t            nextObjectId          = 0;
        std::size_t            nextLayerId           = 0;
        std::size_t            hexSideLength         = 0;
        std::size_t            tileWidth             = 0;
        std::size_t            tileHeight            = 0;
        char                   staggerIndex          = '-';
        char                   staggerAxis           = '-';

        std::vector<TMEProperty>                       properties;
    };

}

#endif //TMXL_TMENODE_H
