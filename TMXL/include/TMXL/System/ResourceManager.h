//
// Created by depish on 15.07.19.
//

#ifndef RESOURCEMANAGER_H

#include "../Config.h"

#include <SFML/System/String.hpp>

#include <memory>
#include <map>

namespace TMXL {

    template <typename T, typename String_t = sf::String>
    class ResourceManager : public std::map<String_t, std::shared_ptr<T>> {
    public:
        ResourceManager() : std::map<String_t, std::shared_ptr<T>>() {}

        /**
         * @brief Reutrn false if resource by name is not exists
         * @param name
         * @return
         */
        bool exists(const String_t &name) {
            return !(this->find(name) == this->end());
        }
    };

}

#define RESOURCEMANAGER_H

#endif //RESOURCEMANAGER_H
