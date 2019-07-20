//
// Created by depish on 17.07.19.
//

#ifndef TMXL_NODEOBJECT_H
#define TMXL_NODEOBJECT_H

#include "TMXL/Config.h"

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>

namespace TMXL {

    class NodeObject {
	public:
        using NodeList = std::vector<NodeObject>;
        using Attributes = std::map<std::string, std::string>;

		/**
		 * @brief Find nodes on all childrens and add finded nodes to 'toVector'
		 * @param nodeName
		 * @param toVector
		 */
        void findAllNodes(const std::string& nodeName, std::vector<NodeObject>& toVector) noexcept;

        /**
         * @brief Node name
         */
        std::string name;

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
        std::string content;

        /**
         * @brief ture if is root node
         */
        bool isRootNode             = false;

	private:

		void recursiveFind(const std::string& nodeName, NodeObject& object, std::vector<NodeObject>& vector) noexcept;

    };

}

#endif //TMXL_NODEOBJECT_H
