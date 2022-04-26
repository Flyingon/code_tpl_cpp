#include <stdio.h>
#include <iostream>

using namespace std;

struct test1 {
    char c;
    int i;
};

struct __attribute__ ((__packed__)) test2 {
    char c;
    int i;
};

/* Note: sdshdr5 is never used, we just access the flags byte directly.
 * However is here to document the layout of type 5 SDS strings. */
struct __attribute__ ((__packed__)) sdshdr5 {
    unsigned char flags; /* 3 lsb of type, and 5 msb of string length */
    char buf[];
};
struct __attribute__ ((__packed__)) sdshdr8 {
    uint8_t len; /* used */
    uint8_t alloc; /* excluding the header and null terminator */
    unsigned char flags; /* 3 lsb of type, 5 unused bits */
    char buf[];
};
struct __attribute__ ((__packed__)) sdshdr16 {
    uint16_t len; /* used */
    uint16_t alloc; /* excluding the header and null terminator */
    unsigned char flags; /* 3 lsb of type, 5 unused bits */
    char buf[];
};
struct __attribute__ ((__packed__)) sdshdr32 {
    uint32_t len; /* used */
    uint32_t alloc; /* excluding the header and null terminator */
    unsigned char flags; /* 3 lsb of type, 5 unused bits */
    char buf[];
};
struct __attribute__ ((__packed__)) sdshdr64 {
    uint64_t len; /* used */
    uint64_t alloc; /* excluding the header and null terminator */
    unsigned char flags; /* 3 lsb of type, 5 unused bits */
    char buf[];
};

int main()
{
    cout << "size of test1:" << sizeof(struct test1) << endl;
    cout << "size of test2:" << sizeof(struct test2) << endl;

    printf("%ld\n", sizeof(struct sdshdr8));  // 3
    printf("%ld\n", sizeof(struct sdshdr16)); // 5
    printf("%ld\n", sizeof(struct sdshdr32)); // 9
    printf("%ld\n", sizeof(struct sdshdr64)); // 17
}
