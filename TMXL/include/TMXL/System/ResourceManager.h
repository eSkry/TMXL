#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <memory>
#include <map>

namespace TMXL {

    enum RDC : int { // Singletone Data Category
        DEFAULT = 1,
        USER
    };

    template <typename T>
    class ResourceManager : public std::map<std::string, std::shared_ptr<T>> {
    public:
        ResourceManager() : std::map<std::string, std::shared_ptr<T>>() {}

        /**
         * @brief Reutrn false if resource by name is not exists
         * @param name
         * @return
         */
        bool exists(const std::string &name) {
            return !(this->find(name) == this->end());
        }
    };

}

#endif //RESOURCEMANAGER_H
