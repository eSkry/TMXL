#include <TMXL/Parsers/XML/XMLParser.h>
#include <TMXL/Tools.h>

#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/exception.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <fstream>

using namespace std;

bool readFileToString(const boost::filesystem::path& file, std::string& outString) {
    if (!boost::filesystem::exists(file))
        return false;

    if (!outString.empty())
        outString.clear();

    std::ifstream fileStream(file.native());
    if (fileStream.is_open()) {
        auto fileSize = boost::filesystem::file_size(file);
        outString.resize(static_cast<std::string::size_type>(fileSize));
        fileStream.read(&(outString[0]), fileSize);
    } else {
        return false;
    }

    fileStream.close();
    return true;
}


int main() {
    std::string mapData;
    if (!readFileToString("Maps/area5x5.tmx", mapData))
        std::cout << "Error open file\n";

    auto TMXParser = std::make_shared<TMXL::XMLParser>();

    auto map = TMXParser->parse(mapData);

    return 0;
}