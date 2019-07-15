#ifndef TMXL_TOOLS_H
#define TMXL_TOOLS_H

#include "Config.h"
#include "TMXL/System/StringTools.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>

#include <algorithm>
#include <string.h>

namespace TMXL {

    enum class TMXLTypes {
        Undefined_e = -1,
        Int_e,
        TLSize_e,
        Long_e,
        Bool_e,
        Double_e,
        Float_e,
        String_e,
        Color_e,
        File_e
    };

    /**
     * @details Устанавливает объекту передаваемое значение если объект не является указателем на nullptr.
     *          snn - set if not nullptr
     * @tparam T
     * @tparam V
     * @param object
     * @param val
     */
    template <typename T, typename V>
    void snn(T *object, V val) _TMXL_NOEXCEPT {
        if (object)
            *object = val;
    }

    /**
     * @details Возвращает новую строку с измененными симвалами верхнего регистра на нижний регистр.
     * @param str
     * @return
     */
    static sf::String strToLowerCase(const sf::String& str) _TMXL_NOEXCEPT {
        if (str.isEmpty()){
            return {};
        }

        const TLSize_t distance = static_cast<int>('a') - static_cast<int>('A');
        sf::String tempStr(str);

        for (TLSize_t i = 0; i < str.getSize(); i++){
            if (str[i] >= 'A' && str[i] <= 'Z') {
                tempStr[i] = str[i] + distance;
            }
        }

        return tempStr;
    }

    /**
     * @details Если символ записан в верхнем регистре то вернется тот же символ но в нижнем регистре.
     * @param ch
     * @return
     */
    static char charToLowerCase(char ch) _TMXL_NOEXCEPT {
        const TLSize_t distance = static_cast<int>('a') - static_cast<int>('A');
        if (ch >= 'A' && ch <= 'Z'){
            return static_cast<char>(static_cast<int>(ch) + distance);
        }
        return ch;
    }

    /**
     * @brief static TMXLType stringToType(const sf::String& str) [_TMXL_NOEXCEPT]
     * @details Определяет тип данных написанный в строке
     * @param str
     * @return
     */
    static TMXLTypes stringToType(const sf::String& str) _TMXL_NOEXCEPT {
        if (str == "string"){
            return TMXLTypes::String_e;
        } else if (str == "int"){
            return TMXLTypes::Int_e;
        } else if (str == "float") {
            return TMXLTypes::Float_e;
        } else if (str == "bool") {
            return TMXLTypes ::Bool_e;
        } else if (str == "color") {
            return TMXLTypes::Color_e;
        } else if (str == "file") {
            return TMXLTypes::File_e;
        }

        return TMXLTypes::Undefined_e;
    }

    static TMXLTypes stringToType(const char *str) _TMXL_NOEXCEPT {
        if (compare(str, "string", StringComparison::IgnoreCase)) {
            return TMXLTypes::String_e;
        } else if (compare(str, "int", StringComparison::IgnoreCase))  {
            return TMXLTypes::Int_e;
        } else if (compare(str, "float", StringComparison::IgnoreCase)) {
            return TMXLTypes::Float_e;
        } else if (compare(str, "bool", StringComparison::IgnoreCase)) {
            return TMXLTypes ::Bool_e;
        } else if (compare(str, "color", StringComparison::IgnoreCase)) {
            return TMXLTypes::Color_e;
        } else if (compare(str, "flie", StringComparison::IgnoreCase)) {
            return TMXLTypes::File_e;
        }

        return TMXLTypes::Undefined_e;
    }


}

#endif //TMXL_TOOLS_H
