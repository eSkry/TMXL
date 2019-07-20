#include "TMXL/Parsers/IParser.h"

namespace TMXL {

    void IParser::setFileName(const std::string& fileName) noexcept {
        mfileName = fileName;
    }

    const std::string &IParser::getFileName() const noexcept {
        return mfileName;
    }

    IParser::~IParser() = default;

}