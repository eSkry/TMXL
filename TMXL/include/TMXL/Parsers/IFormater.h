#ifndef IFORMATER_H
#define IFORMATER_H

#include "TMXL/Map/NodeObject.h"

#include <ostream>

namespace TMXL {
	
	enum Formatting : unsigned {
		Indented = 0x01
	};

	class IFormater {
	public:

		virtual std::ostream& formatNode(const NodeObject& node, std::ostream& os) = 0;

		virtual void setFormat(Formatting format) = 0;

		virtual void unsetFormat(Formatting format) = 0;

		virtual void clearFormat() = 0;

	};

}

#endif // !IFORMATER_H
