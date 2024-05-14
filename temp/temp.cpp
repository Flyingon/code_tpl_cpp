#include <iconv.h>

int main() {
    // Open a conversion descriptor
    iconv_t cd = iconv_open("UTF-8", "ISO-8859-1");
    if (cd == (iconv_t)-1) {
        // Handle error
        perror("iconv_open failed");
        return 1;
    }

    // Use cd for conversion...

    // Close the conversion descriptor
    if (iconv_close(cd) != 0) {
        perror("iconv_close failed");
    }

    return 0;
}