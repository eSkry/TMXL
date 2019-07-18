//
// Created by depish on 17.07.19.
//

#ifndef TMXL_NODEOBJECT_H
#define TMXL_NODEOBJECT_H

#include "TMXL/Config.h"
#include "TMXL/TMXLType.h"

#include <SFML/System/String.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <map>

namespace TMXL {

    class NodeObject {
	public:
        using NodeList = std::vector<std::shared_ptr<NodeObject>>;
        using Attributes = std::map<sf::String, TMXLType>;

		void dump() const;

		std::shared_ptr<std::vector<std::shared_ptr<NodeObject>>> findAllNodes(const sf::String& nodeName) _TMXL_NOEXCEPT;

        /**
         * @brief Node name
         */
        sf::String name;

        /**
         * @brief std::map children nodes
         */
        NodeList childrens;

        /**
         * @brief std::map attributes
         */
        Attributes  attributes;

        /**
         * @brief Node content
         */
        TMXLType content;

        /**
         * @brief ture if is root node
         */
        bool isRootNode             = false;

        /**
         * @brief Pointer to parent object, if nullptr then is root node
         */
        std::shared_ptr<NodeObject> parent;

	private:

		void recursiveFind(const sf::String& nodeName, std::shared_ptr<NodeObject> object, std::shared_ptr<std::vector<std::shared_ptr<NodeObject>>> vector) _TMXL_NOEXCEPT;

    };

}

#endif //TMXL_NODEOBJECT_H
