
#include <iostream>
using namespace std;

#include <TMXL/Parsers/TMXParser.h>
#include <SFML/Graphics.hpp>

#include <TMXL/Tools.h>

int main() {
    cout << "TMXL Version: " << TMXL::getTMXLVersion() << endl;
    cout << "Lower: " << TMXL::strToLowerCase("Is LOOOOOOWeer =) yeah 123").toAnsiString() << endl;
    cout << cout.hex << TMXL::charToUint8('1', '1') << endl;
    cout << "Color: " << TMXL::colorToStringARGB(sf::Color::Red).toAnsiString() << endl;

    TMXL::TMXParser parser;
    parser.setFileName("map1.tmx");
    parser.parse();

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