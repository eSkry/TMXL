#ifndef TMXL_TMXLTYPE_H
#define TMXL_TMXLTYPE_H

#include "TMXL/TypeConvert.h"
#include "TMXL/Config.h"
#include "TMXL/Tools.h"

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
        TMXLTypes getType() const noexcept;

        void operator=(int val) noexcept;
        void operator=(bool val) noexcept;
        void operator=(long val) noexcept;
        void operator=(double val) noexcept;
        void operator=(const sf::Color& val) noexcept;
        void operator=(const sf::String& val) noexcept;

        int as_int(int defaultValue = -1) const noexcept;
        long as_long(long defaultValue = -1) const noexcept;
        bool as_bool(bool defaultValue = false) const noexcept;
        double as_double(double defaultValue = -1) const noexcept;
        sf::Color as_color(const sf::Color& defaultValue = sf::Color::Black) const noexcept;
        sf::String as_string(const sf::String& defaultValue = "") const noexcept;

    private:
        void deleteData() noexcept;

        TMXLTypes   m_type;
        void*       m_data;
    };

}



#endif //TMXL_TMXLTYPE_H
