#ifndef LEVEL_H
#define LEVEL_H

/////////// PUGI ///////////
#include <pugixml.hpp>

/////////// SFML ///////////
#include <SFML/Graphics.hpp>
using namespace sf;

/////////// STL ///////////
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <list>
using namespace std;

class Level{
public:
    Level(RenderWindow *renderWindow);
    ~Level();

    struct Object{
        Object();
        Object(const Object &object);

        string              sName;
        string              sType;

        FloatRect           fRect;
        Texture*            tTexture;
        Sprite*             sSprite;

        void*               vData;
    };

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
        int**               iLayer;
    };

    // Отрисовка уровня
    void drawLevel();

    void loadLevel(string fileName);
    void closeLevel();

    // Получить обьекты
    list<Object*>& getAllObjects();
    list<Object*>  getTypeObjects(string type);
    list<Object*>  getNameObjects(string name);

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
    list<Object*>           lObjects;

    // Возвращает таилсет на отрисовку
    vector<Level::Tileset>::iterator getDrawSprite(int idTile);

    const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
    const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;

    // SYSTEM //
    RenderWindow*           rRenderWindow;

    string                  sLoaderVersion;
};

#endif // LEVEL_H
