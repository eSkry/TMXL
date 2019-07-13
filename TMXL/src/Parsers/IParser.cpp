#include "TMXL/Parsers/IParser.h"

namespace TMXL {

    void IParser::setFileName(const sf::String& fileName) {
        m_fileName = fileName;
    }

    const sf::String &IParser::getFileName() const {
        return m_fileName;
    }

    IParser::~IParser() = default;

}