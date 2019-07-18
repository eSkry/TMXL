#ifndef XMLFORMATER_H
#define XMLFORMATER_H

#include "TMXL/Parsers/IFormater.h"
#include "TMXL/Map/NodeObject.h"
#include "TMXL/Config.h"

#include <sstream>
#include <string>
#include <memory>

namespace TMXL {

	class XMLFormater : public IFormater {
	public:
		
		XMLFormater();

		std::stringstream& formatNode(std::shared_ptr<NodeObject> node, bool skipFirstNode = false) override;

	protected:

		void recurseFormat(std::shared_ptr<NodeObject> node, std::stringstream& stream);

	private:

		std::stringstream mStream;
		int mLevel;

	};

}

#endif // XMLFORMATER_H