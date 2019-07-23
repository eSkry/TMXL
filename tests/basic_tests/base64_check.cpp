#include "gtest/gtest.h"

#include <TMXL/Encodings/Base64Encoder.h>
#include <sstream>

TEST(base64_check, test_eq) {
    using namespace TMXL;

    Base64Encoder encoder;
    // By string
    // Hello base64! == SGVsbG8gYmFzZTY0IQ==
    ASSERT_STREQ(encoder.encode("Hello base64!").c_str(), "SGVsbG8gYmFzZTY0IQ==");
    ASSERT_STREQ(encoder.decode("SGVsbG8gYmFzZTY0IQ==").c_str(), "Hello base64!");
}

TEST(base64_stream_check, test_eq) {
    using namespace TMXL;

    Base64Encoder encoder;
    // By stream
    std::ostringstream stream;
    // TestString123 == VGVzdFN0cmluZzEyMw==
    encoder.encode("TestString123", stream);
    ASSERT_STREQ(stream.str().c_str(), "VGVzdFN0cmluZzEyMw==");
    stream.str("");

    encoder.decode("VGVzdFN0cmluZzEyMw==", stream);
    ASSERT_STREQ("TestString123", stream.str().c_str());
}

TEST(base64_strref_check, test_eq) {
    using namespace TMXL;

    Base64Encoder encoder;
    // By string ref
    std::string str;
    // Meow^_^ == TWVvd15fXg==
    encoder.encode("Meow^_^", str);
    ASSERT_STREQ(str.c_str(), "TWVvd15fXg==");
    encoder.decode("TWVvd15fXg==", str);
    ASSERT_STREQ(str.c_str(), "Meow^_^");
}