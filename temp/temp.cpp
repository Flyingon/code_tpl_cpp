
#include <stdio.h>

#include <iostream>
#include <vector>
#include <string>

using namespace std;


void c_strcpy(char *strDest, char *strSrc) {
    while ((*strDest++ = *strSrc++) != '\0');
}

int test_return_int() {
    int i = 10;
    return i;
}

std::string *test_return_string() {
    std::string j = "10";
    std::cout << &j << std::endl;
    return &j;
}

class ABC {
public:
    int number;
    int numbers[5];

    ABC(int in_number) : number(in_number) {
        numbers[in_number] = in_number;
    }

    ~ABC() {
        std::cout << "~ABC" << std::endl;
    }
};

int main(void) {
//    std::string *res = test_return_string();
//    cout << res << endl;
    for (int i = 0; i < 5; i++) {
        ABC abc = ABC(i);
        std::cout << &abc << " " << &abc.number << " " << abc.number << " " << &abc.numbers << " " << abc.numbers[2]
                  << std::endl;
    }
}

