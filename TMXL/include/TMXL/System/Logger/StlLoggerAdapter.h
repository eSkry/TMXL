#ifndef TMXL_STLLOGGERADAPTER_H
#define TMXL_STLLOGGERADAPTER_H

#include <iostream>
#include <string>

#include "AbstractLoggerAdapter.h"

namespace TMXL {

    /**
     * @brief StlLoggerAdapter class - Адептер логера для вывода на консоль
     */
    class StlLoggerAdapter : AbstractLoggerAdapter {
    public:
        virtual void Info(const std::string& str) override;
        virtual void Warn(const std::string& str) override;
        virtual void Error(const std::string& str) override;
    };

}

#endif //TMXL_STLLOGGERADAPTER_H
