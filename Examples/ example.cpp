
#include "level.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(900, 600), "Test DBG", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Level level(&window);
    level.loadLevel("maps/testMap.tmx");

    while (window.isOpen()){
    
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        level.drawLevel(); // Drawind map

        window.display();
    }
}
