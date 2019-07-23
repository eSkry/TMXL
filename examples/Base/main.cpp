
#include <TMXL/System/NodeObjectPrinter.h>
#include <TMXL/Map/NodeObjectWalker.h>
#include <TMXL/Parsers/XML/PugiParser.h>
#include <TMXL/Parsers/XMLFormater.h>
#include <TMXL/Map/NodeObject.h>
#include <TMXL/System/Logger.h>
#include <TMXL/Tools.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
using namespace std;

int main() {
    // Set map for load
    TMXL::PugiParser parser("Maps/infinite1.tmx");
    // Start parsion
    parser.parse();
    // Get root node of map (is not "map" node)
    auto map = parser.getRoot();

	// For printing map structure to stream - create xmlFormater
	TMXL::XMLFormater xmlFormat;
	// And start printing
	TMXL::NodeObjectPrinter::print(*map, xmlFormat, false, cout);

    return 0;
}