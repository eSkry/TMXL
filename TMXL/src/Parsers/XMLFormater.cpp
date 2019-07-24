#include "TMXL/Parsers/XMLFormater.h"

namespace TMXL {

	XMLFormater::XMLFormater() {
		mLevel = -1;
		mFormat = 0;
	}

	std::ostream& XMLFormater::formatNode(const NodeObject& node, std::ostream& os) {
        recurseFormat(node, os);
		return os;
	}

	void XMLFormater::recurseFormat(const NodeObject& node, std::ostream& os) {
		++mLevel;
		os << std::string(mLevel, ' ') << '<' << node.name;
		for (const auto& attr : node.attributes) {
			os << ' ' << attr.first << "=\"" << attr.second << "\"";
		}

		if (node.childrens.empty() && node.content.empty()) {
			os << "/>";
			writeNewLine(os);
			--mLevel;
			return;
		}

		os << ">";
		writeNewLine(os);

		if (!node.content.empty()) {
			os << node.content;
			os << std::string(mLevel, ' ') << "</" << node.name << ">";
			writeNewLine(os);
			--mLevel;
			return;
		}

		for (const auto& child : node.childrens) {
			recurseFormat(child, os);
		}

		os << std::string(mLevel, ' ') << "</" << node.name << ">";
		writeNewLine(os);
		--mLevel;
	}

	void XMLFormater::setFormat(Formatting format) {
		mFormat |= format;
	}

	void XMLFormater::unsetFormat(Formatting format) {
		mFormat &= ~format;
	}

	void XMLFormater::clearFormat() {
		mFormat = 0;
	}

	void XMLFormater::writeNewLine(std::ostream& os) {
		if (mFormat & Formatting::Indented){
			os << '\n';
		}
	}

}