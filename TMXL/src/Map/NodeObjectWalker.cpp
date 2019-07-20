//
// Created by depish on 17.07.19.
//

#include "TMXL/Map/NodeObjectWalker.h"

namespace TMXL {

    void NodeObjectWalker::registerCallback(const std::string &nodeName, CallbackType callback) {
        callbacks[nodeName] = std::move(callback);
    }

    void NodeObjectWalker::run(NodeObject& node) {
		auto rootId = IDGenerator<GCategory::NODEOBJECTS>::getId();
		walk(node, rootId, rootId);
    }

	void NodeObjectWalker::walk(NodeObject& node, std::size_t thisId, std::size_t parentId) {
		if (const std::string& name = node.name; callbacks.find(name) != callbacks.end()) {
			callbacks[name](node, thisId, parentId);
		}
		for (auto it : node.childrens) {
			walk(it, IDGenerator<GCategory::NODEOBJECTS>::getId(), thisId);
		}
	}

    void NodeObjectWalker::clearCallbacks() {
        callbacks.clear();
    }

}