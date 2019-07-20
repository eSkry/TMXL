#ifndef IFORMATER_H
#define IFORMATER_H

#include "TMXL/Map/NodeObject.h"

namespace TMXL {
	
	class IFormater {
	public:

		virtual std::stringstream& formatNode(const NodeObject& node, bool skipFirstNode = false) = 0;

	};

}

#endif // !IFORMATER_H
