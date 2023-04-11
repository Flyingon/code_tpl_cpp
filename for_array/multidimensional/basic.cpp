#include <iostream>

int main() {
    int **a2d = new int *[5];

    for (int i = 0; i < 5; i++) {
        a2d[i] = new int[5];
    }
    std::cout << *a2d << std::endl;
}