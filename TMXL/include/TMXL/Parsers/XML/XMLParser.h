#pragma once

#include "../IParser.h"

namespace TMXL {

    class XMLParser : public IParser {
    public:
        virtual ~XMLParser() = default;
        TMEMapPtr parse(const std::string &xmlData) override;
    };

}

