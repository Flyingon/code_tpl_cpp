#include <iostream>
#include <vector>

void PrintValue(int a) {
    std::cout << "Value: " << a << std::endl;
}

void ForEach(const std::vector<int> &values, void(*func)(int)) {
    for (int value: values) {
        func(value);
    }
}

int main() {
    std::vector<int> values = {1,  3, 4, 5, 2};
    ForEach(values, PrintValue);
    std::cout << " " << std::endl;
    ForEach(values, [](int a){std::cout << "Value: " << a << std::endl;});
}