//
// Created by depish on 17.07.19.
//

#include "TMXL/System/NodeObjectWalker.h"

namespace TMXL {

    void NodeObjectWalker::registerCallback(const sf::String &nodeName, CallbackType callback) {
        callbacks[nodeName] = std::move(callback);
    }

    void NodeObjectWalker::run(std::shared_ptr<NodeObject> node) {
		walk(node, 0, 0);
    }

	void NodeObjectWalker::walk(std::shared_ptr<NodeObject> node, TLSize_t thisId, TLSize_t parentId) {
		if (const sf::String& name = node->name; callbacks.find(name) != callbacks.end()) {
			callbacks[name](node, thisId, parentId);
		}
		for (auto it : node->childrens) {
			walk(it, /*gen new id with non collision*/-1, thisId);
		}
	}

    void NodeObjectWalker::clearCallbacks() {
        callbacks.clear();
    }

}