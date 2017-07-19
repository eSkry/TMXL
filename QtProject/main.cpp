#include "Loader/level.h"


int main(){
    sf::RenderWindow window(sf::VideoMode(900, 600), "Test Loader Map", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Level level(&window);
    level.loadLevel("./maps/testMap.tmx");


    LPropertyData* bgColor = level.getTileConcrProperty("marioTiles", 1, "background");
    Color tempColor = bgColor->pValue.as_color();

    LPropertyData* abc = level.getLayerConctProperty("Main", "lol");
    cout << abc->pValue.as_int() << endl;

    while (window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(tempColor);

        level.drawLevel(); // Drawind map

        window.display();
    }

    level.closeLevel();
}

