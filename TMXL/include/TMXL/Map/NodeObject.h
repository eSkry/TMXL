//
// Created by depish on 17.07.19.
//

#ifndef TMXL_NODEOBJECT_H
#define TMXL_NODEOBJECT_H

#include "TMXL/Config.h"

#include <SFML/System/String.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <map>

namespace TMXL {

    class NodeObject {
	public:
        using NodeList = std::vector<std::shared_ptr<NodeObject>>;
        using Attributes = std::map<sf::String, sf::String>;

		/**
		 * @brief Find nodes on all childrens and return std::shared_ptr<vector<std::shared_ptr<NodeObject>>>
		 * @param nodeName
		 * @return
		 */
		std::shared_ptr<std::vector<std::shared_ptr<NodeObject>>> findAllNodes(const sf::String& nodeName) noexcept;

		/**
		 * @brief Find nodes on all childrens and add finded nodes to 'toVector'
		 * @param nodeName
		 * @param toVector
		 */
        void findAllNodes(const sf::String& nodeName, std::shared_ptr<std::vector<std::shared_ptr<NodeObject>>> toVector) noexcept;

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
        sf::String content;

        /**
         * @brief ture if is root node
         */
        bool isRootNode             = false;

        /**
         * @brief Pointer to parent object, if nullptr then is root node
         */
        std::shared_ptr<NodeObject> parent;

	private:

		void recursiveFind(const sf::String& nodeName, std::shared_ptr<NodeObject> object, std::shared_ptr<std::vector<std::shared_ptr<NodeObject>>> vector) noexcept;

    };

}

#endif //TMXL_NODEOBJECT_H
