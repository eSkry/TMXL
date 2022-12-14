#include "TMXL/Parsers/XML/PugiParser.h"

namespace TMXL {

    PugiParser::PugiParser() {
        mGenerator.reset();
    }

    PugiParser::PugiParser(const std::string& fileName) : PugiParser() {
        mfileName = fileName;
    }

    bool PugiParser::parse() {
        if (mfileName.empty()){
            Log::error("PugiParser: file name is empty!");
            return false;
        }

        mRootNode = std::make_shared<NodeObject>();
        mGenerator.reset();

        using pugi::xml_parse_result;
        using pugi::xml_document;
        using pugi::xml_node;

        xml_document        l_document;
        xml_parse_result    l_result = l_document.load_file(mfileName.c_str());

        if (!l_result){
            Log::error("PugiParser: '" + mfileName + ", " + l_result.description());
            return false;
        }

		xml_node lRootNode = l_document.root();

        parseNode(&lRootNode, *mRootNode);
        mRootNode->nodeId = mGenerator.getId();
        mRootNode->isRootNode = true;

        return true;
    }

    std::shared_ptr<NodeObject> PugiParser::getRoot() noexcept {
        return mRootNode;
    }

    void PugiParser::parseNode(pugi::xml_node *pNode, NodeObject& pNodeObject) noexcept {
        pNodeObject.name = std::string(pNode->name());
        parseAttributes(pNode, pNodeObject);

		pNodeObject.content = pNode->text().as_string();
		if (!pNodeObject.content.empty()) {
			TMXL::replaceAll(pNodeObject.content, "\n", "");
		}

        for (auto childNode : pNode->children()){
            pNodeObject.childrens.push_back( std::make_shared<NodeObject>() );
            pNodeObject.childrens.back()->nodeId = mGenerator.getId();
            parseNode(&childNode, *pNodeObject.childrens.back());
        }
    }

    void PugiParser::parseAttributes(pugi::xml_node *pNodeWithAttributes, NodeObject& pToObject) noexcept {
        for (auto it : pNodeWithAttributes->attributes()){
            pToObject.attributes.insert(std::make_pair(std::string(it.name()), it.value()));
        }
    }

    void PugiParser::clean() noexcept {
        mRootNode.reset();
        mGenerator.reset();
    }

}