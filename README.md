# TMX-Loader-TME
Loader map by Tiled Map Editor

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
	list<Enemy*>& getEnemyObjects(); - Обьекты врагов
	list<Object*>& getOtherObjects(); - Остальные обьекты (которые не подошли к другим типам)
	list<Object*>& getBrickObjects(); - Обьекты кирпичей (стен)
	list<Object*>& getPlatformObjects(); - Обьекты неподвижных платформ
	list<Object*>& getPlatform_mObjects(); - Обьекты пдвижных платформ
	list<Object*>& getPlatform_mvObjects(); - Обьекты пдвижных платформ
	list<Object*>& getPlatform_mhObjects(); - Обьекты пдвижных платформ
	Player* getPLayerObject(); Обьект игрока
***

Типы обьектов
Регистр букв учитывается
Обьекты могут быть только прямоугольными!

	player — обьект игрока
	brick — Неподвижный твердый обьект
	platform — Неподвижная платформа
	platform_m — Подвижная платформа
	platform_mh — Подвижная платформа по горизонтали
	platform_mv — Подвижная платформа по вертикали
	enemy — Враг
	other — Остальное

Обьекты это то, что вы указываете в поле «Type» (Тип) в Tiled Map Editor.
Если на карте встретится более одного обьект типа «player» то загружен будет только первый попавшийся обьект, остальные будут игнорироваться.
Структуры обьектов
Обьекты: «brick, platform, platform_m, platform_mh, platform_mv, other» - имеют следующую структуру:

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

Обьект: «player» - имеет структуру:

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

Обьект «enemy» - имеет структуру:

    struct Enemy{
        string              sName;
        string              sType;
        FloatRect           fRect;
        Texture*            tTexture;
        Sprite*             sSprite;
        int                 iHealth;
        void*               vData;
    };
***
Реализовывать поведение и физику обьектов предстоит вам, это предназначено для удобного отделения обьектов друг от друга.
