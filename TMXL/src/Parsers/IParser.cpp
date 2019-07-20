#include "TMXL/Parsers/IParser.h"

namespace TMXL {

    void IParser::setFileName(const std::string& fileName) noexcept {
        m_fileName = fileName;
    }

    const std::string &IParser::getFileName() const noexcept {
        return m_fileName;
    }

    IParser::~IParser() = default;

}