#ifndef TMXL_IENCODER_H
#define TMXL_IENCODER_H

#include <ostream>
#include <string>

namespace TMXL {

    /**
     * @details Base class for encoders
     */
    class IEncoder {
    public:

        virtual std::string encode(const std::string& data) = 0;
        virtual std::string decode(const std::string& data) = 0;

        virtual void encode(const std::string& data, std::ostream& os) = 0;
        virtual void decode(const std::string& data, std::ostream& os) = 0;

        virtual void encode(const std::string& data, std::string& out) = 0;
        virtual void decode(const std::string& data, std::string& out) = 0;

    };

}

#endif //TMXL_IENCODER_H
