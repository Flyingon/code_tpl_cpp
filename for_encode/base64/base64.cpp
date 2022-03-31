
#include <iostream>
#include "common/base64.h"
#include "common/base64.cpp"

using namespace std;

int main() {
    std::string a = "12345";
    std::string encode_str = base64_decode(a);
    cout << a.c_str() << " base64: " << encode_str << endl;
}