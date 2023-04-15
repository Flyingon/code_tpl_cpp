#include<iostream>

struct Entity {
    int x, y;
};

int main() {
    Entity e = {5, 8};
    int *position = (int *) &e;

    int y = *(int *) ((char *) &e + 4);
    int z = *(int *) ((int *) &e + 1);
    std::cout << position[0] << ", " << position[0] << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "z: " << z << std::endl;
}