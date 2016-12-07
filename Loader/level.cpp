#include "level.h"

Level::Level(RenderWindow *renderWindow){
     rRenderWindow = renderWindow;
     iCountAllTiles      = 0;
     iCountAllLayers     = 0;
     iTileHeight         = 0;
     iTileWidth          = 0;
     iFullWorldSizeWidth = 0;
     iFullWorldSizeHeight= 0;
     bLoaded             = false;
     sLoaderVersion      = "3.0";
}

void Level::loadLevel(string fileName){
    if (bLoaded)
        return;

    pugi::xml_document doc;

    cout << "MAP LOADDER: " << sLoaderVersion << "\n\t-------------Start loading map-------------" << endl << endl;

    cout << "Load " << fileName << " Map" << endl;

    if (!doc.load_file(fileName.c_str())){
        cout << "File not Load" << endl;
        return;
    }

    pugi::xml_node map        = doc.child("map");
    pugi::xml_node tileset    = map.child("tileset");
    pugi::xml_node image      = tileset.child("image");
    pugi::xml_node imageLayer = map.child("imagelayer");
    pugi::xml_node imageBG    = imageLayer.child("image");

    string tempStringDirs;

    /////////////////// ЗАГРУЗКА ДАННЫХ ИЗОБРАЖЕНИЙ ///////////////////

    while (imageLayer){

        BackGround tempBG;

        tempBG.vPosition.x             = imageLayer.attribute("x").as_int();
        tempBG.vPosition.y             = imageLayer.attribute("y").as_int();

        tempStringDirs                 = imageBG.attribute("source").as_string();

        cout << "Image: " << tempStringDirs << endl;

        Texture *tempTexture = new Texture;
        tempTexture->loadFromFile(tempStringDirs);

        Sprite *tempSprite  = new Sprite(*tempTexture);

        tempBG.tTexture                = tempTexture;
        tempBG.sSprite                 = tempSprite;

        tempBG.sSprite->setPosition( tempBG.vPosition );

        vBackGrounds.push_back( tempBG );

        imageLayer = imageLayer.next_sibling("imagelayer");
        imageBG = imageLayer.child("image");
    }
    cout << endl;

    /////////////////// ЗАГРУЗКА ДАННЫХ ТАЙЛОВ ///////////////////

    iTileWidth =  map.attribute("tilewidth").as_int();
    iTileHeight = map.attribute("tileheight").as_int();
    iFullWorldSizeWidth = map.attribute("width").as_int() * iTileWidth;
    iFullWorldSizeHeight = map.attribute("height").as_int() * iTileHeight;

    while (tileset){
        image = tileset.child("image");

        cout << "iFirstTileID: "   << tileset.attribute("firstgid").as_int()   << endl;
        cout << "iTileWidth: "     << tileset.attribute("tilewidth").as_int()  << endl;
        cout << "iTileHeight: "    << tileset.attribute("tileheight").as_int() << endl;
        cout << "tempStringDirs: " << image.attribute("source").as_string()    << endl;

        Tileset tempTileSet;
        tempTileSet.iFirstTileID = tileset.attribute("firstgid").as_int();
        tempTileSet.iTileWidth   = tileset.attribute("tilewidth").as_int();
        tempTileSet.iTileHeight  = tileset.attribute("tileheight").as_int();
        tempStringDirs = image.attribute("source").as_string();

        tempTileSet.tTexture = new Texture;
        tempTileSet.tTexture->loadFromFile(tempStringDirs);

        tempTileSet.sSprite  = new Sprite;
        tempTileSet.sSprite->setTexture( *tempTileSet.tTexture );
        tempTileSet.sSprite->setOrigin( tempTileSet.iTileWidth / 2, tempTileSet.iTileHeight / 2);

        int countTileX  = tempTileSet.tTexture->getSize().x / tempTileSet.iTileWidth;
        int countTileY  = tempTileSet.tTexture->getSize().y / tempTileSet.iTileHeight;
        int startTileID = tempTileSet.iFirstTileID;

        tempTileSet.iTileCount   = countTileX * countTileY + tempTileSet.iFirstTileID-1;

        cout << "iTileCount: " << tempTileSet.iTileCount << endl << endl;

        for (int i = 0; i < countTileY; i++){
            for (int j = 0; j < countTileX; j++){
                IntRect tempRect;
                tempRect.left   = j * tempTileSet.iTileWidth;
                tempRect.top    = i * tempTileSet.iTileHeight;
                tempRect.width  = tempTileSet.iTileWidth;
                tempRect.height = tempTileSet.iTileHeight;

                tempTileSet.mTiles.insert(std::pair<int, IntRect>(startTileID, tempRect));
                startTileID++;
            }
        }

        vTilesets.push_back( tempTileSet );
        iCountAllLayers++;
        tileset = tileset.next_sibling("tileset");
    }


    pugi::xml_node layer = map.child("layer");
    pugi::xml_node data  = layer.child("data");

    int outCountLayers = 0;

    /////////////////// ЗАГРУЗКА ДАННЫХ СЛОЕВ ///////////////////

    while (layer){
        outCountLayers++;

        cout << "Loading " << outCountLayers << " layer";
        cout << "Layer name: " << layer.attribute("name").as_string() << endl;

        Layer tempLayer;
        tempLayer.iWidth  = layer.attribute("width").as_int();
        tempLayer.iHeight = layer.attribute("height").as_int();

        tempLayer.iLayer = new int*[tempLayer.iHeight];
        for (int i = 0; i < tempLayer.iHeight; i++)
            tempLayer.iLayer[i] = new int[tempLayer.iWidth];

        string TempLayerString = data.text().as_string();
        string tempStrNum;

        int layerX = 0;
        int layerY = 0;

        for (char i : TempLayerString) {
            if (i != ',') {
                tempStrNum += i;
            } else {
                tempLayer.iLayer[layerY][layerX] = atoi(tempStrNum.c_str());
                tempStrNum.clear();
                layerX++;
            }
            if (layerX == tempLayer.iWidth){
                layerX = 0;
                layerY++;
            }
        }
        tempLayer.iLayer[layerY][layerX] = atoi(tempStrNum.c_str());
        vLayers.push_back(tempLayer);

        layer = layer.next_sibling("layer");
        data = layer.child("data");
    }

    /////////////////// ЗАГРУЗКА ДАННЫХ ОБЬЕКТОВ ///////////////////

    cout << endl << endl << "OBJECTS: " << endl;

    pugi::xml_node objectgroup = map.child("objectgroup");
    pugi::xml_node object = objectgroup.child("object");

    bool LOADED_OBJECT_FLAG = false;

    while (objectgroup){
        object = objectgroup.child("object");
        while (object){
            LOADED_OBJECT_FLAG = false;

            Object *temp = new Object;

            temp->sType = object.attribute("type").as_string();
            temp->sName = object.attribute("name").as_string();

            temp->fRect.top = object.attribute("x").as_float();
            temp->fRect.left = object.attribute("y").as_float();
            temp->fRect.width = object.attribute("width").as_float();
            temp->fRect.height = object.attribute("height").as_float();

            temp->tTexture = nullptr;
            temp->sSprite = nullptr;
            temp->vData = nullptr;

            cout << "Name: " << temp->sName << " Type: " << temp->sType << endl;

            if (strcmp(temp->sType.c_str(), "brick") == 0){ // BRICK
                lBricks.push_back(temp);
                LOADED_OBJECT_FLAG = true;
            }

            if (strcmp(temp->sType.c_str(), "platform") == 0){ // PLATFORM
                lPlatforms.push_back(temp);
                LOADED_OBJECT_FLAG = true;
            }

            if (strcmp(temp->sType.c_str(), "platform_m") == 0){ // PLATFORM_M
                lPlatforms_m.push_back(temp);
                LOADED_OBJECT_FLAG = true;
            }

            if (strcmp(temp->sType.c_str(), "platform_mh") == 0){ // PLATFORM_MH
                lPlatforms_mh.push_back(temp);
                LOADED_OBJECT_FLAG = true;
            }

            if (strcmp(temp->sType.c_str(), "platform_mv") == 0){ // PLATFORM_MV
                lPlatforms_mv.push_back(temp);
                LOADED_OBJECT_FLAG = true;
            }

            if (strcmp(temp->sType.c_str(), "enemy") == 0){ // ENEMY
                Enemy *tempp = new Enemy;

                tempp->sName = temp->sName;
                tempp->sType = temp->sType;
                tempp->fRect = temp->fRect;
                tempp->tTexture = nullptr;
                tempp->sSprite = nullptr;
                tempp->vData = nullptr;
                tempp->iHealth = 0;

                lEnemys.push_back(tempp);
                LOADED_OBJECT_FLAG = true;
            }

            if (strcmp(temp->sType.c_str(), "player") == 0 && pPlayer == nullptr){ // PLAYER
                Player *tempp = new Player;
                tempp->sName = temp->sName;
                tempp->sType = temp->sType;
                tempp->fRect = temp->fRect;
                tempp->tTexture = nullptr;
                tempp->sSprite = nullptr;
                tempp->iHealth = 0;
                tempp->iMana = 0;
                tempp->iScore = 0;
                tempp->vData = nullptr;
                pPlayer = tempp;
                LOADED_OBJECT_FLAG = true;
            }

            if (!LOADED_OBJECT_FLAG){
                lOthers.push_back(temp);
                LOADED_OBJECT_FLAG = true;
            }

            object = object.next_sibling("object");
        }

        objectgroup = objectgroup.next_sibling("objectgroup");
    }

    cout << "\nOBJECT LIST" << endl;

    cout << "Other: " << lOthers.size() << endl;
    cout << "Enemy: " << lEnemys.size() << endl;
    cout << "Bricks: " << lBricks.size() << endl;
    cout << "Platforms: " << lPlatforms.size() << endl;
    cout << "Platforms_m: " << lPlatforms_m.size() << endl;
    cout << "Platforms_mv: " << lPlatforms_mv.size() << endl;
    cout << "Platforms_mh: " << lPlatforms_mh.size() << endl;


    cout << "\n\t-------------Map Loaded-------------" << endl;
    bLoaded = true;
}

