#ifndef TMXL_TMXLTYPE_H
#define TMXL_TMXLTYPE_H

#include "TypeConvert.h"
#include "Config.h"
#include "Tools.h"

#include <memory>

#include <SFML/Graphics/Color.hpp>

/*
 * TODO: Реализовать собственный аллокатор для хранения даных в классе TMXLType.
 * Все что создается через new в классе TMXLType необходимо хранить скомпанованно
 * а не по разным участкам памяти.
 */

namespace TMXL {

    /**
     * @brief class TMXLType
     */
    class TMXLType {
    public:

        TMXLType();
        TMXLType(const TMXLType& object);
        ~TMXLType();

        /**
         * @details Возвращает тип хранимых данных.
         * @return
         */
        TMXLTypes getType() const _TMXL_NOEXCEPT;

        void operator=(int val) _TMXL_NOEXCEPT;
        void operator=(bool val) _TMXL_NOEXCEPT;
        void operator=(long val) _TMXL_NOEXCEPT;
        void operator=(double val) _TMXL_NOEXCEPT;
        void operator=(const sf::Color& val) _TMXL_NOEXCEPT;
        void operator=(const sf::String& val) _TMXL_NOEXCEPT;

        int as_int(int defaultValue = -1) const _TMXL_NOEXCEPT;
        long as_long(long defaultValue = -1) const _TMXL_NOEXCEPT;
        bool as_bool(bool defaultValue = false) const _TMXL_NOEXCEPT;
        double as_double(double defaultValue = -1) const _TMXL_NOEXCEPT;
        sf::Color as_color(const sf::Color& defaultValue = sf::Color::Black) const _TMXL_NOEXCEPT;
        sf::String as_string(const sf::String& defaultValue = "") const _TMXL_NOEXCEPT;

    private:
        void deleteData() _TMXL_NOEXCEPT;

        TMXLTypes   m_type;
        void*       m_data;
    };

}



#endif //TMXL_TMXLTYPE_H
