#ifndef TMXL_TMECONVERTER_H
#define TMXL_TMECONVERTER_H

#include "TMXL/Parsers/LayerDataParser.h"
#include "TMXL/Map/NodeObjectWalker.h"
#include "TMXL/Map/NodeObject.h"
#include "TMXL/Map/TMENodes.h"
#include "TMXL/TypeConvert.h"

#include <memory>
#include <vector>

namespace TMXL {

    // TODO: Вытащить 4
    //  layers, map, tilesets
    // TODO: Вытащить специфические параметры, анимацию и прочее
    class TMEConverter {
    public:

        TMEConverter();

        void convert(std::shared_ptr<NodeObject> root);

    private:
        NodeObjectWalker                            mWalker;
        std::vector<std::shared_ptr<TMELayer>>      mLayers;
    };

}

#endif //TMXL_TMECONVERTER_H
