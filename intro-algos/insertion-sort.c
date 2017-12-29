#include <stdio.h>
#include "algos.h"

int main(int argc, char* argv[]) {
    int ret=0, i=0, j=0;
    unsigned int k, a[100];
    char s[1024];

    printf("A=");
    gets(s);
    ret = str2uints(s, a);

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


