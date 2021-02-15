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
     * @param str1
     * @param str2
     * @return
     */
    static bool ignoreCaseCompire(std::string_view str1, std::string_view str2) {
        if (str1.size() != str2.size()) return false;

        int dist = static_cast<int>('a') - static_cast<int>('A');
        int rdist = 0;

        for (auto fIt = str1.begin(), sIt = str2.begin(); fIt != str1.end(); fIt++, sIt++){
            rdist = std::abs(static_cast<int>(*fIt - *sIt));

            if (*fIt != *sIt && rdist != dist){
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
    static bool compare(const std::string_view str1, const std::string_view str2, StringComparison comparsion = StringComparison::Normal) noexcept {
        if (str1.length() != str2.length()){
            return false;
        }

        if (comparsion == StringComparison::Normal){
            return str1 == str2;
        }

        if (comparsion == StringComparison::IgnoreCase) {
            return ignoreCaseCompire(str1, str2);
        }

        return true;
    }

	static void replaceAll(std::string& str, const std::string& from, const std::string& to) {
		if (from.empty())
			return;
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
	}

    static bool stringEndsWith(std::string_view str, std::string_view end) {
        if (end.size() > str.size()) return false;

        std::size_t sPos = str.size() - end.size();
        for (auto it = str.begin() + sPos, eIt = end.begin(); eIt != end.end(); it++, eIt++) {
            if (*it != *eIt) return false;
        }

        return true;
    }


}

#endif //TMXL_STRINGTOOLS_H
