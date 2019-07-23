#ifndef TMXL_BASE64ENCODER_H
#define TMXL_BASE64ENCODER_H

#include "IEncoder.h"

#include <sstream>
#include <ostream>
#include <string>

namespace TMXL {

    static const std::string Base64Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    class Base64Encoder : IEncoder {
    public:

        std::string encode(const std::string& data) override;
        std::string decode(const std::string& data) override;

        void encode(const std::string& data, std::ostream& os) override;
        void decode(const std::string& data, std::ostream& os) override;

        void encode(const std::string& data, std::string& out) override;
        void decode(const std::string& data, std::string& out) override;

        std::size_t decodeLength(const std::string& data);
        std::size_t encodeLength(const std::string& data);

    private:
        void b3Tob4(unsigned char* b3, unsigned char* b4);
        void b4Tob3(unsigned char* b4, unsigned char* b3);
        unsigned char b64Lookup(unsigned char c);
    };

}

#endif //TMXL_BASE64ENCODER_H
