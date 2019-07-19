#include "TMXL/System/NodeObjectPrinter.h"

namespace TMXL {

	std::ostream& NodeObjectPrinter::print(const NodeObject& node, IFormater* formater, std::ostream& os, bool skipFirstNode) {
		os << formater->formatNode(node, skipFirstNode).str();
		return os;
	}

}