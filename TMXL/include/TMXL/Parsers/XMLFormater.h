#ifndef XMLFORMATER_H
#define XMLFORMATER_H

#include "TMXL/Parsers/IFormater.h"
#include "TMXL/Map/NodeObject.h"

#include <sstream>
#include <ostream>
#include <string>

namespace TMXL {

	class XMLFormater : public IFormater {
	public:
		
		XMLFormater();

		std::ostream& formatNode(const NodeObject& node, std::ostream& os) override;

	protected:

		void recurseFormat(const NodeObject& node, std::ostream& stream);

	private:
		int mLevel;
		bool mSkipFirstNode;
	};

}

#endif // XMLFORMATER_H