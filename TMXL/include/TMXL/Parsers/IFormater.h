#ifndef IFORMATER_H
#define IFORMATER_H

#include "TMXL/Map/NodeObject.h"
#include "TMXL/Config.h"

#include <sstream>
#include <memory>

namespace TMXL {
	
	class IFormater {
	public:

		virtual std::stringstream& formatNode(std::shared_ptr<NodeObject> node, bool skipFirstNode = false) = 0;

	};

}

#endif // !IFORMATER_H
