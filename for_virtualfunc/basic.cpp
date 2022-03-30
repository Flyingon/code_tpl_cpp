#include <iostream>

class A
{
public:
    virtual void foo()
    {
        std::cout<<"A::foo() is called"<<std::endl;
    }
};
class B:public A
{
public:
    void foo()
    {
        std::cout<<"B::foo() is called"<<std::endl;
    }
};
int main(void)
{
    A *a = new B();
    a->foo();   // 在这里，a虽然是指向A的指针，但是被调用的函数(foo)却是B的!
    return 0;
}
