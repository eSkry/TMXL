//
// Created by depish on 07.06.19.
//

#ifndef TMXL_STRINGTOOLS_H
#define TMXL_STRINGTOOLS_H

#include <cstring>
#include <math.h>
#include <string>

namespace TMXL {

    enum class StringComparison {
        Normal,
        IgnoreCase
    };

    /**
     * @tparam T1
     * @tparam T2
     * @param str1
     * @param str2
     * @param len
     * @return
     */
    template <typename T1, typename T2>
    static bool ignoreCaseCompire(const T1& str1, const T2& str2, std::size_t len) {
        int dist = static_cast<int>('a') - static_cast<int>('A');
        int rdist = 0;

        for (std::size_t i = 0; i < len; i++){
            rdist = std::abs(static_cast<int>(str1[i] - str2[i]));

            if (str1[i] != str2[i] && rdist != dist){
                return false;
            }
        }

        return true;
    }

    /**
     * @brief static bool compare(const sf::String& str1, const sf::String& str2, StringComparison comparsion = StringComparison::Normal) [_TMXL_NOEXCEPT]
     * @details Сравнивает две строки, возвращает true если строки равны, false если не равны, если указать StringComparison::IgnoreCase то строки val и VAL будут равны.
     * @param str1
     * @param str2
     * @return
     */
    static bool compare(const std::string& str1, const std::string& str2, StringComparison comparsion = StringComparison::Normal) noexcept {
        if (str1.length() != str2.length()){
            return false;
        }

        if (comparsion == StringComparison::Normal){
            return str1 == str2;
        }

        std::size_t len = str1.length();
        if (comparsion == StringComparison::IgnoreCase) {
            return ignoreCaseCompire(str1, str2, len);
        }

        return true;
    }

    /**
     * @param str1
     * @param str2
     * @param len
     * @param comparison
     * @return
     */
    static bool compare(const std::string& str1, const char* str2, std::size_t len, StringComparison comparison = StringComparison::IgnoreCase) noexcept {
        if (str1.length() != len) {
            return false;
        }

        if (comparison == StringComparison::Normal) {
            for (std::size_t i = 0; i < len; i++) {
                if (str1[i] != str2[i]){
                    return false;
                }
            }

            return true;
        }

        if (comparison == StringComparison::IgnoreCase) {
            return ignoreCaseCompire(str1, str2, len);
        }

        return false;
    }

    static bool compareCString(const char* str1, const char* str2, StringComparison comparison = StringComparison::IgnoreCase) {
        std::size_t len1 = std::strlen(str1);
        std::size_t len2 = std::strlen(str2);

        if (len1 != len2) {
            return false;
        }

        if (comparison == StringComparison::Normal) {
            for (std::size_t i = 0; i < len1; i++) {
                if (str1[i] != str2[i]){
                    return false;
                }
            }

            return true;
        }

        if (comparison == StringComparison::IgnoreCase){
            return ignoreCaseCompire(str1, str2, len1);
        }

        return false;
    }

}

#endif //TMXL_STRINGTOOLS_H
