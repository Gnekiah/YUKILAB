#include "algos.h"

int str2uints(char* s, unsigned int *a) {
    int ret = 0;
    unsigned int i = 0;

    while (*s) {
        if (*s <= '9' && *s >= '0') {
            i = i * 10 + *s - '0';
        } else {
            if (i != 0) {
                *a++ = i;
                ++ret;
            }
            i = 0;
        }
        s++;
    }
    if (i != 0) {
        *a++ = i;
        ++ret;
    }

    return ret;
}
