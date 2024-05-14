#include <iostream>


void multi_type_vector() {
    std::vector<std::variant<std::string, float, int>> vec;
    vec.emplace_back("abc");
    vec.emplace_back(1);
    vec.emplace_back(0.2f);

    for (const auto &elem: vec) {
        if (const int *valInt = std::get_if<int>(&elem))
            std::cout << "variant value: " << *valInt << '\n';
        else if (const std::string *valStr = std::get_if<std::string>(&elem))
            std::cout << "variant value: " << *valStr << '\n';
        else if (const float *valFloat = std::get_if<float>(&elem))
            std::cout << "variant value: " << *valFloat << '\n';
        else
            std::cout << "failed to get value!" << '\n';
    }
}

int main() {
    multi_type_vector();
}