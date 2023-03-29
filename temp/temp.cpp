
#include <stdio.h>

#include <iostream>
#include <GLFW/glfw3.h>


void c_strcpy(char *strDest, char *strSrc) {
    while ((*strDest++ = *strSrc++) != '\0');
}

int main(void) {
    int res = glfwInit();
    std::cout << res << std::endl;
}

