#include "TMXL/Map/NodeObjectWalker.h"

namespace TMXL {

    void NodeObjectWalker::registerCallback(const std::string &nodeName, CallbackType callback) {
        mCallbacks[nodeName] = std::move(callback);
    }

    void NodeObjectWalker::run(NodeObject& node) {
		auto rootId = mGenerator.getId();
		walk(node, rootId, rootId);
    }

	void NodeObjectWalker::walk(NodeObject& node, std::size_t thisId, std::size_t parentId) {
		if (const std::string& name = node.name; mCallbacks.find(name) != mCallbacks.end()) {
            mCallbacks[name](node, thisId, parentId);
		}
		for (auto it : node.childrens) {
			walk(*it, mGenerator.getId(), thisId);
		}
	}

    void NodeObjectWalker::clearCallbacks() {
        mCallbacks.clear();
    }

}