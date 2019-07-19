#ifndef TMXL_TYPECONVERT_H
#define TMXL_TYPECONVERT_H

#include "SFMLSugar.h"
#include "Config.h"
#include "Tools.h"

#include <typeinfo>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>

#include <SFML/Graphics/Color.hpp>

namespace TMXL {

    /**
     * @brief Преобразует bool в int
     * @details Преобразует bool в int
     *          true  -> 1
     *          false -> 0
     * @param val
     * @return
     */
    inline int boolToInt(bool val) noexcept {
        return val ? 1 : 0;
    }

    /**
     * @brief Преобразует int в bool
     * @details Преобразует int в bool
     *          val > 0  -> true
     *          val <= 0 -> false
     * @param val
     * @return
     */
    inline bool intToBool(int val) noexcept {
        return val > 0;
    }

    /**
     * @brief Преобразует long в bool
     * @details Преобразует long в bool
     *          val > 0  -> true
     *          val <= 0 -> false
     * @param val
     * @return
     */
    inline bool longToBool(long val) noexcept {
        return val > 0;
    }

    /**
     * @brief Преобразует bool в long
     * @details Преобразует bool в long
     *          true  -> 1
     *          false -> 0
     * @param val
     * @return
     */
    inline long boolToLong(bool val) noexcept {
        return val ? 1 : 0;
    }

    /**
     * @brief Преобразует bool в double
     * @details Преобразует bool в long
     *          true  -> 1.0
     *          false -> 0.0
     * @param val
     * @return
     */
    inline double boolToDouble(bool val) noexcept {
        return val ? 1.0 : 0.0;
    }

    /**
     * @brief Преобразует double в bool
     * @details Преобразует double в bool
     *          val > 0  -> true
     *          val <= 0 -> false
     * @param val
     * @return
     */
    inline bool doubleToBool(double val) noexcept {
        return val >= 1;
    }

    /**
     * @brief Преобразует bool в TLString_t
     * @details Преобразует bool в TLString_t
     * @param val - Значение которое необходимо преобразовать
     * @param fullFormat - Формат строки, если true то вернется полная строка если false то только первый символ строки.
     * @param a_true - Строка возвращаемая при val == true, по умолчанию "true"
     * @param a_false - Строка возвращаемая при val == false, по умолчанию "false"
     * @return
     */
    static sf::String boolToString(bool val, bool fullFormat = true
                    , const char* a_true = "true"
                    , const char* a_false = "false") noexcept {
        if (val && fullFormat) return a_true;
        if (val && !fullFormat) return a_true[0];
        if (!val && fullFormat) return a_false;
        return a_false[0];
    }

    /**
     * @brief Преобразует строку в bool
     * @details Принимает на вход строку, преобразует содержащиеся данные в тип bool.
     *          Регистр символов в строке значения не имеет.
     *
     *          0 -> false
     *          f = F -> false
     *          False = false = FaLSe = ... -> false
     *          ...
     *          Для true все так же
     *
     *          Если в строке не содержится прваильных данных для преобразования то вернется defaultValue.
     *
     * @param str
     * @param defaultValue - Значение возвращаемое если строку невозможно преобразовать в bool.
     * @return
     */
    static bool strToBool(const sf::String& str, bool defaultValue = false) noexcept {
        if (str.isEmpty()){
            return defaultValue;
        }

        if (str.getSize() == 1) {
            if (str == '1' || str == 't' || str == 'T') {
                return true;
            } else if (str == '0' || str == 'f' || str == 'F') {
                return false;
            }
            return defaultValue;
        }

        const sf::String lowerStr = strToLowerCase(str);
        if (lowerStr == "true"){
            return true;
        } else if (lowerStr == "false"){
            return false;
        }

        return defaultValue;
    }

