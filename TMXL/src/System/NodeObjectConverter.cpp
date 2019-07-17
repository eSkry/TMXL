//
// Created by depish on 17.07.19.
//

#include "TMXL/System/NodeObjectConverter.h"

namespace TMXL {

    void NodeObjectConverter::registerCallback(const sf::String &nodeName, CallbackType callback) {
        callbacks[nodeName] = std::move(callback);
    }

    void NodeObjectConverter::convert(std::shared_ptr<NodeObject> node) {
        if (const sf::String& name = node->name; callbacks.find(name) != callbacks.end()){
            callbacks[name](node);
        }
        for (auto it : node->childrens){
            convert(it);
        }
    }

    void NodeObjectConverter::clearCallbacks() {
        callbacks.clear();
    }

}