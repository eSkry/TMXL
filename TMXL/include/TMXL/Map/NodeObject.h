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

    struct NodeObject {
        using NodeList = std::vector<std::shared_ptr<NodeObject>>;
        using Attributes = std::map<sf::String, TMXLType>;

        void dump() const { // TODO: remove it or replace
            using namespace std;

            cout << name.toAnsiString() << endl;
            cout << "---------" << endl;
            for (auto it : attributes){
                cout << it.first.toAnsiString() << ": " << it.second.as_string().toAnsiString() << endl;
            }
            cout << content.as_string().toAnsiString() << endl;

            cout << endl;
            for (auto it : childrens){
                it->dump();
            }
        }

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
    };

}

#endif //TMXL_NODEOBJECT_H
