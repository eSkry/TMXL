//
// Created by depish on 20.07.19.
//

#ifndef TMXL_LOGGER_H
#define TMXL_LOGGER_H

#include "TMXL/Config.h"

#include <iostream>
#include <string>

namespace TMXL::Log {


    inline void info(const std::string& message) {
        std::cout << "INFO: " << message << std::endl;
    }

    inline void warn(const std::string& message) {
        std::cout << "WARN: " << message << std::endl;
    }

    inline void error(const std::string& message) {
        std::cout << "ERROR: " << message << std::endl;
    }

}

#endif //TMXL_LOGGER_H
