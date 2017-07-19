#include "Loader/level.h"
#include "Loader/Tools/grid.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(900, 600), "Test Loader Map", sf::Style::Default);
    window.setFramerateLimit(40);
    window.setVerticalSyncEnabled(true);

    Grid grid(&window, 64, 64, 20, 20);
    grid.setColor(sf::Color::Cyan);
    grid.setOffset(sf::Vector2f(15, 15));

    Level level(&window);
    level.loadLevel("./maps/testMap.tmx");

    View view;
    view.reset(FloatRect(0, 0, 900, 600));
    window.setView(view);

    view.zoom(2);

    //LPropertyData* bgColor = level.getTileConcrProperty("marioTiles", 1, "background");
    //Color tempColor = bgColor->pValue.as_color();

    /*LPropertyData* abc = level.getLayerConctProperty("Main", "lol");
    cout << abc->pValue.as_int() << endl;*/

    float camSpeed = 1.3;

    float time;
    sf::Clock clock;
    while (window.isOpen()){
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 800;

        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized){
                view.setSize(window.getSize().x, window.getSize().y);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            view.move(-camSpeed * time, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            view.move(camSpeed * time, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            view.move(0, -camSpeed * time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            view.move(0, camSpeed * time);
        }


        window.clear();
        window.setView(view);
        level.drawLevel(); // Drawind map

        grid.draw();
        window.display();
    }

    level.closeLevel();
}

