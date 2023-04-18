
#include <stdio.h>

#include <iostream>
//#include <GLFW/glfw3.h>


void c_strcpy(char *strDest, char *strSrc) {
    while ((*strDest++ = *strSrc++) != '\0');
}

int test_return_int() {
    int i = 10;
    return i;
}

std::string* test_return_string() {
    std::string j = "10";
    std::cout << &j << std::endl;
    return &j;
}

int main(void) {
//    int res = glfwInit();

    std::string *res = test_return_string();
    std::cout << *res << std::endl;
}

