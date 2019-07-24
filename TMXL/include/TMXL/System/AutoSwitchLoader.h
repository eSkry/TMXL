#ifndef TMXL_AUTOSWITCHLOADER
#define TMXL_AUTOSWITCHLOADER

#include "TMXL/Parsers/IParser.h"
#include "TMXL/Map/NodeObject.h"
#include "TMXL/System/Logger.h"

#include <string>
#include <map>

namespace TMXL {

    class AutoSwitchLoader {
    public:

        void registerParser(const std::string& type, IParser* parser);

        std::shared_ptr<NodeObject> parser(const std::string& fileName);

    private:
        std::map<std::string, IParser*> mParsers;
    };

}

#endif // TMXL_AUTOSWITCHLOADER