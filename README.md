# TMX-Loader-TME
Loader map Tiled Map Editor for SFML C++

## Map Loader API

## Если у вас есть предложение по улучшению или нашли баг то сообщите vk.com/id219750877

Загрузка карты
Default constructor:  Level(RenderWindow *renderWindow);


Для загрузки карты нужно вызвать метод loadLevel(string), который принимает путь до файла tmx в формате CSV (другие форматы не поддерживаются).

Например: loadLevel(«maps/level1.tmx»);

Для отрисовки карты понадобится вызвать метод drawLevel();
Если попытаться загрузить еще одну карту не выгрузив текущую то загрузка не произойдет, для выгрузки текущей карты необходимо воспользоваться методом closeLevel();
***


## Остальные методы

	int getWorldWidthPixel(); - Ширина мира в пикселях (tileWidth * countTilesWidth).>
	int getWorldHeightPixel(); - Высота мира в пикселях (tileHeight * countTilesHeight).
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
    list<Polyline*> getPolylineAll();
    list<Polyline*> getPolylineWithType(string type);
    list<Polyline*> getPolylineWithName(string name);
    list<Polyline*> getPolylineWithID(int ID);
***

Типы обьектов
Регистр букв учитывается

Обьекты это то, что вы указываете в поле «Type» (Тип) в Tiled Map Editor.
Если на карте встретится более одного обьект типа «player» то загружен будет только первый попавшийся обьект, остальные будут игнорироваться.
Структура обьектов:

    struct Objects{
    	string              sObjectGroupName;
    	string              sName;
    	string              sType;

    	int                 iID;

    	void*               vData;
    };

    sName — Имя обьекта;
    sType — Тип обьектa;
    vData — Здесь вы можете ссылаться на любые ваши данные;

Круг (Circle)

    struct TShape : public Objects{
    	TShape();
    	TShape(const TShape &obj);

    	FloatRect           fRect; // Позиция и радиус

    	Texture*            tTexture;
    };

Прямоугольник (Rect)

    struct TRect : public Objects{
    	TRect();
    	TRect(const TRect &object);

    	FloatRect           fRect;

    	Texture*            tTexture;
    	Sprite*             sSprite;
    };
    
Полигон

    struct Polygon : public Objects{
    	Polygon();
    	Polygon(const Polygon &obj);

    	Vector2f            vPosition;

    	ConvexShape         cShape;

    	list<Vector2f>      lShapePoints;
    	int                 iCountShapePoints;
    };
    
    struct Polyline : public Objects{
    	Polyline();
    	Polyline(const Polyline &obj);

    	ConvexShape         cShape;

    	list<Vector2f>      lShapePoints;
    	int                 iCountShapePoints;
    };
***
Реализовывать поведение и физику обьектов предстоит вам, это предназначено для удобного отделения обьектов друг от друга.
