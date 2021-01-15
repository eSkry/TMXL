#include "TMXL/Map/Converters/TMEConverter.h"

namespace TMXL {

    TMEConverter::TMEConverter() {
        mWalker.registerCallback("layer", [this](NodeObject& node, std::size_t thisId, std::size_t parentId){
            NodeObject::NodeList dataList;
            node.findAllNodes("data", dataList);
            if (dataList.empty()){
                return; // Is node incorrect
            }

            auto layer = std::make_shared<TMELayer>();
            auto object = dataList[0];
            layer->name = object->name;
//            layer->width = strToSize(object->attributes["width"]);
            // TODO: допасить данные в структуру
            LayerDataParser::load(object->content, layer->data, layer->width, layer->height);

            this->mLayers.push_back(layer);
        });
    }

    void TMEConverter::convert(std::shared_ptr<NodeObject> root) {
        mWalker.run(*root);
    }

}