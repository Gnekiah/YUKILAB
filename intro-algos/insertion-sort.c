#include <stdio.h>

int parse_str(const char* s, unsigned short *a) {
    int ret = 0;
    unsigned short i = 0;

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

int main(int argc, char* argv[]) {
    int ret=0, i=0, j=0;
    unsigned short k, a[100];
    char s[1024];

    printf("A=");
    gets(s);
    ret = parse_str(s, a);

    for (i = 1; i < ret; i++) {
        k = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > k) {
            a[j+1] = a[j];
            --j;
        }
        a[j+1] = k;
    }

    printf("RESULT=");
    while(ret--)
        printf("%u > ", a[ret]);
    printf("\b\b \n");

    return 0;
}
