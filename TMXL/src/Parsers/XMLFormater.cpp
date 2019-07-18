#include "TMXL/Parsers/XMLFormater.h"

namespace TMXL {

	XMLFormater::XMLFormater() {
		mLevel = -1;
	}

	std::stringstream& XMLFormater::formatNode(std::shared_ptr<NodeObject> node) {
		bool isNodeHaveChild = false;
		if (node->childrens.size() != 0) {
			isNodeHaveChild = true;
		}

		recurseFormat(node, mStream);

		return mStream;
	}

	void XMLFormater::recurseFormat(std::shared_ptr<NodeObject> node, std::stringstream& stream) {
		++mLevel;
		mStream << std::string(mLevel, ' ') << '<' << node->name.toAnsiString();
		for (auto attr : node->attributes) {
			mStream << ' ' << attr.first.toAnsiString() << "=\"" << attr.second.as_string().toAnsiString() << "\"";
		}

		auto content = node->content.as_string();

		if (node->childrens.empty() && content.isEmpty()) {
			mStream << "/>\n";
			--mLevel;
			return;
		}

		stream << ">\n";

		if (!content.isEmpty()) {
			mStream << content.toAnsiString();
			mStream << std::string(mLevel, ' ') << "</" << node->name.toAnsiString() << ">\n";
			--mLevel;
			return;
		}

		for (auto child : node->childrens) {
			recurseFormat(child, mStream);
		}

		mStream << std::string(mLevel, ' ') << "</" << node->name.toAnsiString() << ">\n";
		--mLevel;
	}


}