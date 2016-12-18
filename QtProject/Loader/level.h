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
#include "datatilepropertys.h"
#include "objects.h"

/////////////////////////// GRAPHICS ///////////////////////////
struct BackGround{
    Texture*            tTexture;
    Sprite*             sSprite;

    int                 iWidth;
    int                 iHeight;

    Vector2f            vPosition;
};

struct LPropertyData{
    string              sName;
    string              sType;
    PropertyValue       pValue;
};

struct Tileset{
    string              sName;

    int                 iFirstTileID;
    int                 iTileCount;
    int                 iTileWidth;
    int                 iTileHeight;

    int                 iSpacing;
    int                 iMarign;

    Texture*            tTexture;
    Sprite*             sSprite;

    map<int, vector<LPropertyData*>> mPropertys;

    map<int, IntRect>   mTiles;
};

struct Layer{
    string              sName;

    int                 iWidth;
    int                 iHeight;
    int                 iOpacity;

    int                 iOffestX;
    int                 iOffestY;

    vector<LPropertyData*> vPropertys;

    unsigned**          iLayer;
};

/////////////////////////// GRAPHICS ///////////////////////////

/////////////////////////// TYPEDEFS ///////////////////////////
typedef vector<LPropertyData*> LVecTilePropertys;
/////////////////////////// TYPEDEFS ///////////////////////////

class Level{
public:  
    Level(RenderWindow *renderWindow);
    ~Level();

    // Отрисовка уровня
    void drawLevel();

    void loadLevel(string fileName);
    void closeLevel();

    // Получить обьекты
    list<Rect_ML*>    getRectsWithObjectGroup(string objGroup);
    list<Rect_ML*>&   getRectsAll();
    list<Rect_ML*>    getRectsWithType(string type);
    list<Rect_ML*>    getRectsWithName(string name);
    list<Rect_ML*>    getRectsWithID(int ID);

    list<Polygon_ML*>  getPolygonsWithObjectGroup(string objGroup);
    list<Polygon_ML*>& getPolygonsAll();
    list<Polygon_ML*>  getPolygonsWithType(string type);
    list<Polygon_ML*>  getPolygonsWithName(string name);
    list<Polygon_ML*>  getPolygonsWithID(int ID);

    list<Shape_ML*>   getShapesWithObjectGroup(string objGroup);
    list<Shape_ML*>&  getShapesAll();
    list<Shape_ML*>   getShapesWithType(string type);
    list<Shape_ML*>   getShapesWithName(string name);
    list<Shape_ML*>   getShapesWithID(int ID);

    list<Polyline_ML*> getPolylineWithObjectGroup(string objGroup);
    list<Polyline_ML*>& getPolylineAll();
    list<Polyline_ML*> getPolylineWithType(string type);
    list<Polyline_ML*> getPolylineWithName(string name);
    list<Polyline_ML*> getPolylineWithID(int ID);

    vector<LPropertyData*> getTilePropertys(string tilesetName, int tileID);
    LPropertyData* getTileConcrProperty(string tilesetName, int tileID, string propertyName);

    vector<LPropertyData*> getLayerPropertys(string layerName);
    LPropertyData* getLayerConctProperty(string layerName, string propertyName);

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
    vector<Tileset*>        vTilesets;
    vector<Layer*>          vLayers;
    vector<BackGround*>     vBackGrounds;

    // OBJECT DATA //
    list<Rect_ML*>          lRects;       // Прямоугольники
    list<Polygon_ML*>       lPolygons;    // Полигоны
    list<Polyline_ML*>      lPolylines;   // Полилайны
    list<Shape_ML*>         lShapes;      // Элипсы

    // Возвращает таилсет на отрисовку
    vector<Tileset*>::iterator getDrawSprite(int idTile);

    // Преобразует строку точек в список точек (points)
    list<Vector2f> stringToData(string sData);

    // Загружает картинки из карты
    void loadImages(pugi::xml_document &doc);
    void loadTiles(pugi::xml_document &doc);
    void loadTileData(pugi::xml_document &doc);

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
