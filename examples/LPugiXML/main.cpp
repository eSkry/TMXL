
#include <TMXL/System/NodeObjectPrinter.h>
#include <TMXL/Parsers/XML/PugiParser.h>
#include <TMXL/Parsers/XMLFormater.h>
#include <TMXL/Map/NodeObject.h>
#include <TMXL/Map/TMENodes.h>

#include <iostream>

int main(){
    TMXL::PugiParser parser("Maps/map1.tmx");
    if (!parser.parse()){
        std::cout << "Load failed" << std::endl;
    }

    auto mapRoot = parser.getRoot();

    TMXL::XMLFormater fXml;
    TMXL::NodeObjectPrinter::print(*mapRoot, fXml, true, std::cout); // Print structure to std::cout

    return 0;
}