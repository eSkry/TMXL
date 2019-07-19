#ifndef TMXL_TMENODE_H
#define TMXL_TMENODE_H

#include "TMXL/System/ResourceManager.h"
#include "TMXL/TMXLType.h"
#include "TMXL/Config.h"
#include "TMXL/Tools.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>

#include <vector>
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

    /**
     * @details TMEProperty - Структура хранащая одну единица параметра в разделе properties
     */
    struct TMEProperty {
        sf::String              name;
        TMXLTypes               type;
        TMXLType                value;
    };

    struct TMEImage {
        sf::Color                   trans;
        sf::Vector2u                size;
        std::shared_ptr<sf::Image>  image;
    };

    struct TMETileset {

        TMETileset() { image = nullptr; }
        ~TMETileset() { if (image) delete image; }

        sf::Image*              image;
        sf::String              source;
        sf::String              name;
        std::size_t             firstGID;
        sf::Vector2u            tileSize;
        int                     spacing;
        int                     marign;
        std::size_t             tileCount;
        std::size_t             columns;
    };

    class Tilesets : public std::map<sf::String, std::shared_ptr<TMETileset>> {
    public:

    private:
    };

    /**
     * @details TMEMap - Структура хранящая основную информацию карты.
     * staggerIndex хранит вместо строки со значением even или odd, первые символы этой строки.
     *              e = even
     *              o = odd
     */
    struct TMEMap {
        sf::Vector2u            mapSize;
        MapOrientation          mapOrientation        = MapOrientation::Undefined;
        MapRenderOrder          renderOrder           = MapRenderOrder::Undefined;

        sf::Vector2u            tileSize;
        sf::Color               backgroundColor       = sf::Color::White;
        TLSize_t                nextObjectId          = 0;
        TLSize_t                nextLayerId           = 0;
        TLSize_t                hexSideLength         = 0;
        TLSize_t                tileWidth             = 0;
        TLSize_t                tileHeight            = 0;
        char                    staggerIndex          = '-';
        char                    staggerAxis           = '-';

        //ResourceManager<TMEImage>   images            = ResourceManager<TMEImage>::

        Tilesets                                        tilesets;
        std::vector<TMEProperty>                        properties;
    };

}

#endif //TMXL_TMENODE_H
