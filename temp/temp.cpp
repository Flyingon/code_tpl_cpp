
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

void c_strcpy(char *strDest, char *strSrc) {
    while ((*strDest++ = *strSrc++) != '\0');
}

int main(void) {
    char* name = "joeyuan";
    name[2] = 'b';
    std::cout << name << std::endl;
    return 0;
}

