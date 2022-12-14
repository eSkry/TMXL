#pragma once

#include "TMXL/System/StringTools.h"
#include "TMXL/System/Color.h"

#include <algorithm>
#include <string.h>

namespace TMXL {

    enum class TMXLTypes {
        Undefined_e = -1,
        Int_e,
        Long_e,
        Bool_e,
        Double_e,
        String_e,
        Color_e
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
    void snn(T *object, V val) noexcept {
        if (object)
            *object = val;
    }

    /**
     * @details Возвращает новую строку с измененными симвалами верхнего регистра на нижний регистр.
     * @param str
     * @return
     */
    static std::string strToLowerCase(const std::string& str) noexcept {
        if (str.empty()){
            return {};
        }

        const std::size_t distance = static_cast<int>('a') - static_cast<int>('A');
        std::string tempStr(str);

        for (std::size_t i = 0; i < str.length(); i++){
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
    static char charToLowerCase(char ch) noexcept {
        const std::size_t distance = static_cast<int>('a') - static_cast<int>('A');
        if (ch >= 'A' && ch <= 'Z'){
            return static_cast<char>(static_cast<int>(ch) + distance);
        }
        return ch;
    }

    /**
     * @brief static TMXLType stringToType(const sf::String& str) [noexcept]
     * @details Определяет тип данных написанный в строке
     * @param str
     * @return
     */
    static TMXLTypes stringToType(const std::string& str) noexcept {
        if (compare(str, "string", StringComparison::IgnoreCase)){
            return TMXLTypes::String_e;
        } else if (compare(str, "int", StringComparison::IgnoreCase)){
            return TMXLTypes::Int_e;
        } else if (compare(str, "float", StringComparison::IgnoreCase)) {
            return TMXLTypes::Double_e;
        } else if (compare(str, "bool", StringComparison::IgnoreCase)) {
            return TMXLTypes ::Bool_e;
        } else if (compare(str, "color", StringComparison::IgnoreCase)) {
            return TMXLTypes::Color_e;
        } else if (compare(str, "file", StringComparison::IgnoreCase)) {
            return TMXLTypes::String_e;
        }

        return TMXLTypes::Undefined_e;
    }

    static TMXLTypes stringToType(const char *str) noexcept {
        if (compare(str, "string", StringComparison::IgnoreCase)) {
            return TMXLTypes::String_e;
        } else if (compare(str, "int", StringComparison::IgnoreCase))  {
            return TMXLTypes::Int_e;
        } else if (compare(str, "float", StringComparison::IgnoreCase)) {
            return TMXLTypes::Double_e;
        } else if (compare(str, "bool", StringComparison::IgnoreCase)) {
            return TMXLTypes ::Bool_e;
        } else if (compare(str, "color", StringComparison::IgnoreCase)) {
            return TMXLTypes::Color_e;
        } else if (compare(str, "flie", StringComparison::IgnoreCase)) {
            return TMXLTypes::String_e;
        }

        return TMXLTypes::Undefined_e;
    }


}
