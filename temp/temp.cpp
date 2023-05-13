
#include <stdio.h>

#include <iostream>
//#include <GLFW/glfw3.h>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace  std;
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

int main(void) {
//    int res = glfwInit();

//    std::string *res = test_return_string();
//    std::cout << *res << std::endl;
//    char a_str[100] = "aaa,fff,eedakc,cccc";
//    char *ptr = strtok(a_str, ",");
//    std::cout << "XXX: " << ptr << std::endl;
    string a = "";
    cout << a.size() << endl;
    cout << a.length() << endl;
}

