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

    std::string LayerDataParser::serialize(const std::vector<std::size_t>& data, std::size_t layerWidth, bool addNewLines){
        std::string result;
        serialize(data, result, layerWidth, addNewLines);
        return result;
    }

    void LayerDataParser::serialize(const std::vector<std::size_t>& data, std::string& to, std::size_t layerWidth, bool addNewLines){
        std::size_t dataLength = data.size() * 2;
        to.clear();
        to.reserve(dataLength);
        std::size_t countNumbers = data.size();

        for (std::size_t i = 0; i < countNumbers - 1; i++){
            to += std::to_string(data[i]);
            to += ',';
            if (addNewLines && (i + 1) % layerWidth == 0){
                to += '\n';
            }
        }
        to += std::to_string(data[countNumbers - 1]);
    }

}