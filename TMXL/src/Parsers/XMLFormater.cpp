#include "TMXL/Parsers/XMLFormater.h"

namespace TMXL {

	XMLFormater::XMLFormater() {
	
	}

	std::stringstream& XMLFormater::formatNode(std::shared_ptr<NodeObject> node) {
		bool isNodeHaveChild = false;
		if (node->childrens.size() != 0) {
			isNodeHaveChild = true;
		}

		recurseFormat(node, stream);

		return stream;
	}

	void XMLFormater::recurseFormat(std::shared_ptr<NodeObject> node, std::stringstream& stream) {
		stream << '<' << node->name.toAnsiString() << ' ';
		for (auto attr : node->attributes) {
			stream << attr.first.toAnsiString() << "=\"" << attr.second.as_string().toAnsiString() << "\"" << ' ';
		}

		auto content = node->content.as_string();

		if (node->childrens.empty() && content.isEmpty()) {
			stream << "/>";
			return;
		}

		stream << '>';

		if (!content.isEmpty()) {
			stream << content.toAnsiString();
			stream << "</" << node->name.toAnsiString() << '>';
			return;
		}

		for (auto child : node->childrens) {
			recurseFormat(child, stream);
		}

		stream << "</" << node->name.toAnsiString() << '>';
	}


}