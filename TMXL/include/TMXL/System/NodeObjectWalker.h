//
// Created by depish on 17.07.19.
//

#ifndef TMXL_NODEOBJECTWALKER_H
#define TMXL_NODEOBJECTWALKER_H

#include "TMXL/System/IDGenerator.h"
#include "TMXL/Map/NodeObject.h"
#include "TMXL/Config.h"

#include <SFML/System/String.hpp>

#include <functional>
#include <utility>
#include <map>

namespace TMXL {

    class NodeObjectWalker {
    public:

		struct NodeMeta {
			TLSize_t level = 0;
		};

        using CallbackType = std::function<void(NodeObject&, TLSize_t thisId, TLSize_t parentId)>;

        /**
         * @param nodeName
         * @param callback
         */
        void registerCallback(const sf::String& nodeName, CallbackType callback);

        void run(NodeObject& root);

        void clearCallbacks();

    private:

		void walk(NodeObject& node, TLSize_t thisId, TLSize_t parentId);

        std::map<sf::String, CallbackType> callbacks;
    };

}

#endif //TMXL_NODEOBJECTWALKER_H
