#include "TMXL/System/NodeObjectPrinter.h"

namespace TMXL {

	std::ostream& NodeObjectPrinter::print(const NodeObject& node, IFormater& formater, std::ostream& os, bool skipFirstNode) {
		return os << formater.formatNode(node, skipFirstNode).str();
	}

}