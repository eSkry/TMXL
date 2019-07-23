#include "TMXL/Encodings/Base64Encoder.h"

namespace TMXL {

    std::string Base64Encoder::encode(const std::string &data) {
        std::ostringstream stream;
        encode(data, stream);
        return stream.str();
    }

    std::string Base64Encoder::decode(const std::string &data) {
        std::ostringstream stream;
        decode(data, stream);
        return stream.str();
    }

    void Base64Encoder::encode(const std::string &data, std::ostream &os) {
        std::stringstream result;
        std::size_t i = 0, j = 0, e = 0;
        std::size_t inputLength = data.length();
        unsigned char b3[3];
        unsigned char b4[4];

        while (inputLength--){
            b3[i++] = data[e++];
            if (i == 3) {
                b3Tob4(b3, b4);
                for (i = 0; i < 4; i++){
                    os << Base64Alphabet[ b4[i] ];
                }
                i = 0;
            }
        }

        if (i) {
            for (j = i; j < 3; j++){
                b3[j] = '\0';
            }
            b3Tob4(b3, b4);
            for (j = 0; j < i + 1; j++){
                os << Base64Alphabet[ b4[j] ];
            }
            while (i++ < 3){
                os << '=';
            }
        }
    }

    void Base64Encoder::decode(const std::string &data, std::ostream &os) {
        std::stringstream result;
        std::size_t i = 0, j = 0, e = 0;
        unsigned char b3[3];
        unsigned char b4[4];
        std::size_t inputLength = data.length();

        while (inputLength--){
            if (data[e] == '='){
                break;
            }
            b4[i++] = data[e++];
            if (i == 4) {
                for (i = 0; i < 4; i++){
                    b4[i] = b64Lookup( b4[i] );
                }
                b4Tob3(b4, b3);
                for (i = 0; i < 3; i++){
                    os << b3[i];
                }
                i = 0;
            }
        }

        if (i) {
            for (j = i; j < 4; j++){
                b4[j] = '\0';
            }
            for (j = 0; j < 4; j++){
                b4[j] = b64Lookup( b4[j] );
            }
            b4Tob3(b4, b3);
            for (j = 0; j < i - 1; j++){
                os << b3[j];
            }
        }
    }

    void Base64Encoder::encode(const std::string &data, std::string &out) {
        std::stringstream stream;
        encode(data, stream);
        out.resize( encodeLength(data) );
        out = stream.str();
    }

    void Base64Encoder::decode(const std::string &data, std::string &out) {
        std::stringstream stream;
        decode(data, stream);
        out.resize( decodeLength(data) );
        out = stream.str();
    }

    void Base64Encoder::b3Tob4(unsigned char *b3, unsigned char *b4) {
        b4[0] = (b3[0] & 0xfc) >> 2;
        b4[1] = ((b3[0] & 0x03) << 4) + ((b3[1] & 0xf0) >> 4);
        b4[2] = ((b3[1] & 0x0f) << 2) + ((b3[2] & 0xc0) >> 6);
        b4[3] = (b3[2] & 0x3f);
    }

    void Base64Encoder::b4Tob3(unsigned char *b4, unsigned char *b3) {
        b3[0] = (b4[0] << 2) + ((b4[1] & 0x30) >> 4);
        b3[1] = ((b4[1] & 0xf) << 4) + ((b4[2] & 0x3c) >> 2);
        b3[2] = ((b4[2] & 0x3) << 6) + b4[3];
    }

    unsigned char Base64Encoder::b64Lookup(unsigned char c) {
        if(c >='A' && c <='Z') return c - 'A';
        if(c >='a' && c <='z') return c - 71;
        if(c >='0' && c <='9') return c + 4;
        if(c == '+') return 62;
        if(c == '/') return 63;
        return 255;
    }

    std::size_t Base64Encoder::decodeLength(const std::string &data) {
        int numEq = 0, n = data.size();
        for (std::string::const_reverse_iterator it = data.rbegin(); *it == '='; ++it) {
            ++numEq;
        }
        return ((6 * n) / 8) - numEq;
    }

    std::size_t Base64Encoder::encodeLength(const std::string &data) {
        return (data.size() + 2 - ((data.size() + 2) % 3)) / 3 * 4;
    }

}