
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

void c_strcpy(char *strDest, char *strSrc)
{
while( (*strDest++ = *strSrc++) != '\0' );
}

int main(void) {
    char* name = "Joeeyuan";
    char name2[8] = {"J", "o", "e", "e", "y", "u", "a", "n"};
    cout << name2 << std::end;

    name[2] = "b";

}

