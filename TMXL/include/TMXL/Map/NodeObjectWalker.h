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

        using CallbackType = std::function<void(NodeObject&, std::size_t thisId, std::size_t parentId)>;

        /**
         * @param nodeName
         * @param callback
         */
        void registerCallback(const std::string& nodeName, CallbackType callback);

        /**
         * @brief Запускает обход всех дочерних узлов
         * @param root
         */
        void run(NodeObject& root);

        /**
         * @brief Очищает зарегистрированные callbacks
         */
        void clearCallbacks();

    private:
		void walk(NodeObject& node, std::size_t thisId, std::size_t parentId);
        std::map<std::string, CallbackType> mCallbacks;
        IDGenerator mGenerator;
    };

}

#endif //TMXL_NODEOBJECTWALKER_H
