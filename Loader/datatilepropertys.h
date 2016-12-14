#ifndef DATATILEPROPERTYS_H
#define DATATILEPROPERTYS_H

#include <SFML/Graphics/Color.hpp>

#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <math.h>
using std::string;

class DataTilePropertys{
public:
    DataTilePropertys();
    ~DataTilePropertys();

    ///////////// OPERATORS = /////////////
    void operator=(int value);
    void operator=(float value);
    void operator=(string value);
    //void operator=(bool value);
    void operator=(sf::Color value);

    ///////////// get data /////////////
    string      as_string();
    float       as_float();
    sf::Color   as_color();
    bool        as_bool();
    int         as_int();
private:
    void*           vData;

    enum MyType{
        NONE_E,
        STRING_E, // _E - enumeration
        FLOAT_E,
        COLOR_E,
        BOOL_E,
        INT_E
    };

    MyType          tType;

    void deleteCurrentData();

    template <class T>
    void newData(T value);

    sf::Uint8 charHexToUInt(char c);
};

#endif // DATATILEPROPERTYS_H
