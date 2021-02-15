#include "TMXL/System/Logger/StlLoggerAdapter.h"

namespace TMXL {

    void StlLoggerAdapter::Info(const std::string &str) {
        std::cout << str << '\n';
    }

    void StlLoggerAdapter::Warn(const std::string &str) {
        std::cout << str << '\n';
    }

    void StlLoggerAdapter::Error(const std::string &str) {
        std::cout << str << '\n';
    }

}