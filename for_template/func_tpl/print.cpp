# include <iostream>
# include <string>

template<typename T>
void Print(T value) {
    std::cout << value << std::endl;
}

int main() {
    Print(3);
    Print(3.14);
    Print("joeeyuan");
}