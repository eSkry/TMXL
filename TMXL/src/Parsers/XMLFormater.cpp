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
		mStream << std::string(mLevel, ' ') << '<' << node.name.toAnsiString();
		for (auto attr : node.attributes) {
			mStream << ' ' << attr.first.toAnsiString() << "=\"" << attr.second.toAnsiString() << "\"";
		}

		if (node.childrens.empty() && node.content.isEmpty()) {
			mStream << "/>\n";
			--mLevel;
			return;
		}

		stream << ">\n";

		if (!node.content.isEmpty()) {
			mStream << node.content.toAnsiString();
			mStream << std::string(mLevel, ' ') << "</" << node.name.toAnsiString() << ">\n";
			--mLevel;
			return;
		}

		for (auto child : node.childrens) {
			recurseFormat(child, mStream);
		}

		mStream << std::string(mLevel, ' ') << "</" << node.name.toAnsiString() << ">\n";
		--mLevel;
	}


}