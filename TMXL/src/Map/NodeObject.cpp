#include "TMXL/Map/NodeObject.h"

namespace TMXL {

    void NodeObject::findAllNodes(const std::string& nodeName, NodeList& toVector) noexcept {
        for (auto it : childrens) {
            recursiveFind(nodeName, it, toVector);
        }
    }

	void NodeObject::recursiveFind(const std::string& nodeName, std::shared_ptr<NodeObject>& object, NodeList& vector) noexcept {
		if (object->name == nodeName) {
			vector.push_back(object);
		}

		for (auto it : object->childrens) {
			recursiveFind(nodeName, it, vector);
		}
	}

}