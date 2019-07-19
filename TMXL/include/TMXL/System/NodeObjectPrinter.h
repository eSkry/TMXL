#ifndef NODEOBJECTPRINTER_H
#define NODEOBJECTPRINTER_H

#include "TMXL/Parsers/IFormater.h"
#include "TMXL/Map/NodeObject.h"
#include "TMXL/Config.h"

#include <SFML/System/String.hpp>

#include <iostream>
#include <string>
#include <sstream>

namespace TMXL {

	class NodeObjectPrinter {
	public:

		static std::ostream& print(NodeObject& node, IFormater* formater, std::ostream& os, bool skipFirstNode = false);

	};

}

#endif // !NODEOBJECTPRINTER_H
