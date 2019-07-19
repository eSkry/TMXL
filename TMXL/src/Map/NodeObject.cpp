#include "TMXL/Map/NodeObject.h"

namespace TMXL {

    void NodeObject::findAllNodes(const sf::String& nodeName, std::vector<NodeObject>& toVector) noexcept {
        for (auto it : childrens) {
            recursiveFind(nodeName, it, toVector);
        }
    }

	void NodeObject::recursiveFind(const sf::String& nodeName, NodeObject& object, std::vector<NodeObject>& vector) noexcept {
		if (object.name == nodeName) {
			vector.push_back(object);
		}

		for (auto it : object.childrens) {
			recursiveFind(nodeName, it, vector);
		}
	}

}