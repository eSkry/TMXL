#ifndef IFORMATER_H
#define IFORMATER_H

#include "TMXL/Map/NodeObject.h"

#include <ostream>

namespace TMXL {
	
	class IFormater {
	public:

		virtual std::ostream& formatNode(const NodeObject& node, std::ostream& os) = 0;

	};

}

#endif // !IFORMATER_H
