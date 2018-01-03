#include <stdio.h>
#include <string.h>
#define GG 65535

int n, x[10000];

int main() {
    int i = 0, ret = 0, j = 0, p = 0;

    scanf("%d", &n);
    while(scanf("%d", &x[i++]) != EOF) {
        if (getchar() != ' ') break;
    }

    i = 0;
    while (i < n) {
        p = x[i]+i;
        if (p >= n) {
            ret++;
            break;
        }
        for (j=p; j > i; j--)
            if (x[j]+j > x[p]+p)
                p = j;
        if (x[p] == 0) {
            ret = -1;
            break;
        }
        i = p;
        ret++;
    }
    printf("%d\n", ret);
    return 0;
}
