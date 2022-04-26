//#ifndef __cplusplus

//#endif


#include <iostream>
#include "stdio.h"
#include <stdlib.h>

using namespace std;

struct stru_empty {

};
struct stru1 {
    int a;  //start address is 0
    char b;  //start address is 4
    int c;  //start address is 8
};
struct stru2 {
    int i;  //start address is 0
    short m;  //start address is 4
};
struct stru3 {
    char i;  //start address is 0
    int m;   //start address is 4
    char n;  //start address is 8
};
struct stru4 {
    char i;  //start address is 0
    char n;  //start address is 1
    int m;  //start address is 4
};

struct stru5 {
    short i;
    struct {
        char c;
        int j;
    } ss;
    int k;
};
struct stru6 {
    char i;
    struct {
        char c;
        int j;
    } tt;
    char a;
    char b;
    char d;
    char e;
    int f;
};
struct stru7 {
    char i;
    struct {
        char c;
        //int j;
    } tt;
    char a;
    char b;
    char d;
    char e;
    int f;
};
struct tArray {
    float f;
    char p;
    int arr[3];
};

int main() {
    struct stru6 st6;
    struct stru7 st7;
    struct tArray ar;
    printf("sizof(char)=%d \n", sizeof(char));
    printf("sizof(int)=%d \n", sizeof(int));
    printf("sizof(short int)=%d \n", sizeof(short int));
    printf("sizof(long int)=%d \n", sizeof(long int));
    printf("sizof(long)=%d \n", sizeof(long));
    printf("sizof(float)=%d \n\n", sizeof(float));

    printf("sizof(uint)=%d \n", sizeof(uint));
    printf("sizof(uint16_t)=%d \n", sizeof(uint16_t));
    printf("sizof(uint32_t)=%d \n", sizeof(uint32_t));
    printf("sizof(uint64_t)=%d \n", sizeof(uint64_t));
    printf("sizof(uint8_t)=%d \n", sizeof(uint8_t));

    printf("sizof(stru_empty)=%d \n", sizeof(stru_empty));
    printf("sizof(stru1)=%d \n\n", sizeof(stru1));
    printf("sizof(stru2)=%d \n\n", sizeof(stru2));
    printf("sizof(stru3)=%d \n\n", sizeof(stru3));
    printf("sizof(stru4)=%d \n\n", sizeof(stru4));
    printf("sizof(stru5)=%d \n\n", sizeof(stru5));
    printf("sizof(stru6)=%d \n", sizeof(stru6));
    printf("sizof(stru6.tt)=%d \n", sizeof(st6.tt));
    printf("the address of stru6.i=%d \n", &st6.i);
    printf("the address of stru6.a=%d \n\n", &st6.a);

    printf("sizof(stru7)=%d \n", sizeof(stru7));
    printf("sizof(stru7)=%d \n", sizeof(st7.tt));
    printf("the address of stru7.i=%d \n", &st7.i);
    printf("the address of stru7.a=%d \n\n", &st7.a);

    printf("sizof(ar)=%d \n", sizeof(ar));
    printf("sizof(ar.f)=%d \n", sizeof(ar.f));
    printf("sizof(ar.arr)=%d \n", sizeof(ar.arr));
    return 0;
}