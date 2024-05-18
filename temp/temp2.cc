#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/json.hpp>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

std::string base64_encode(const unsigned char* input, int length) {
    BIO* bmem = BIO_new(BIO_s_mem());
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_push(b64, bmem);
    BIO_write(bmem, input, length);
    BIO_flush(bmem);
    BUF_MEM* bptr = nullptr;
    BIO_get_mem_ptr(bmem, &bptr);

    std::string encoded(bptr->data, bptr->length);
    BIO_free_all(bmem);
    return encoded;
}

std::string hmac_sha256(const std::string& key, const std::string& data) {
    unsigned char* digest;
    digest = HMAC(EVP_sha256(), key.c_str(), key.length(), (unsigned char*)data.c_str(), data.length(), nullptr, nullptr);
    return base64_encode(digest, SHA256_DIGEST_LENGTH);
}

std::string create_jwt(const std::string& header, const std::string& payload, const std::string& secret) {
    std::string encoded_header = base64_encode(reinterpret_cast<const unsigned char*>(header.c_str()), header.length());
    std::string encoded_payload = base64_encode(reinterpret_cast<const unsigned char*>(payload.c_str()), payload.length());

    std::string signature = hmac_sha256(secret, encoded_header + "." + encoded_payload);

    return encoded_header + "." + encoded_payload + "." + signature;
}

bool verify_jwt(const std::string& token, const std::string& secret) {
    size_t first_dot = token.find('.');
    size_t second_dot = token.find('.', first_dot + 1);

    if (first_dot == std::string::npos || second_dot == std::string::npos) {
        return false;
    }

    std::string encoded_header = token.substr(0, first_dot);
    std::string encoded_payload = token.substr(first_dot + 1, second_dot - first_dot - 1);
    std::string received_signature = token.substr(second_dot + 1);

    std::string expected_signature = hmac_sha256(secret, encoded_header + "." + encoded_payload);

    return received_signature == expected_signature;
}

int main() {
    std::string header = R"({"alg":"HS256","typ":"JWT"})";
    std::string payload = R"({"sub":"1234567890","name":"John Doe","iat":1516239022})";
    std::string secret = "your-256-bit-secret";

    std::string token = create_jwt(header, payload, secret);
    std::cout << "JWT Token: " << token << std::endl;

    bool is_valid = verify_jwt(token, secret);
    std::cout << "Token is valid: " << std::boolalpha << is_valid << std::endl;

    return 0;
}
