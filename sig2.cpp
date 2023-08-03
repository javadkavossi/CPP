#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#define R(str) #str
// کلید خصوصی ثابت برای امضای پیام‌ها
const char* privateKeyStr = R"("
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAp1FWaJ2kwZKGg48itFCxCfVJCMaTEP78wZ2ruEs1ux/ls/9B
6XK4qLUK0UkFbS/s3wZtB8AEWU1O9hGhsDFpLBCXtAAQTjYZzGK59xIvWSOgXvZ8
W3NM0LaCMV7U5z6QvVvqXs88uTz+0grL7Zb1VTZPwQq0A+R74jq4WVRuE6tTSvfu
3u7Nz88NcXv/h42o6iWJ9pNQw2ONBF18sY2LqJbSEdC1l6tNU7TmTQLn1FJxONzR
kE8zDwJ8kn6iwlvSpk1HPIUWWKHf4vnNoFHYG27jyZLHxigNTA0fRRZ2FSiH18I9
IOdiR6Ys4wjWlK7Vi0fB7NKRq8x6v+M0HbfKjQIDAQABAoIBAGLQUz/AR0OUamr1
atJkXxI32ABsyiJF0Weuf3s41b6t/viaXZPGX+0NOOCjT0mEs3Sla4kzxMSBCIfO
e8pC5YMKY21XtMz8FP3J3fNcFe5iWMV/2cmZ+ggmJy8gfdhIKu6l1ZDjXefLXU5L
lmPwtMyY5sWY1zAM4STFvnnAFiInUH/8lTk8S1Q5OvPiZBNAdckJ09JF6qDlw0it
sAZs2tMiBWbqD3wvGpahcz5tCJgWADvGRbWDe8iR3FlXWUzXf+n+MSdVTPi2twad
7nO3gR2mefX8jnroU+nqTAbZgZJ/w3W1msmX/sgOWAdh6rddCgLy7Td3GRw5T1FE
Bs1IcQECgYEA4An4lf5MbKVhCKkx7Lq2jCw0Rj9OZuTFu3zW7K17KSwVeOZIAC4L
Xpx6clzueVi3ntrmR6grpi7ZwAfEtxPZIHKo6U1GFO36Db/JDm80yAcBfoA3T0Zl
GX0pREBrmldAS3ms4rryotRjj8BfrBDoH3pr8W3ylCjM6WVJ6Zj84GkCgYEAxF8X
gvc20xE+2tL56jgJgdMHBzTTlwmikdMbtdrOayzcrviWST0yoU9GrL6QJQQhYDX5
kl6UkU9xI6x9GG2fGqKsIyHk7DSYvTZueiABkIOWZWdXQsByBvYVFrNSNtIAe6CB
6vkeMn6fQfsCUXIh/YiP4qLtl3mFsMijjpbNcb8CgYBVmfc1SVapNiqXprX9FtXb
mskSTcdmVeNpjw33/RCd2B8dGvnI8IgR/KC+JrhPT8J7qczHbu1A+nYaIRjNBnVo
2B7MqFY/JSN+7wuzwG5f1SBcJbwwNgdKkOVT5ApUibShsz+kWz9iU5eG5M5pAWGl
02FF6AEmO9xnMzFBoG0TQQKBgQC0R7zy3CtD+jLMyFJg9t//Hup8Qe7TrLMTiFp5
1nVpgJzEKF4J31wvKyp2htyf+vl77RG1xLlZ6Fg55NkmPYukH2mt9T2cl2rt2VwB
gzkz9g24Epm21JIEK5VrFAZmbx5ap/B5fhcq2gFk56LEqZ+nVRI5D0X8LmAr5RQK
8ZlNSwKBgCwzAupnm7pkJSM/QGwT0BR7m09Uj/dlp5kwiVKzE0ZtxGps9bg8P+Ps
1XpAZn0WmtfopVxqXvyC/Z3a55Jq2hJ5q4mrUfNdbjzG+11ypaC+vPQy5iKlCR2N
wxH/LAj6oYlgVDNcb5ia2JnYXx7eLn1q8f8yNGm6zwaOr+4zZYOL
-----END RSA PRIVATE KEY-----
)";

