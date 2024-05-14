#include <format>
#include <iostream>
#include <utility>
#include <vector>

class TestCls {
public:
    std::vector<int> myVec;

    explicit TestCls(std::vector<int> newVector) : myVec(std::move(newVector)) {
        std::cout << "Construct execute " << &myVec <<  std::endl;
    };

    TestCls( const TestCls &obj) {
        std::cout << "Copy Construct execute " << &obj << std::endl;
    };

    ~TestCls() {
        std::cout << "DeConstruct execute " << &myVec << std::endl;
        myVec.clear();
    };

    void print() {
        for (int i: myVec)
            std::cout << i << " ";
        std::cout << "\n";
    }
};

// 直接 栈 创建结构体实例，用指针返回
TestCls *func1() {
    TestCls test(std::vector<int>{1, 2, 3});
    std::cout << "函数内栈创建结构体实例地址: " << &test << std::endl;
    return &test;
}

void callFunc1() {
    auto res1 = func1();
    std::cout << "函数调用结束";
    std::cout << "函数返回地址: " << res1 << std::endl;
    res1->print();
}

// 用 new 在 堆 创建结构体实例，用指针返回
TestCls *func2() {
    auto test = new TestCls(std::vector<int>{1, 2, 3});
    std::cout << "函数内创建结构体实例地址: " << test << std::endl;
    return test;
}

void callFunc2() {
    auto res = func2();
    std::cout << "函数调用结束";
    std::cout << "函数返回地址: " << res << std::endl;
    res->print();
}


// 直接 栈 创建结构体实例，直接返回
TestCls func3() {
    TestCls test(std::vector<int>{1, 2, 3});
    std::cout << "函数内栈创建结构体实例地址: " << &test << std::endl;
    return test;
}

void callFunc3() {
    auto res1 = func3();
    std::cout << "函数调用结束";
    std::cout << "函数返回地址: " << &res1 << std::endl;
    res1.print();
}

// 直接 栈 创建结构体实例，引用返回
TestCls &func4() {
    TestCls test(std::vector<int>{1, 2, 3});
    std::cout << "函数内栈创建结构体实例地址: " << &test << std::endl;
    return test;
}

void callFunc4() {
    auto res1 = func4();
    std::cout << "函数调用结束";
    std::cout << "函数返回地址: " << &res1 << std::endl;
    res1.print();
}

// 用 new 在 堆 创建结构体实例，引用返回
TestCls &func5() {
    auto test = new TestCls(std::vector<int>{1, 2, 3});
    std::cout << "函数内栈创建结构体实例地址: " << &test << std::endl;
    return *test;
}

void callFunc5() {
    auto res1 = func5();
    std::cout << "函数调用结束";
    std::cout << "函数返回地址: " << &res1 << std::endl;
    res1.print();
}

int main(int argc, char *argv[]) {
    std::cout << "直接 栈 创建结构体实例，指针返回，【不能这样写】，函数返回时候，栈内存已经释放: \n";
    callFunc1();

    std::cout << "\n直接 栈 创建结构体实例，直接返回，【可以这样写】没有多余复制: \n";
    callFunc3();

    std::cout << "\n直接 栈 创建结构体实例，引用返回，【不能这样写】，函数返回时候，栈内存已经释放: \n";
    callFunc4();

    std::cout << "\n用 new 在 堆 创建结构体实例，指针返回，【最好不要这样写】，未调析构函数，内存泄漏，后面要调用 delete: \n";
    callFunc2();

    std::cout << "\n用 new 在 堆 创建结构体实例，引用返回，【最好不要这样写】多一次复制，函数内创建的实例未调析构函数，内存泄漏，后面要调用 delete，: \n";
    callFunc5();


}

