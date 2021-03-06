#ifndef TMXL_NODEOBJECTPRINTER_H
#define TMXL_NODEOBJECTPRINTER_H

#include "TMXL/Parsers/IFormater.h"
#include "TMXL/Map/NodeObject.h"

#include <iostream>
#include <string>
#include <ostream>

namespace TMXL {

	class NodeObjectPrinter {
	public:

	    /**
	     * @brief Выводит структуру объектов в поток std::ostream&
	     * @param node
	     * @param formater - формат в который необходимо конвертировать структуру
	     * @param os - поток в который будет выводиться результат
	     * @param skipFirstNode - пропускать печать передаваемого узла?
	     * @return
	     */
		static std::ostream& print(const NodeObject& node, IFormater& formater, bool skipFirstNode, std::ostream& os);

	};

}

#endif // !TMXL_NODEOBJECTPRINTER_H
