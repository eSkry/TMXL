//
// Created by depish on 17.07.19.
//

#ifndef TMXL_NODEOBJECTCONVERTER_H
#define TMXL_NODEOBJECTCONVERTER_H

#include "TMXL/Map/NodeObject.h"
#include "TMXL/Config.h"

#include <SFML/System/String.hpp>

#include <iostream>
#include <functional>
#include <utility>
#include <map>

namespace TMXL {

    class NodeObjectConverter {
    public:
        using CallbackType = std::function<void(std::shared_ptr<NodeObject>)>;

        /**
         * @param nodeName
         * @param callback
         */
        void registerCallback(const sf::String& nodeName, CallbackType callback);

        void convert(std::shared_ptr<NodeObject> root);

        void clearCallbacks();

    private:
        std::map<sf::String, CallbackType> callbacks;
    };

}

#endif //TMXL_NODEOBJECTCONVERTER_H
