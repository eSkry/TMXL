#include "TMXL/Parsers/LayerDataLoader.h"

namespace TMXL {

    void LayerDataLoader::load(const std::string& data, std::vector<std::size_t>& to, std::size_t layerWidth, std::size_t layerHeight){
        to.reserve(layerHeight * layerWidth);
        std::stringstream ss;
        ss << data;
        
        std::size_t idx = 0;
        std::string::value_type trash;
        while (!ss.eof()) {
            ss >> to[idx];
            ss >> trash;
            ++idx;
        }
    }

}