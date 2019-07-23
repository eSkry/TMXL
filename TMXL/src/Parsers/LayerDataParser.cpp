#include "TMXL/Parsers/LayerDataParser.h"
#include <iostream>
namespace TMXL {

    void LayerDataParser::load(const std::string& data, std::vector<std::size_t>& to, std::size_t layerWidth, std::size_t layerHeight){
        to.reserve(layerHeight * layerWidth);
        std::stringstream ss;
        ss << data;
        
        std::size_t idx = 1;
        ss >> to[0];
        while (!ss.eof()) {
            ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');
            ss >> to[idx++];
        }
    }

}