
#include <TMXL/System/NodeObjectWalker.h>
#include <TMXL/Parsers/XMLParser.h>
#include <TMXL/Map/NodeObject.h>
#include <TMXL/Tools.h>

#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>
using namespace std;

int main() {
    cout << "TMXL Version: " << TMXL::getTMXLVersion() << endl;
    cout << "Lower: " << TMXL::strToLowerCase("Is LOOOOOOWeer =) yeah 123").toAnsiString() << endl;
    cout << cout.hex << TMXL::charToUint8('1', '1') << endl;
    cout << "Color: " << TMXL::colorToStringARGB(sf::Color::Red).toAnsiString() << endl;

    TMXL::XMLParser parser;
    parser.setFileName("map1.tmx");
    parser.parse();

    auto map = parser.getRoot();
    //map->dump();

    TMXL::NodeObjectWalker walker;
	walker.registerCallback("map", [](std::shared_ptr<TMXL::NodeObject> node){
        cout << node->name.toAnsiString() << endl;
    });
	walker.registerCallback("object", [](std::shared_ptr<TMXL::NodeObject> node){
        node->parent->dump();
    });
	walker.run(map);

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