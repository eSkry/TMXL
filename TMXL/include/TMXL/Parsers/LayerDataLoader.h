#ifndef TMXL_LAYERDATALOADER_H
#define TMXL_LAYERDATALOADER_H

#include <sstream>
#include <string>
#include <vector>

namespace TMXL {

    class LayerDataLoader {
    public:

        /**
         * @brief Parse layer tile data to vector
         * @param data 
         * @param to 
         * @param layerWidth 
         * @param layerHeight 
         */
        static void load(const std::string& data, std::vector<std::size_t>& to, std::size_t layerWidth, std::size_t layerHeight);
    };

}

#endif