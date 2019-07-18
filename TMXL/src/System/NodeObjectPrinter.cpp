#include "TMXL/System/NodeObjectPrinter.h"

namespace TMXL {

	std::ostream& NodeObjectPrinter::print(std::shared_ptr<NodeObject> node, IFormater* formater, std::ostream& os) {
		os << formater->formatNode(node).str();
		return os;
	}

}