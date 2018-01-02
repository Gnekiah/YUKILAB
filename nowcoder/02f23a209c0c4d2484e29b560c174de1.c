#include <stdio.h>
#include <math.h>

int main() {
    int m = 0, n = 0;
    double ret = 0, tmp = 0;

    scanf("%d %d", &m, &n);
    ret = tmp = m;
    while(--n) {
        tmp = sqrt(tmp);
        ret += tmp;
    }
    printf("%.2lf\n", ret);
    return 0;
}
