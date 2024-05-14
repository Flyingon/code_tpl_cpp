# include <iostream>
#include <cstdlib>
#include <iostream>
#include <string>

void *operator new(std::size_t n) {
    std::cout << "[Allocating " << n << " bytes]\n";
    return malloc(n);
}

void operator delete(void *p) noexcept {
    std::cout << "[Delete address: " << p << "]\n";
    free(p);
}

void newString(const int i) {
    std::cout << i << ": " << std::string(i, '=') << std::endl;
}

int testFunc() {
    for (size_t i = 0; i < 30; ++i) {
        {
            newString(i);
        }
    }
    return 0;
}

// 验证从什么长度开始，从堆上创建
int main() {
    testFunc();
    std::cout << "FINISH" << std::endl;
}

/* mac m1:
 0:
1: =
2: ==
3: ===
4: ====
5: =====
6: ======
7: =======
8: ========
9: =========
10: ==========
11: ===========
12: ============
13: =============
14: ==============
15: ===============
16: ================
17: =================
18: ==================
19: ===================
20: ====================
21: =====================
22: ======================
23: [Allocating 32 bytes]
=======================
[Delete address: 0x600001654040]
24: [Allocating 32 bytes]
========================
[Delete address: 0x600001654040]
25: [Allocating 32 bytes]
=========================
[Delete address: 0x600001654040]
26: [Allocating 32 bytes]
==========================
[Delete address: 0x600001654040]
27: [Allocating 32 bytes]
===========================
[Delete address: 0x600001654040]
28: [Allocating 32 bytes]
============================
[Delete address: 0x600001654040]
29: [Allocating 32 bytes]
=============================
[Delete address: 0x600001654040]
FINISH
 */