    /**
     * @brief charToUnit8 преобразует два символа типа char к типу sf::Uint8 (unsigned char) тем самым обозначая цвет.
     * @param ch1
     * @param ch2
     * @return
     */
    static sf::Uint8 charToUint8(char ch1, char ch2) noexcept {
        sf::Uint8 temp = 0;

        ch1 = charToLowerCase(ch1);
        ch2 = charToLowerCase(ch2);

        if (ch1 >= '0' && ch1 <= '9') {
            temp = static_cast<sf::Uint8>( ch1 - '0' );
        } else if (ch1 >= 'a' && ch1 <= 'f'){
            temp = static_cast<sf::Uint8>( 10 + (ch1 - 'a') );
        }

        temp <<= 4u; // Сдвиг влево на 4 бита
        if (ch2 >= '0' && ch2 <= '9') {
            temp += static_cast<sf::Uint8>( ch2 - '0' );
        } else if (ch2 >= 'a' && ch2 <= 'f'){
            temp += static_cast<sf::Uint8>( 10 + (ch2 - 'a') );
        }

        return temp;
    }

    /**
     * @brief Преобразует строку в sf::Color
     * @details Конструирует объект типа sf::Color из строки формата ARGB и RGB
     *          Допустимые входные строки:
     *          #AARRGGBB
     *          #RRGGBB
     *          AARRGGBB
     *          RRGGBB
     * @param str
     * @return
     */
    static sf::Color strToColorARGB(const sf::String &str) noexcept {
        if (str.getSize() < 6) {
            return {};
        }

        int sp = 0; // sp - start pose
        if (str[0] == '#') {
            sp += 1;
        }

        sf::Color temp;

        // TODO: сделать все в соответствии с типами
        if (str.getSize() > 6 + sp){
            temp.a = charToUint8(str[0 + sp], str[1 + sp]);
            sp += 2;
        }

        temp.r = charToUint8(str[0 + sp], str[1 + sp]);
        temp.g = charToUint8(str[2 + sp], str[3 + sp]);
        temp.b = charToUint8(str[4 + sp], str[5 + sp]);

        return temp;
    }

    /**
     * @brief Преобразует строку в int
     * @param str
     * @param defaultValue
     * @return
     */
    static int strToInt(const sf::String& str, int defaultValue = -1) noexcept {
        return std::stoi(sfStringToChar(str));
    }

    /**
     * @brief Преобразует строку в long
     * @param str
     * @param defaultValue
     * @return
     */
    static long strToLong(const sf::String& str, long defaultValue = -1) noexcept {
        return std::stol(sfStringToChar(str));
    }

    /**
     * @brief Преобразует TLString_t в double
     * @param str
     * @param defaultValue
     * @return
     */
    static double strToDouble(const sf::String& str, double defaultValue = -1.0) noexcept {
        return std::stod(sfStringToChar(str));
    }

    /**
     * @brief Преобразует sf::Color в int
     * @details Функция преобразует sf::Color в иденое число представляющее цвет:
     *          0xAARRGGBB
     * @param c
     * @return
     */
    static int colorToInt(const sf::Color& c) noexcept {
        return  ( ((c.a & 0xff) << 24)
                + ((c.r & 0xff) << 16)
                + ((c.g & 0xff) << 8)
                +  (c.b & 0xff) );
    }

    /**
     * @brief Преобразование int в sf::Color
     * @param color
     * @return
     */
    static sf::Color intToColor(int color) noexcept {
        sf::Color temp;
        temp.a = static_cast<sf::Uint8>((color >> 24) & 0xff);
        temp.r = static_cast<sf::Uint8>((color >> 16) & 0xff);
        temp.g = static_cast<sf::Uint8>((color >> 8) & 0xff);
        temp.b = static_cast<sf::Uint8>(color & 0xff);
        return temp;
    }

    /**
     * @brief Преобразует тип sf::Color в TLString_t ARGB
     * @param val
     * @return
     */
    static sf::String colorToStringARGB(const sf::Color &val) noexcept {
        char temp[10] = {'0'}; // 10-й эллемент под нуль символ sprintf
        sprintf(temp, "#%2x%2x%2x%2x", val.a, val.r, val.g, val.b);

        for (char & i : temp){
            if (i == ' ')
                i = '0';
        }

        return temp;
    }

    /**
     * @brief Преобразует int в TLString_t
     * @param val
     * @return
     */
    static sf::String intToString(int val) noexcept {
        return std::to_string(val);
    }

    /**
     * @brief Преобразует long в TLString_t
     * @param val
     * @return
     */
    static sf::String longToString(long val) noexcept {
        return std::to_string(val);
    }

}

#endif //TMXL_TYPECONVERT_H