void Level::drawLevel(){
    ////////////////////////// ОТРИСОВКА ИЗОБРАЖЕНИЙ //////////////////////////

    for (auto it = vBackGrounds.begin(); it != vBackGrounds.end(); it++){
        rRenderWindow->draw( *it->sSprite );
    }

    ////////////////////////// ОТРИСОВКА КАРТЫ //////////////////////////
    int tempID = 0;
    vector<Tileset>::iterator tempTileset;
    for (auto itLayer = vLayers.begin(); itLayer != vLayers.end(); itLayer++){
        for (int i = 0; i < itLayer->iHeight; i++){
            for (int j = 0; j < itLayer->iWidth; j++){
                tempID = itLayer->iLayer[i][j];
                if (tempID == 0) continue;

                bool flipped_horizontally = (tempID & FLIPPED_HORIZONTALLY_FLAG);
                bool flipped_vertically = (tempID & FLIPPED_VERTICALLY_FLAG);
                bool flipped_diagonally = (tempID & FLIPPED_DIAGONALLY_FLAG);

                tempID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
                tempTileset = getDrawSprite( tempID );

                if (flipped_horizontally && !flipped_vertically && flipped_diagonally){
                    tempTileset->sSprite->rotate(90);
                }

                if (!flipped_horizontally && flipped_vertically && flipped_diagonally){
                    tempTileset->sSprite->rotate(-90);
                }

                if (flipped_horizontally && flipped_vertically && !flipped_diagonally){
                    tempTileset->sSprite->rotate(180);
                }

                tempTileset->sSprite->setPosition( j * iTileHeight + iTileHeight / 2, i * iTileWidth + iTileWidth / 2);
                rRenderWindow->draw( *tempTileset->sSprite );

                if (flipped_horizontally && !flipped_vertically && flipped_diagonally){
                    tempTileset->sSprite->rotate(-90);
                }
                if (!flipped_horizontally && flipped_vertically && flipped_diagonally){
                    tempTileset->sSprite->rotate(90);
                }

                if (flipped_horizontally && flipped_vertically && !flipped_diagonally){
                    tempTileset->sSprite->rotate(-180);
                }
            }
        }

    }
}

