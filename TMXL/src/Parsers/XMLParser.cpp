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

        return true;
    }

    std::shared_ptr<NodeObject> XMLParser::getRoot() {
        return mRootNode;
    }

    XMLParser::XMLParser() {
        mRootNode = std::make_shared<NodeObject>();
    }

    void XMLParser::parseNode(pugi::xml_node *pNode, std::shared_ptr<NodeObject> pNodeObject) {
        pNodeObject->name = pugi::as_wide(pNode->name());
        parseAttributes(pNode, pNodeObject);
        pNodeObject->content = pugi::as_wide(pNode->text().as_string());

        for (auto childNode : pNode->children()){
            pNodeObject->childrens.push_back(std::make_shared<NodeObject>());
            parseNode(&childNode, pNodeObject->childrens.back());
        }
    }

    void XMLParser::parseAttributes(pugi::xml_node *pNodeWithAttributes, std::shared_ptr<NodeObject> pToObject) {
        for (auto it : pNodeWithAttributes->attributes()){
            TMXLType value;
            value = sf::String(pugi::as_wide(it.value()));
            pToObject->attributes.insert(std::make_pair(sf::String(pugi::as_wide(it.name())), value));
        }
    }

}