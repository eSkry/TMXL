#include "TMXL/Map/NodeObject.h"

namespace TMXL {

	std::shared_ptr<std::vector<std::shared_ptr<NodeObject>>> NodeObject::findAllNodes(const sf::String& nodeName) _TMXL_NOEXCEPT {
		auto result = std::make_shared<std::vector<std::shared_ptr<NodeObject>>>();

		findAllNodes(nodeName, result);

		return result;
	}

    void NodeObject::findAllNodes(const sf::String& nodeName, std::shared_ptr<std::vector<std::shared_ptr<NodeObject>>> toVector) {
        for (auto it : childrens) {
            recursiveFind(nodeName, it, toVector);
        }
    }

	void NodeObject::recursiveFind(const sf::String& nodeName, std::shared_ptr<NodeObject> object, std::shared_ptr<std::vector<std::shared_ptr<NodeObject>>> vector) _TMXL_NOEXCEPT {
		if (object->name == nodeName) {
			vector->push_back(object);
		}

		for (auto it : object->childrens) {
			recursiveFind(nodeName, it, vector);
		}
	}

}