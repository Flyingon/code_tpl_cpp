#include <stdio.h>
#include <stdint.h>

int main() {
    int arr[] = {99, 15, 100, 888, 252};
    int len = sizeof(arr) / sizeof(int);  //求数组长度
    int i;
    for (i = 0; i < len; i++) {
        printf("%p: %d  \n", arr + i, *(arr + i));  //*(arr+i)等价于arr[i]
    }

    return 0;
}