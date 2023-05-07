#include<iostream>
#include<vector>

struct Foo {
    Foo() { std::cout << "Constructed" << std::endl; }

    Foo(const Foo &) { std::cout << "Copy-constructed" << std::endl; }

    Foo(Foo &&) { std::cout << "Move-constructed" << std::endl; }

    ~Foo() { std::cout << "Destructed" << std::endl; }
};

int main() {
    std::vector <Foo> vec;
    vec.push_back(Foo());  // Foo() 是右值，所以: 优先执行:  Move-constructed -> 没有执行: Copy-constructed
    return 0;
}