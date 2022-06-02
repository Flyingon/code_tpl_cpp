
#include <stdio.h>
#include <unistd.h>


int main(void) {
#ifdef __Linux__
    printf("linux");
#elif __APPLE__
    printf("apple");
#elif _WIN32
    printf("windows");
#endif
}

