#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

void PrintValue(int a) {
    std::cout << "Value: " << a << std::endl;
}

void ForEach(const std::vector<int> &values, void(*func)(int)) {
    for (int value: values) {
        func(value);
    }
}

namespace cat {
    namespace wanwan {
        void print(const char* a) {
            std::cout << "wanwan: " << a << std::endl;
        }
    }
}

int main() {
    std::vector<int> values = { 1, 3, 4, 5, 2 };

    std::cout << "函数指针: " << std::endl;
    ForEach(values, PrintValue);

 
    std::cout << "lambda 函数: " << std::endl;
    ForEach(values, [](int a){std::cout << "Value: " << a << std::endl;});

    namespace a = cat::wanwan;
    a::print("kambda 函数和 find_if: ");
    auto its = std::find_if(values.begin(), values.end(), [](int value) {return value > 3; });


    std::cout << *its << std::endl;
}