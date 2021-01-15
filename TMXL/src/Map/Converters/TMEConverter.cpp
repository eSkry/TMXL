#include "TMXL/Map/Converters/TMEConverter.h"

namespace TMXL {

    TMEConverter::TMEConverter() {
        mWalker.registerCallback("layer", [this](NodeObject& node, std::size_t thisId, std::size_t parentId){
            auto data = node.findChild("data");
            if (!data.second){
                return; // Is node incorrect
            }

            auto layer = std::make_shared<TMELayer>();
            const NodeObject *object = data.first;
            layer->name = object->name;
            layer->width = strToSize(object->attributes["width"]);

            LayerDataParser::load(object->content, layer->data, layer->width, layer->height);

            this->mLayers.push_back(layer);
        });
    }

    void TMEConverter::convert(std::shared_ptr<NodeObject> root) {
        mWalker.run(*root);
    }

}