
#include <TMXL/System/NodeObjectPrinter.h>
#include <TMXL/System/NodeObjectWalker.h>
#include <TMXL/Parsers/XML/PugiParser.h>
#include <TMXL/Parsers/XMLFormater.h>
#include <TMXL/Map/NodeObject.h>
#include <TMXL/Tools.h>

#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <memory>
using namespace std;

int main() {
    cout << "TMXL Version: " << TMXL::getTMXLVersion() << endl;
    cout << "Lower: " << TMXL::strToLowerCase("Is LOOOOOOWeer =) yeah 123").toAnsiString() << endl;
    cout << cout.hex << TMXL::charToUint8('1', '1') << endl;
    cout << "Color: " << TMXL::colorToStringARGB(sf::Color::Red).toAnsiString() << endl;

    TMXL::PugiParser parser;
    parser.setFileName("map1.tmx");
    parser.parse();

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

	auto nodes = map->findAllNodes("property");
	cout << nodes->size() << endl;
	for (auto it : *nodes) {
		TMXL::NodeObjectPrinter::print(it, &xmlFormat, cout) << endl;
	}

    sf::RenderWindow window(sf::VideoMode(600, 600) ,"Game");
    while(window.isOpen()){

        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();

        window.display();
    }

    return 0;
}