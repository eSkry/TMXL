//
// Created by depish on 17.07.19.
//

#ifndef TMXL_NODEOBJECTWALKER_H
#define TMXL_NODEOBJECTWALKER_H

#include "TMXL/System/IDGenerator.h"
#include "TMXL/Map/NodeObject.h"

#include <functional>
#include <utility>
#include <map>

namespace TMXL {

    class NodeObjectWalker {
    public:

		struct NodeMeta {
			std::size_t level = 0;
		};

        using CallbackType = std::function<void(NodeObject&, std::size_t thisId, std::size_t parentId)>;

        /**
         * @param nodeName
         * @param callback
         */
        void registerCallback(const std::string& nodeName, CallbackType callback);

        void run(NodeObject& root);

        void clearCallbacks();

    private:

		void walk(NodeObject& node, std::size_t thisId, std::size_t parentId);

        std::map<std::string, CallbackType> callbacks;
    };

}

#endif //TMXL_NODEOBJECTWALKER_H
