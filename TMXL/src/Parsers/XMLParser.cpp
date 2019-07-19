#include "TMXL/Parsers/XMLParser.h"

namespace TMXL {

    bool XMLParser::parse() {
        if (m_fileName.isEmpty()){
            return false;
        }

        using pugi::xml_parse_result;
        using pugi::xml_document;
        using pugi::xml_node;

        xml_document        l_document;
        xml_parse_result    l_result = l_document.load_file(m_fileName.toAnsiString().c_str());

        if (!l_result){
            tmxlDebug(l_result.description());
            return false;
        }

		xml_node lRootNode = l_document.root();

        parseNode(&lRootNode, mRootNode);
        mRootNode->isRootNode = true;

        return true;
    }

    std::shared_ptr<NodeObject> XMLParser::getRoot() {
        return mRootNode;
    }

    XMLParser::XMLParser() {
        mRootNode = std::make_shared<NodeObject>();
    }

    void XMLParser::parseNode(pugi::xml_node *pNode, std::shared_ptr<NodeObject> pNodeObject) noexcept {
        pNodeObject->name = std::string(pNode->name());
        parseAttributes(pNode, pNodeObject);

		sf::String content = std::string(pNode->text().as_string());
		if (!content.isEmpty()) {
			pNodeObject->content = content;
		}

        for (auto childNode : pNode->children()){
            pNodeObject->childrens.push_back(std::make_shared<NodeObject>());
            pNodeObject->childrens.back()->parent = pNodeObject;
            parseNode(&childNode, pNodeObject->childrens.back());
        }
    }

    void XMLParser::parseAttributes(pugi::xml_node *pNodeWithAttributes, std::shared_ptr<NodeObject> pToObject) noexcept {
        for (auto it : pNodeWithAttributes->attributes()){
            TMXLType value;
            value = sf::String(std::string(it.value()));
            pToObject->attributes.insert(std::make_pair(std::string(it.name()), value));
        }
    }

}