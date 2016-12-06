#ifndef LEVEL_H
#define LEVEL_H

/////////// PUGI ///////////
#include <pugixml.hpp>

/////////// SFML ///////////
#include <SFML/Graphics.hpp>
using namespace sf;

/////////// STL ///////////
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

class Level{
public:
    Level(RenderWindow *renderWindow);
    ~Level();

    struct Player{
        string              sName;
        string              sType;

        FloatRect           fRect;
        Texture*            tTexture;
        Sprite*             sSprite;

        int                 iHealth;
        int                 iMana;
        int                 iScore;

        void*               vData;
    };

    struct Enemy{
        string              sName;
        string              sType;

        FloatRect           fRect;
        Texture*            tTexture;
        Sprite*             sSprite;

        int                 iHealth;

        void*               vData;
    };

    struct Object{
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
    list<Enemy*>& getEnemyObjects();
    list<Object*>& getOtherObjects();
    list<Object*>& getBrickObjects();
    list<Object*>& getPlatformObjects();
    list<Object*>& getPlatform_mObjects();
    list<Object*>& getPlatform_mvObjects();
    list<Object*>& getPlatform_mhObjects();

    Player* getPLayerObject();

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
    list<Object*>          lOthers;
    list<Object*>          lBricks;
    list<Object*>          lPlatforms;
    list<Object*>          lPlatforms_m; // MOVED
    list<Object*>          lPlatforms_mh; // MOVED HORISINTALY
    list<Object*>          lPlatforms_mv; // MOVED VERTICALY
    list<Enemy*>           lEnemys;

    // PLAYER
    Player*                 pPlayer;

    // Возвращает таилсет на отрисовку
    vector<Level::Tileset>::iterator getDrawSprite(int idTile);

    // Помошник для удаления
    template <class T>
    void delObject(T &obj);

    const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
    const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;

    // SYSTEM //
    System*                 sSystem;
    RenderWindow*           rRenderWindow;

    string                  sLoaderVersion;
};

#endif // LEVEL_H
