/**
 * @file Config.h Данный фаил разрешено редактировать
 * @details В данном файле определены базовые типы для загрузчика карт
 */
#ifndef TMXL_CONFIG_H
#define TMXL_CONFIG_H

#define MAKE_STR(x) _MAKE_STR(x)
#define _MAKE_STR(x) #x

#ifndef TMXL_VERSION // If not defined version in CMakeLists.txt then use default value "0.0.0"
#define TMXL_VERSION "0.0.0"
#endif

#include <stddef.h> // Used for std::size_t
#include <string>

#include <SFML/System/String.hpp>

namespace TMXL {
    // Used size type
    using TLSize_t = std::size_t;

    inline const char* getTMXLVersion() {
        return MAKE_STR(TMXL_VERSION);
    }

}

#endif //TMXL_CONFIG_H

// TODO: Стоит добавить в функционал библиотеки - освещение, имеется готовая библиотека освещения для SFML - LTBL2
// https://github.com/222464/LTBL2

// TODO: Подумать по поводу шейдеров
// Можно добавить возможность отрисовки карты с применением шейдеров.
// В редакторе Tiled можно указать имя шейдера, а загрузчик будет искать его.

// TODO: Возможность смены дня и ночи (уже идет упор на существовании освещения карты)

// TODO: Сделать класс преобразующий загружаемые данные из карты для работы в box2d
// Но это потребует связки физического тела и положения отрисовываемого объекта на сцене

// TODO: Добавить возможность загружать карты из сети а так же их сохранять

// TODO: добавить поиск текстур в указанных каталогах