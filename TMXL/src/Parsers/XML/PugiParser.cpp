#include "TMXL/Parsers/XML/PugiParser.h"

namespace TMXL {

    bool PugiParser::parse() {
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

        parseNode(&lRootNode, *mRootNode);
        mRootNode->isRootNode = true;

        return true;
    }

    std::shared_ptr<NodeObject> PugiParser::getRoot() {
        return mRootNode;
    }

    PugiParser::PugiParser() {
        mRootNode = std::make_shared<NodeObject>();
    }

    void PugiParser::parseNode(pugi::xml_node *pNode, NodeObject& pNodeObject) noexcept {
        pNodeObject.name = std::string(pNode->name());
        parseAttributes(pNode, pNodeObject);

		sf::String content = std::string(pNode->text().as_string());
		if (!content.isEmpty()) {
			pNodeObject.content = content;
		}

        for (auto childNode : pNode->children()){
            pNodeObject.childrens.push_back( NodeObject() );
            parseNode(&childNode, pNodeObject.childrens.back());
        }
    }

    void PugiParser::parseAttributes(pugi::xml_node *pNodeWithAttributes, NodeObject& pToObject) noexcept {
        for (auto it : pNodeWithAttributes->attributes()){
            pToObject.attributes.insert(std::make_pair(std::string(it.name()), it.value()));
        }
    }

}