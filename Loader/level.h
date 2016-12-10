#ifndef LEVEL_H
#define LEVEL_H

/////////// PUGI ///////////
#include <pugixml.hpp>

/////////// SFML ///////////
#include <SFML/Graphics.hpp>
using namespace sf;

/////////// STL ///////////
#include <iostream>
#include <typeinfo>
#include <cstring>
#include <string>
#include <vector>
#include <list>
using namespace std;

/////////// LOADER ///////////
#include "objects.h"

/////////////////////////// GRAPHICS ///////////////////////////
struct BackGround{
    Texture*            tTexture;
    Sprite*             sSprite;

    int                 iWidth;
    int                 iHeight;

    Vector2f            vPosition;
};

struct Tileset{
    int                 iFirstTileID;
    int                 iTileCount;
    int                 iTileWidth;
    int                 iTileHeight;

    Texture*            tTexture;
    Sprite*             sSprite;

    map<int, IntRect>   mTiles;
};

struct Layer{
    int                 iWidth;
    int                 iHeight;
    int                 iOpacity;
    int**               iLayer;
};

/////////////////////////// GRAPHICS ///////////////////////////

class Level{
public:
    Level(RenderWindow *renderWindow);
    ~Level();

    // Отрисовка уровня
    void drawLevel();

    void loadLevel(string fileName);
    void closeLevel();

    // Получить обьекты
    list<TRect*>    getRectsWithObjectGroup(string objGroup);
    list<TRect*>&   getRectsAll();
    list<TRect*>    getRectsWithType(string type);
    list<TRect*>    getRectsWithName(string name);
    list<TRect*>    getRectsWithID(int ID);

    list<Polygon*>  getPolygonsWithObjectGroup(string objGroup);
    list<Polygon*>& getPolygonsAll();
    list<Polygon*>  getPolygonsWithType(string type);
    list<Polygon*>  getPolygonsWithName(string name);
    list<Polygon*>  getPolygonsWithID(int ID);

    list<TShape*>   getShapesWithObjectGroup(string objGroup);
    list<TShape*>&  getShapesAll();
    list<TShape*>   getShapesWithType(string type);
    list<TShape*>   getShapesWithName(string name);
    list<TShape*>   getShapesWithID(int ID);

    list<Polyline*> getPolylineWithObjectGroup(string objGroup);
    list<Polyline*>& getPolylineAll();
    list<Polyline*> getPolylineWithType(string type);
    list<Polyline*> getPolylineWithName(string name);
    list<Polyline*> getPolylineWithID(int ID);

    // WORLD
    int getWorldWidthPixel();
    int getWorldHeightPixel();
private:
    //  MAP //
    int                     iCountAllTiles;
    int                     iCountAllLayers;
    int                     iTileWidth;
    int                     iTileHeight;
    int                     iFullWorldSizeWidth;
    int                     iFullWorldSizeHeight;

    bool                    bLoaded;

    // MAP DATA //
    vector<Tileset>         vTilesets;
    vector<Layer>           vLayers;
    vector<BackGround>      vBackGrounds;

    // OBJECT DATA //
    list<TRect*>            lRects;       // Прямоугольники
    list<Polygon*>          lPolygons;    // Полигоны
    list<Polyline*>         lPolylines;   // Полилайны
    list<TShape*>           lShapes;      // Элипсы

    // Возвращает таилсет на отрисовку
    vector<Tileset>::iterator getDrawSprite(int idTile);

    // Преобразует строку точек в список точек (points)
    list<Vector2f> stringToData(string sData);

    template <class T>
    T getOBjectsObjectGroup(T& object, string objGroup);
    template <class T>
    T getObjectsName(T& object, string name);
    template <class T>
    T getObjectsType(T& object, string type);
    template <class T>
    T getObjectsID(T& object, int ID);


    const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
    const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;

    // SYSTEM //
    RenderWindow*           rRenderWindow;

    string                  sLoaderVersion;
};

#endif // LEVEL_H
