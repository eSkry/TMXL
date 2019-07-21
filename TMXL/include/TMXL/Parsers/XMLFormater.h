#ifndef XMLFORMATER_H
#define XMLFORMATER_H

#include "TMXL/Parsers/IFormater.h"
#include "TMXL/Map/NodeObject.h"

#include <sstream>
#include <string>

namespace TMXL {

	class XMLFormater : public IFormater {
	public:
		
		XMLFormater();

		std::stringstream& formatNode(const NodeObject& node, bool skipFirstNode = false) override;

	protected:

		void recurseFormat(const NodeObject& node, std::stringstream& stream);

	private:
		std::stringstream mStream;
		int mLevel;
	};

}

#endif // XMLFORMATER_H