// کلید عمومی برای تایید پیام‌ها
const char* publicKeyStr = R"("
-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAp1FWaJ2kwZKGg48itFCx
CfVJCMaTEP78wZ2ruEs1ux/ls/9B6XK4qLUK0UkFbS/s3wZtB8AEWU1O9hGhsDFp
LBCXtAAQTjYZzGK59xIvWSOgXvZ8W3NM0LaCMV7U5z6QvVvqXs88uTz+0grL7Zb1
VTZPwQq0A+R74jq4WVRuE6tTSvfu3u7Nz88NcXv/h42o6iWJ9pNQw2ONBF18sY2L
qJbSEdC1l6tNU7TmTQLn1FJxONzRkE8zDwJ8kn6iwlvSpk1HPIUWWKHf4vnNoFHY
G27jyZLHxigNTA0fRRZ2FSiH18I9IOdiR6Ys4wjWlK7Vi0fB7NKRq8x6v+M0HbfK
jQIDAQAB
-----END PUBLIC KEY-----
")";

// تابع امضای پیام با کلید خصوصی ثابت
std::string signMessage(const std::string& message) {
    RSA* rsa = nullptr;
    BIO* bio = BIO_new_mem_buf(const_cast<char*>(privateKeyStr), -1);
    rsa = PEM_read_bio_RSAPrivateKey(bio, &rsa, nullptr, nullptr);
    BIO_free(bio);

    if (!rsa) {
        std::cerr << "Error loading private key" << std::endl;
        return "";
    }

    unsigned int sigLen = RSA_size(rsa);
    unsigned char* signBuffer = new unsigned char[sigLen];

    if (RSA_sign(NID_sha256, reinterpret_cast<const unsigned char*>(message.c_str()), message.size(), signBuffer, &sigLen, rsa) != 1) {
        std::cerr << "Error signing the message" << std::endl;
        delete[] signBuffer;
        RSA_free(rsa);
        return "";
    }

    std::string signature(reinterpret_cast<char*>(signBuffer), sigLen);
    delete[] signBuffer;
    RSA_free(rsa);

    return signature;
}

// تابع تایید پیام با کلید عمومی
bool verifySignature(const std::string& message, const std::string& signature) {
    RSA* rsa = nullptr;
    BIO* bio = BIO_new_mem_buf(const_cast<char*>(publicKeyStr), -1);
    rsa = PEM_read_bio_RSA_PUBKEY(bio, &rsa, nullptr, nullptr);
    BIO_free(bio);

    if (!rsa) {
        std::cerr << "Error loading public key" << std::endl;
        return false;
    }

    if (RSA_verify(NID_sha256, reinterpret_cast<const unsigned char*>(message.c_str()), message.size(), reinterpret_cast<const unsigned char*>(signature.c_str()), signature.size(), rsa) != 1) {
        std::cerr << "Error verifying the signature" << std::endl;
        RSA_free(rsa);
        return false;
    }

    RSA_free(rsa);

    return true;
}

int main() {
    // پیام مورد امضاء
    std::string message;
    std::cout << "Enter the message to be signed: ";
    std::getline(std::cin, message);

    // امضاء پیام با کلید خصوصی ثابت
    std::string signature = signMessage(message);

    // چاپ پیام امضا شده
    std::cout << "Signed Message: " << signature << std::endl;

    // تایید پیام با کلید عمومی
    bool isVerified = verifySignature(message, signature);
    if (isVerified) {
        std::cout << "Signature is verified." << std::endl;
    } else {
        std::cout << "Signature verification failed." << std::endl;
    }

    return 0;
}