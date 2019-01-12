/*
 * 数列的第一项为n，以后各项为前一项的平方根，求数列的前m项的和。
 * */

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
