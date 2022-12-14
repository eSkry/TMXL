#include <TMXL/System/AutoSwitchLoader.h>
#include <TMXL/System/NodeObjectPrinter.h>
#include <TMXL/Parsers/XML/PugiParser.h>
#include <TMXL/Map/NodeObjectWalker.h>
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
    TMXL::AutoSwitchLoader loader;
    auto TMXParser = std::make_shared<TMXL::PugiParser>();
    loader.registerParser("tmx", TMXParser);

    // Parse map
    auto map = loader.parse("Maps/infinite1.tmx");

	// For printing map structure to stream - create xmlFormater
	TMXL::XMLFormater xmlFormat;
	// And start printing
	TMXL::NodeObjectPrinter::print(*map, xmlFormat, false, cout);

    return 0;
}