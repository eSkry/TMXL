#include "TMXL/Parsers/XMLFormater.h"

namespace TMXL {

	XMLFormater::XMLFormater() {
		mLevel = -1;
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
			os << "/>\n";
			--mLevel;
			return;
		}

		os << ">\n";

		if (!node.content.empty()) {
			os << node.content;
			os << std::string(mLevel, ' ') << "</" << node.name << ">\n";
			--mLevel;
			return;
		}

		for (const auto& child : node.childrens) {
			recurseFormat(child, os);
		}

		os << std::string(mLevel, ' ') << "</" << node.name << ">\n";
		--mLevel;
	}

}