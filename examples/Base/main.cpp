
#include <TMXL/System/NodeObjectPrinter.h>
#include <TMXL/System/NodeObjectWalker.h>
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
    cout << "Lower: " << TMXL::strToLowerCase("Is LOOOOOOWeer =) yeah 123") << endl;
    cout << cout.hex << TMXL::charToUint8('1', '1') << endl;
    cout << "Color: " << TMXL::colorToStringARGB(TMXL::Color::Red) << endl;

    TMXL::PugiParser parser("map1.tmx");
    parser.parse();

    TMXL::Log::info("is work!");

    auto map = parser.getRoot();
    //map->dump();

 //   TMXL::NodeObjectWalker walker;
	//walker.registerCallback("map", [](std::shared_ptr<TMXL::NodeObject> node){
 //       cout << node->name.toAnsiString() << endl;
 //   });
	//walker.registerCallback("object", [](std::shared_ptr<TMXL::NodeObject> node){
 //       node->dump();
 //   });
	//walker.run(map);

	TMXL::XMLFormater xmlFormat;
	//TMXL::NodeObjectPrinter::print(map, &xmlFormat, cout);

	std::vector<TMXL::NodeObject> data;
	map->findAllNodes("property", data);

	for (auto it : data) {
		TMXL::NodeObjectPrinter::print(it, xmlFormat, cout) << endl;
	}

    return 0;
}