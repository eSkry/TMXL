#ifndef TMXL_XMLFORMATER_H
#define TMXL_XMLFORMATER_H

#include "TMXL/Parsers/IFormater.h"
#include "TMXL/Map/NodeObject.h"

#include <ostream>
#include <string>

namespace TMXL {

    /**
     * @brief Строит XML структуру из NodeObject
     */
	class XMLFormater : public IFormater {
	public:
		
		XMLFormater();

		std::ostream& formatNode(const NodeObject& node, std::ostream& os) override;

		void setFormat(Formatting format) override;

		void unsetFormat(Formatting format) override;

		void clearFormat() override;

	protected:

		void recurseFormat(const NodeObject& node, std::ostream& stream);

	private:
		void writeNewLine(std::ostream& os);

		int 		mLevel;
		unsigned 	mFormat;
	};

}

#endif // TMXL_XMLFORMATER_H