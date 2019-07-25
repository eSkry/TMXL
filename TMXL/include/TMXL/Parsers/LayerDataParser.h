#ifndef TMXL_LAYERDATAPARSER_H
#define TMXL_LAYERDATAPARSER_H

#include <sstream>
#include <string>
#include <vector>
#include <limits>

namespace TMXL {

    class LayerDataParser {
    public:

        /**
         * @brief Parse layer tile data to vector
         * @param data 
         * @param to 
         * @param layerWidth 
         * @param layerHeight 
         */
        static void load(const std::string& data, std::vector<std::size_t>& to, std::size_t layerWidth, std::size_t layerHeight);

        /**
         * @brief Convert std::vector<std::size_t> to std::string ("0,1,2,3,4,5 ...")
         * @param data
         * @param layerWidth 
         * @param layerHeight 
         * @return std::string 
         */
        static std::string serialize(const std::vector<std::size_t>& data, std::size_t layerWidth, bool addNewLines = false);

        /**
         * @brief Convert std::vector<std::size_t> to std::string ("0,1,2,3,4,5 ...")
         * @param data 
         * @param to 
         * @param layerWidth 
         */
        static void serialize(const std::vector<std::size_t>& data, std::string& to, std::size_t layerWidth, bool addNewLines = false);

    };

}

#endif // TMXL_LAYERDATAPARSER_H