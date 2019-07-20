//
// Created by depish on 17.07.19.
//

#include "TMXL/System/NodeObjectWalker.h"

namespace TMXL {

    void NodeObjectWalker::registerCallback(const std::string &nodeName, CallbackType callback) {
        callbacks[nodeName] = std::move(callback);
    }

    void NodeObjectWalker::run(NodeObject& node) {
		auto rootId = IDGenerator<GCategory::NODEOBJECTS>::getId();
		walk(node, rootId, rootId);
    }

	void NodeObjectWalker::walk(NodeObject& node, TLSize_t thisId, TLSize_t parentId) {
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