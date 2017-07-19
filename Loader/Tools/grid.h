#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

class Grid{
public:
    Grid(sf::RenderWindow *window, int width, int height, int sizeX, int sizeY);

    void draw();

    void setOffset(sf::Vector2f offset);
    void setColor(sf::Color color);

private:
    sf::RenderWindow *window;
    sf::Color cGridColor;

    int iWidth, iHeight;
    int iRepitCountX, iRepitCountY;

    float fOffsetX, fOffsetY;
    float fCameraX, fCameraY;

    sf::Vertex vLineHorisontal[2] = {
        sf::Vertex(sf::Vector2f(0,0)),
        sf::Vertex(sf::Vector2f(0,0))
    };

    sf::Vertex vLineVertical[2] = {
        sf::Vertex(sf::Vector2f(0,0)),
        sf::Vertex(sf::Vector2f(0,0))
    };
};

#endif
