#include "TMXL/System/IDGenerator.h"

namespace TMXL {

    IDGenerator::IDGenerator() {
        mId = std::numeric_limits<std::size_t>::min();
    }

    void IDGenerator::reset() noexcept {
        mId = std::numeric_limits<std::size_t>::min();
    }

    std::size_t IDGenerator::getId() noexcept {
        if (mId == std::numeric_limits<std::size_t>::max()) {
            // @todo: send exception or massage 'generator out of numeric range' or set to minimal value
            mId = std::numeric_limits<std::size_t>::min();
        }
        return ++mId;
    }

}