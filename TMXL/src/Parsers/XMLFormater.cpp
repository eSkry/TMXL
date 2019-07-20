#include "TMXL/Parsers/XMLFormater.h"

namespace TMXL {

	XMLFormater::XMLFormater() {
		mLevel = -1;
	}

	std::stringstream& XMLFormater::formatNode(const NodeObject& node, bool skipFirstNode) {
		bool isNodeHaveChild = false;
		if (node.childrens.size() != 0) {
			isNodeHaveChild = true;
		}

		if (skipFirstNode) {
			for (auto it : node.childrens) {
				recurseFormat(it, mStream);
			}
		} else {
			recurseFormat(node, mStream);
		}

		return mStream;
	}

	void XMLFormater::recurseFormat(const NodeObject& node, std::stringstream& stream) {
		++mLevel;
		mStream << std::string(mLevel, ' ') << '<' << node.name;
		for (auto attr : node.attributes) {
			mStream << ' ' << attr.first << "=\"" << attr.second << "\"";
		}

		if (node.childrens.empty() && node.content.empty()) {
			mStream << "/>\n";
			--mLevel;
			return;
		}

		stream << ">\n";

		if (!node.content.empty()) {
			mStream << node.content;
			mStream << std::string(mLevel, ' ') << "</" << node.name << ">\n";
			--mLevel;
			return;
		}

		for (auto child : node.childrens) {
			recurseFormat(child, mStream);
		}

		mStream << std::string(mLevel, ' ') << "</" << node.name << ">\n";
		--mLevel;
	}


}