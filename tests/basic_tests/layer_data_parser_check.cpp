#include "gtest/gtest.h"

#include <TMXL/Parsers/LayerDataParser.h>
#include <string>
#include <vector>

TEST(layer_data_parser_check, test_eq) {
    using namespace TMXL;

    LayerDataParser parser;

    std::string input = "0,1,2,3,4,5";
    std::vector<std::size_t> to;
    parser.load(input, to, 6, 1);

    for (int i = 0; i < 6; i++){
        ASSERT_EQ(to[i], i);
    }

}
