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
     sLoaderVersion      = "7.0";
}

void Level::loadLevel(string fileName){
    if (bLoaded)
        return;

    pugi::xml_document doc;

    cout << "\t-------------Start loading map V" << sLoaderVersion << "-------------" << endl << endl;

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

        BackGround *tempBG = new BackGround;

        tempBG->vPosition.x             = imageLayer.attribute("x").as_int();
        tempBG->vPosition.y             = imageLayer.attribute("y").as_int();

        tempStringDirs                 = imageBG.attribute("source").as_string();

        cout << "Image: " << tempStringDirs << endl;

        Texture *tempTexture = new Texture;
        tempTexture->loadFromFile(tempStringDirs);

        Sprite *tempSprite  = new Sprite(*tempTexture);

        tempBG->tTexture                = tempTexture;
        tempBG->sSprite                 = tempSprite;

        tempBG->sSprite->setPosition( tempBG->vPosition );

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

    pugi::xml_attribute spacing;
    pugi::xml_attribute marign;

    pugi::xml_node tile;
    pugi::xml_node properties;
    pugi::xml_node property;

    while (tileset){
        image = tileset.child("image");

        spacing = tileset.attribute("spacing");
        marign  = tileset.attribute("margin");

        cout << "iFirstTileID: "   << tileset.attribute("firstgid").as_int()   << endl;
        cout << "iTileWidth: "     << tileset.attribute("tilewidth").as_int()  << endl;
        cout << "iTileHeight: "    << tileset.attribute("tileheight").as_int() << endl;
        cout << "Tile directory: " << image.attribute("source").as_string()    << endl;

        Tileset *tempTileSet = new Tileset;
        tempTileSet->sName        = tileset.attribute("name").as_string();
        tempTileSet->iFirstTileID = tileset.attribute("firstgid").as_int();
        tempTileSet->iTileWidth   = tileset.attribute("tilewidth").as_int();
        tempTileSet->iTileHeight  = tileset.attribute("tileheight").as_int();

        tile = tileset.child("tile");
        while (tile){
            properties = tile.child("properties");
            property = properties.child("property");

            int iIDTile = tile.attribute("id").as_int();
            vector<TilePropertys*> tempPropsVec;

            while (property){
                TilePropertys *tempProp = new TilePropertys;

                tempProp->sName = property.attribute("name").as_string();
                tempProp->sValue = property.attribute("value").as_string();

                if (property.attribute("type") != NULL){
                    tempProp->sValue = property.attribute("type").as_string();
                }

                tempPropsVec.push_back( tempProp );
                property = property.next_sibling("property");
            }

            tempTileSet->mPropertys.insert( pair<int, vector<TilePropertys*>>(iIDTile, tempPropsVec) );


            tile = tile.next_sibling("tile");
        }


        if (spacing == NULL){
            tempTileSet->iSpacing = 0;
        } else{
            tempTileSet->iSpacing = spacing.as_int();
        }

        if (marign == NULL){
            tempTileSet->iMarign = 0;
        } else {
            tempTileSet->iMarign = marign.as_int();
        }

        tempStringDirs = image.attribute("source").as_string();

        tempTileSet->tTexture = new Texture;
        tempTileSet->tTexture->loadFromFile(tempStringDirs);

        tempTileSet->sSprite  = new Sprite;
        tempTileSet->sSprite->setTexture( *tempTileSet->tTexture );
        tempTileSet->sSprite->setOrigin( tempTileSet->iTileWidth / 2, tempTileSet->iTileHeight / 2);

        int countTileX  = (tempTileSet->tTexture->getSize().x - tempTileSet->iMarign) / (tempTileSet->iTileWidth + tempTileSet->iSpacing);
        int countTileY  = (tempTileSet->tTexture->getSize().y - tempTileSet->iMarign) / (tempTileSet->iTileHeight + tempTileSet->iSpacing);
        int startTileID = tempTileSet->iFirstTileID;

        cout << "Tiles in " << tempTileSet->sName << " : " << countTileX * countTileY << endl;

        tempTileSet->iTileCount   = countTileX * countTileY + tempTileSet->iFirstTileID-1;

        cout << "iTileCount: " << tempTileSet->iTileCount << endl << endl;


        for (int i = 0; i < countTileY; i++){
            for (int j = 0; j < countTileX; j++){
                IntRect tempRect;

                tempRect.left   = j * (tempTileSet->iTileWidth  + tempTileSet->iSpacing) + tempTileSet->iMarign;
                tempRect.top    = i * (tempTileSet->iTileHeight + tempTileSet->iSpacing) + tempTileSet->iMarign;

                tempRect.width  = tempTileSet->iTileWidth;
                tempRect.height = tempTileSet->iTileHeight;

                tempTileSet->mTiles.insert(std::pair<int, IntRect>(startTileID, tempRect));
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

    pugi::xml_attribute opacity;
    float tempOpacity = 0;

    /////////////////// ЗАГРУЗКА ДАННЫХ СЛОЕВ ///////////////////

    while (layer){
        outCountLayers++;
        opacity = layer.attribute("opacity");

        cout << "Loading " << outCountLayers << " layer";
        cout << "Layer name: " << layer.attribute("name").as_string() << endl;

        Layer *tempLayer = new Layer;
        tempLayer->iWidth   = layer.attribute("width").as_int();
        tempLayer->iHeight  = layer.attribute("height").as_int();
        tempLayer->iOffestX = layer.attribute("offsetx").as_int();
        tempLayer->iOffestY = layer.attribute("offsety").as_int();

        if (opacity == NULL){
            tempOpacity = 1;
        } else {
            tempOpacity = opacity.as_float();
        }

        tempLayer->iOpacity = int(tempOpacity * 255);


        //tempLayer->iOpacity = 255 * tempOpacity;

        cout << tempLayer->iOpacity << endl;

        tempLayer->iLayer = new unsigned*[tempLayer->iHeight];
        for (int i = 0; i < tempLayer->iHeight; i++)
            tempLayer->iLayer[i] = new unsigned[tempLayer->iWidth];

        string TempLayerString = data.text().as_string();
        string tempStrNum;

        int layerX = 0;
        int layerY = 0;

        for (char i : TempLayerString) {
            if (i != ',') {
                tempStrNum += i;
            } else {
                tempLayer->iLayer[layerY][layerX] = unsigned(atoi(tempStrNum.c_str()));
                tempStrNum.clear();
                layerX++;
            }
            if (layerX == tempLayer->iWidth){
                layerX = 0;
                layerY++;
            }
        }
        tempLayer->iLayer[layerY][layerX] = unsigned(atoi(tempStrNum.c_str()));
        vLayers.push_back(tempLayer);

        layer = layer.next_sibling("layer");
        data = layer.child("data");
    }

    /////////////////// ЗАГРУЗКА ДАННЫХ ОБЬЕКТОВ ///////////////////

    cout << endl << endl << "OBJECTS: " << endl;

    pugi::xml_node objectgroup = map.child("objectgroup");
    pugi::xml_node object = objectgroup.child("object");
    pugi::xml_node polygon;
    pugi::xml_node polyline;
    pugi::xml_node ellipse;

    while (objectgroup){
        object = objectgroup.child("object");
        while (object){

            polygon = object.child("polygon");
            polyline = object.child("polyline");
            ellipse = object.child("ellipse");



            if (ellipse != NULL && polyline == NULL && polygon == NULL){
                Shape_ML *temp = new Shape_ML;

                temp->sObjectGroupName  = objectgroup.attribute("name").as_string();
                temp->iID   = object.attribute("id").as_int();
                temp->sType = object.attribute("type").as_string();
                temp->sName = object.attribute("name").as_string();
                temp->fRect.top = object.attribute("y").as_float();
                temp->fRect.left = object.attribute("x").as_float();
                temp->fRect.width = object.attribute("width").as_float();
                temp->fRect.height = object.attribute("height").as_float();
                temp->tTexture = nullptr;

                lShapes.push_back(temp);
            }

            if (ellipse == NULL && polyline == NULL && polygon == NULL){
                Rect_ML *temp = new Rect_ML;

                temp->sObjectGroupName  = objectgroup.attribute("name").as_string();
                temp->iID   = object.attribute("id").as_int();
                temp->sType = object.attribute("type").as_string();
                temp->sName = object.attribute("name").as_string();
                temp->fRect.top = object.attribute("y").as_float();
                temp->fRect.left = object.attribute("x").as_float();
                temp->fRect.width = object.attribute("width").as_float();
                temp->fRect.height = object.attribute("height").as_float();
                temp->tTexture = nullptr;
                temp->sSprite = nullptr;
                temp->vData = nullptr;

                lRects.push_back(temp);

                //cout << "Name: " << temp->sName << " Type: " << temp->sType << endl;
            }

            if (ellipse != NULL && polyline != NULL && polygon == NULL){
                Polyline_ML *temp = new Polyline_ML;

                temp->sObjectGroupName  = objectgroup.attribute("name").as_string();

                temp->sName = object.attribute("name").as_string();
                temp->sType = object.attribute("type").as_string();
                temp->lShapePoints = stringToData( polygon.attribute("points").as_string() );

                temp->iCountShapePoints = 0;
                for (auto it : temp->lShapePoints) temp->iCountShapePoints++;

                temp->cShape.setPointCount( temp->iCountShapePoints );
                int i = 0;
                for (auto it = temp->lShapePoints.begin(); it != temp->lShapePoints.end(); it++, i++){
                    temp->cShape.setPoint(i, (*it));
                }

                lPolylines.push_back(temp);
            }

            if (ellipse == NULL && polyline == NULL && polygon != NULL){
                Polygon_ML *temp = new Polygon_ML;

                temp->sObjectGroupName  = objectgroup.attribute("name").as_string();
                temp->sName = object.attribute("name").as_string();
                temp->sType = object.attribute("type").as_string();
                temp->vPosition.x = object.attribute("x").as_float();
                temp->vPosition.y = object.attribute("y").as_float();
                temp->lShapePoints = stringToData( polygon.attribute("points").as_string() );

                temp->iCountShapePoints = 0;
                for (auto it : temp->lShapePoints) temp->iCountShapePoints++;

                temp->cShape.setPointCount( temp->iCountShapePoints );
                int i = 0;
                for (auto it = temp->lShapePoints.begin(); it != temp->lShapePoints.end(); it++, i++){
                    temp->cShape.setPoint(i, (*it));
                }
                temp->cShape.setPosition( temp->vPosition );
                temp->cShape.setFillColor(sf::Color::Cyan);

                lPolygons.push_back(temp);
                //cout << "Name: " << temp->sName << " Type: " << temp->sType << endl;
            }


            object = object.next_sibling("object");
        }

        objectgroup = objectgroup.next_sibling("objectgroup");
    }

    cout << "Count Objects: " << lRects.size() + lPolygons.size() + lPolylines.size() + lShapes.size() << endl;

    cout << "\n\t-------------Map Loaded-------------" << endl;
    bLoaded = true;
}

void Level::drawLevel(){
    ////////////////////////// ОТРИСОВКА ИЗОБРАЖЕНИЙ //////////////////////////

    for (auto it = vBackGrounds.begin(); it != vBackGrounds.end(); it++){
        rRenderWindow->draw( *(*it)->sSprite );
    }

    ////////////////////////// ОТРИСОВКА КАРТЫ //////////////////////////
    unsigned tempID = 0;
    vector<Tileset*>::iterator tempTileset;
    int opacity = 1;
    for (auto itLayer = vLayers.begin(); itLayer != vLayers.end(); itLayer++){
        opacity = (*itLayer)->iOpacity;
        for (int i = 0; i < (*itLayer)->iHeight; i++){
            for (int j = 0; j < (*itLayer)->iWidth; j++){
                tempID = (*itLayer)->iLayer[i][j];
                if (tempID == 0) continue;

                bool flipped_horizontally = (tempID & FLIPPED_HORIZONTALLY_FLAG);
                bool flipped_vertically   = (tempID & FLIPPED_VERTICALLY_FLAG);
                bool flipped_diagonally   = (tempID & FLIPPED_DIAGONALLY_FLAG);

                tempID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
                tempTileset = getDrawSprite( int(tempID) );
                (*tempTileset)->sSprite->setColor(Color(255, 255, 255, opacity));

                if (flipped_horizontally && !flipped_vertically && flipped_diagonally){
                    (*tempTileset)->sSprite->rotate(90);
                }

                if (!flipped_horizontally && flipped_vertically && flipped_diagonally){
                    (*tempTileset)->sSprite->rotate(-90);
                }

                if (flipped_horizontally && flipped_vertically && !flipped_diagonally){
                    (*tempTileset)->sSprite->rotate(180);
                }

                (*tempTileset)->sSprite->setPosition( (j * iTileHeight + iTileHeight / 2) + (*itLayer)->iOffestX,
                                                      (i   * iTileWidth + iTileWidth / 2) + (*itLayer)->iOffestY);

                rRenderWindow->draw( *(*tempTileset)->sSprite );

                if (flipped_horizontally && !flipped_vertically && flipped_diagonally){
                    (*tempTileset)->sSprite->rotate(-90);
                }
                if (!flipped_horizontally && flipped_vertically && flipped_diagonally){
                    (*tempTileset)->sSprite->rotate(90);
                }

                if (flipped_horizontally && flipped_vertically && !flipped_diagonally){
                    (*tempTileset)->sSprite->rotate(-180);
                }
            }
        }

    }
}

vector<Tileset*>::iterator Level::getDrawSprite(int idTile){
    auto mapIT = (*vTilesets.begin())->mTiles.begin();
    vector<Tileset*>::iterator it = vTilesets.begin();

    for (; it != vTilesets.end(); it++){
        mapIT = (*it)->mTiles.find( idTile );
        if (mapIT != (*it)->mTiles.end())
            break;
    }

    (*it)->sSprite->setTextureRect( mapIT->second );

    return it;
}

void Level::closeLevel(){
    for (auto it = lShapes.begin(); it != lShapes.end(); it++){
        delete (*it)->tTexture;
    }

    for (auto it = lRects.begin(); it != lRects.end(); it++){
        delete (*it)->tTexture;
        delete (*it)->sSprite;
    }

    lRects.clear();
    lPolygons.clear();
    lPolylines.clear();
    lShapes.clear();

    for (auto it = vBackGrounds.begin(); it != vBackGrounds.end(); it++){
        delete (*it)->tTexture;
        delete (*it)->sSprite;
        delete (*it);
    }

    vBackGrounds.clear();

    for (auto it = vTilesets.begin(); it != vTilesets.end(); it++){
        delete (*it)->tTexture;
        delete (*it)->sSprite;
        (*it)->mTiles.clear();
        delete (*it);
    }

    vTilesets.clear();

    for (auto it = vLayers.begin(); it != vLayers.end(); it++){
        for (int i = 0; i < (*it)->iHeight; i++){
            delete [] (*it)->iLayer[i];
        }
        delete (*it)->iLayer;
        delete (*it);
    }

    vLayers.clear();

    iCountAllLayers = 0;
    iCountAllTiles  = 0;
    iTileHeight     = 0;
    iTileWidth      = 0;

    bLoaded         = false;
}

list<Vector2f> Level::stringToData(string sData){
    list<Vector2f> temp;
    list<string> pointsStr;

    /////////////////////////////////
    string sTemps;
    for (char i : sData){
        if (i != ' '){
            sTemps += i;
        } else {
            pointsStr.push_back( sTemps );
            sTemps.clear();
        }
    }
    pointsStr.push_back( sTemps );
    sTemps.clear();
    /////////////////////////////////

    Vector2f tempVec;
    bool isX = true;
    for (list<string>::iterator it = pointsStr.begin(); it != pointsStr.end(); it++){
        for (char i : (*it)){
            if (i != ','){
                sTemps += i;
            } else {
                if (isX)  tempVec.x = atof(sTemps.c_str());
                if (!isX) tempVec.y = atof(sTemps.c_str());
                sTemps.clear();
                isX = false;
            }
        }
        isX = true;
        tempVec.y = atof(sTemps.c_str());
        temp.push_back(tempVec);
        sTemps.clear();
    }

    return temp;
}

vector<TilePropertys*> Level::getTilePropertys(string tilesetName, int tileID){
    Tileset *tempTileset = nullptr;

    if (vTilesets.size() > 0){
        for (auto it = vTilesets.begin(); it != vTilesets.end(); it++){
            if (strcmp((*it)->sName.c_str(), tilesetName.c_str()) == 0){
                tempTileset = (*it);
                break;
            }
        }
    }

    if (tempTileset != nullptr){
        auto it = tempTileset->mPropertys.find(tileID);
        if (tempTileset->mPropertys.size() > 0){
            //if ((*it).second.size() > 0){
                return it->second;
            //}
        }
    }

    vector<TilePropertys*> clearVector;
    return clearVector;
}

template <class T>
T Level::getObjectsName(T& object, string name){
    T temp;
    for (auto it = object.begin(); it != object.end(); it++){
        if (strcmp((*it)->sName.c_str(), name.c_str()  ) == 0){
            temp.push_back( (*it) );
        }
    }
    return temp;
}

template <class T>
T Level::getObjectsType(T& object, string type){
    T temp;
    for (auto it = object.begin(); it != object.end(); it++){
        if (strcmp((*it)->sType.c_str(), type.c_str()  ) == 0){
            temp.push_back( (*it) );
        }
    }
    return temp;
}

template <class T>
T Level::getObjectsID(T& object, int ID){
    T temp;
    for (auto it = object.begin(); it != object.end(); it++){
        if ( (*it)->iID == ID ){
            temp.push_back( (*it) );
        }
    }
    return temp;
}

template <class T>
T Level::getOBjectsObjectGroup(T& object, string objGroup){
    T temp;
    for (auto it = object.begin(); it != object.end(); it++){
        if (strcmp((*it)->sObjectGroupName.c_str(), objGroup.c_str()  ) == 0){
            temp.push_back( (*it) );
        }
    }
    return temp;
}

list<Polyline_ML*> Level::getPolylineWithObjectGroup(string objGroup){
    return getOBjectsObjectGroup<list<Polyline_ML*>>(lPolylines, objGroup);
}

list<Polyline_ML*>& Level::getPolylineAll(){
    return lPolylines;
}

list<Polyline_ML*> Level::getPolylineWithType(string type){
    return getObjectsType<list<Polyline_ML*>>(lPolylines, type);
}

list<Polyline_ML*> Level::getPolylineWithName(string name){
    return getObjectsName<list<Polyline_ML*>>(lPolylines, name);
}

list<Polyline_ML*> Level::getPolylineWithID(int ID){
    return getObjectsID<list<Polyline_ML*>>(lPolylines, ID);
}

list<Rect_ML*> Level::getRectsWithObjectGroup(string objGroup){
    return getOBjectsObjectGroup<list<Rect_ML*>>(lRects, objGroup);
}

list<Rect_ML*>& Level::getRectsAll(){
    return lRects;
}

list<Rect_ML*>  Level::getRectsWithType(string type){
    return getObjectsType<list<Rect_ML*>>(lRects, type);
}

list<Rect_ML*>  Level::getRectsWithName(string name){
    return getObjectsName<list<Rect_ML*>>(lRects, name);
}

list<Rect_ML*> Level::getRectsWithID(int ID){
    return getObjectsID<list<Rect_ML*>>(lRects, ID);
}

list<Polygon_ML*>& Level::getPolygonsAll(){
    return lPolygons;
}

list<Polygon_ML*> Level::getPolygonsWithObjectGroup(string objGroup){
    return getOBjectsObjectGroup<list<Polygon_ML*>>(lPolygons, objGroup);
}

list<Polygon_ML*> Level::getPolygonsWithType(string type){
    return getObjectsType<list<Polygon_ML*>>(lPolygons, type);
}

list<Polygon_ML*> Level::getPolygonsWithName(string name){
    return getObjectsName<list<Polygon_ML*>>(lPolygons, name);
}

list<Polygon_ML*> Level::getPolygonsWithID(int ID){
    return getObjectsID<list<Polygon_ML*>>(lPolygons, ID);
}

list<Shape_ML*> Level::getShapesWithObjectGroup(string objGroup){
    return getOBjectsObjectGroup<list<Shape_ML*>>(lShapes, objGroup);
}

list<Shape_ML*>&  Level::getShapesAll(){
    return lShapes;
}

list<Shape_ML*>   Level::getShapesWithType(string type){
    return getObjectsType<list<Shape_ML*>>(lShapes, type);
}

list<Shape_ML*>   Level::getShapesWithName(string name){
    return getObjectsName<list<Shape_ML*>>(lShapes, name);
}

list<Shape_ML*>   Level::getShapesWithID(int ID){
    return getObjectsID<list<Shape_ML*>>(lShapes, ID);
}

int Level::getWorldWidthPixel(){
    return iFullWorldSizeWidth;
}

int Level::getWorldHeightPixel(){
    return iFullWorldSizeHeight;
}

Level::~Level(){
    closeLevel();
}
