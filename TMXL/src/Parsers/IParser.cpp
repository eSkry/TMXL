#include "TMXL/Parsers/IParser.h"

namespace TMXL {

    void IParser::setFileName(const sf::String& fileName) noexcept {
        m_fileName = fileName;
    }

    const sf::String &IParser::getFileName() const noexcept {
        return m_fileName;
    }

    IParser::~IParser() = default;

}