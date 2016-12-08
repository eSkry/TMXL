# TMX-Loader-TME
Loader map Tiled Map Editor for SFML C++

## Map Loader API
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
    list<Object*>& getAllObjects(); - Возвращает все обьекты
    list<Object*>  getTypeObjects(string type); - Возвращает все обьекты с данным типом
    list<Object*>  getNameObjects(string name); - Возвращает все обьекты с данным именем
***

Типы обьектов
Регистр букв учитывается
Обьекты могут быть только прямоугольными!


Обьекты это то, что вы указываете в поле «Type» (Тип) в Tiled Map Editor.
Если на карте встретится более одного обьект типа «player» то загружен будет только первый попавшийся обьект, остальные будут игнорироваться.
Структура обьектов:

    struct Object{
    	string              sName;
    	string              sType;
    	FloatRect           fRect;
    	Texture*            tTexture;
    	Sprite*             sSprite;
    	void*               vData;
    };

    sName — Имя обьекта;
    sType — Тип обьектa;
    fRect — Прямоугольник обьекта;
    tTexture — Текстура (По умолчанию nullptr, саму текстуру загружаете — вы);
    sSprite — Спрайт (По умолчанию nullptr, спрайт создаете — вы);
    vData — Здесь вы можете ссылаться на любые ваши данные;

***
Реализовывать поведение и физику обьектов предстоит вам, это предназначено для удобного отделения обьектов друг от друга.