vector<Level::Tileset>::iterator Level::getDrawSprite(int idTile){
    auto mapIT = vTilesets.begin()->mTiles.begin();
    auto it = vTilesets.begin();

    for (; it != vTilesets.end(); it++){
        mapIT = it->mTiles.find( idTile );
        if (mapIT != it->mTiles.end())
            break;
    }

    it->sSprite->setTextureRect( mapIT->second );

    return it;
}

template <class T>
void Level::delObject(T &obj){
    for (auto it = obj.begin(); it != obj.end(); it++){
        if ((*it)->tTexture != nullptr)
            delete (*it)->tTexture;
        if ((*it)->sSprite != nullptr){
            delete (*it)->sSprite;
        }
        delete (*it)->vData;
        delete (*it);
    }
    obj.clear();
}

void Level::closeLevel(){
    delObject<list<Object*>>(lBricks);
    delObject<list<Object*>>(lOthers);
    delObject<list<Object*>>(lPlatforms);
    delObject<list<Object*>>(lPlatforms_m);
    delObject<list<Object*>>(lPlatforms_mh);
    delObject<list<Object*>>(lPlatforms_mv);


    for (auto it = vBackGrounds.begin(); it != vBackGrounds.end(); it++){
        delete it->tTexture;
        delete it->sSprite;
    }

    vBackGrounds.clear();

    for (auto it = vTilesets.begin(); it != vTilesets.end(); it++){
        delete it->tTexture;
        delete it->sSprite;
        it->mTiles.clear();
    }

    vTilesets.clear();

    for (auto it = vLayers.begin(); it != vLayers.end(); it++){
        for (int i = 0; i < it->iHeight; i++){
            delete [] it->iLayer[i];
        }
        delete it->iLayer;
    }

    vLayers.clear();

    iCountAllLayers = 0;
    iCountAllTiles = 0;
    iTileHeight = 0;
    iTileWidth = 0;

    delete pPlayer;
    pPlayer = nullptr;

    bLoaded = false;
}

int Level::getWorldWidthPixel(){
    return iFullWorldSizeWidth;
}

int Level::getWorldHeightPixel(){
    return iFullWorldSizeHeight;
}

list<Level::Enemy*>& Level::getEnemyObjects(){
    return lEnemys;
}

list<Level::Object*>& Level::getOtherObjects(){
    return lOthers;
}

list<Level::Object*>& Level::getBrickObjects(){
    return lBricks;
}

list<Level::Object*>& Level::getPlatformObjects(){
    return lPlatforms;
}

list<Level::Object*>& Level::getPlatform_mObjects(){
    return lPlatforms_m;
}

list<Level::Object*>& Level::getPlatform_mvObjects(){
    return lPlatforms_mv;
}

list<Level::Object*>& Level::getPlatform_mhObjects(){
    return lPlatforms_mh;
}

Level::Player* Level::getPLayerObject(){
    return pPlayer;
}

Level::~Level(){
    closeLevel();
}
