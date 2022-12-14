#include "TMXL/System/NodeObjectPrinter.h"

namespace TMXL {

	std::ostream& NodeObjectPrinter::print(const NodeObject& node, IFormater& formater, bool skipFirstNode, std::ostream& os) {
        if (skipFirstNode) {
            for (const auto& it : node.childrens) {
                formater.formatNode(*it, os);
            }
        } else {
            formater.formatNode(node, os);
        }

		return os;
	}

}