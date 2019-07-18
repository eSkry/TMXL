//
// Created by depish on 17.07.19.
//

#include "TMXL/System/NodeObjectWalker.h"

namespace TMXL {

    void NodeObjectWalker::registerCallback(const sf::String &nodeName, CallbackType callback) {
        callbacks[nodeName] = std::move(callback);
    }

    void NodeObjectWalker::run(std::shared_ptr<NodeObject> node) {
        if (const sf::String& name = node->name; callbacks.find(name) != callbacks.end()){
            callbacks[name](node);
        }
        for (auto it : node->childrens){
            run(it);
        }
    }

    void NodeObjectWalker::clearCallbacks() {
        callbacks.clear();
    }

}