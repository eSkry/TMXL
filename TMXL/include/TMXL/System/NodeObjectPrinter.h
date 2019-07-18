#ifndef NODEOBJECTPRINTER_H
#define NODEOBJECTPRINTER_H

#include "TMXL/Parsers/IFormater.h"
#include "TMXL/Map/NodeObject.h"
#include "TMXL/Config.h"

#include <SFML/System/String.hpp>

#include <iostream>
#include <string>
#include <memory>

namespace TMXL {

	class NodeObjectPrinter {
	public:

		static std::ostream& print(std::shared_ptr<NodeObject> node, IFormater* formater, std::ostream& os, bool skipFirstNode = false);

	};

}

#endif // !NODEOBJECTPRINTER_H
