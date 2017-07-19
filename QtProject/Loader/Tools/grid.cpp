#include "grid.h"

Grid::Grid(sf::RenderWindow *window, int width, int height, int sizeX, int sizeY){
    this->window = window;
    iWidth = width;
    iHeight = height;
    fOffsetX = 0;
    fOffsetY = 0;
    cGridColor = sf::Color::White;
    iRepitCountX = sizeX;
    iRepitCountY = sizeY;
}


void Grid::setColor(sf::Color color){
    cGridColor = color;
    vLineVertical[0].color = color;
    vLineVertical[1].color = color;
    vLineHorisontal[0].color = color;
    vLineHorisontal[1].color = color;
}

void Grid::draw(){
    for (int y = 0; y < iRepitCountY; y++){
        for (int x = 0; x < iRepitCountX; x++){
            vLineVertical[0].position.y = y*iHeight + fOffsetY;
            vLineVertical[1].position.y = y*iHeight+iHeight + fOffsetY;

            vLineVertical[0].position.x = x*iWidth + fOffsetX;
            vLineVertical[1].position.x = x*iWidth + fOffsetX;

            window->draw(vLineVertical, 2, sf::Lines);

            vLineHorisontal[0].position.y = y*iHeight + fOffsetY;
            vLineHorisontal[1].position.y = y*iHeight + fOffsetY;

            vLineHorisontal[0].position.x = x*iWidth + fOffsetX;
            vLineHorisontal[1].position.x = x*iWidth+iWidth + fOffsetX;

            window->draw(vLineHorisontal, 2, sf::Lines);
        }
    }
}

void Grid::setOffset(sf::Vector2f offset){
    fOffsetX = offset.x;
    fOffsetY = offset.y;
}
