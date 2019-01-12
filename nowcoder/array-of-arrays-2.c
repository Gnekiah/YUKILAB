/*
 * 给定一个数组序列, 需要求选出一个区间, 使得该区间是所有区间中经
 * 过如下计算的值最大的一个：区间中的最小数 * 区间所有数的和最后
 * 程序输出经过计算后的最大值即可，不需要输出具体的区间。如给定序
 * 列  [6 2 1]则根据上述公式, 可得到所有可以选定各个区间的计算值:
 *
 * [6] = 6 * 6 = 36;
 * [2] = 2 * 2 = 4;
 * [1] = 1 * 1 = 1;
 * [6,2] = 2 * 8 = 16;
 * [2,1] = 1 * 3 = 3;
 * [6, 2, 1] = 1 * 9 = 9;
 *
 * 从上述计算可见选定区间 [6] ，计算值为 36， 则程序输出为 36。
 * 区间内的所有数字都在[0, 100]的范围内;
 * */

#include <stdio.h>

int x[500000];
long MAX(long x, long y) { return x > y ? x : y; }

int func(int l, int r, long max) {
    long sum = 0;
    int min = x[l];
    int index = l;
    int i = 0;

    if (l+1 == r) 
        return MAX(max, x[l] * x[l]);

    for (i=l; i < r; i++) {
        sum += x[i];
        if (min > x[i]) {
            min = x[i];
            index = i;
        }
    }
    max = MAX(max, sum * min);

    if (index == l) {
        max = MAX(max, func(index+1, r, max));
    }
    else if(index+1 == r) {
        max = MAX(max, func(l, index, max));
    } else {
        max = MAX(max, func(index+1, r, max));
        max = MAX(max, func(l, index, max));
    }
    return max;
}

int main() {
    long n = 0;
    int i = 0;
    
    scanf("%ld", &n);
    while(scanf("%d",&x[i++]) != EOF)
        if (getchar() != ' ') break;
    
    n = func(0, i, 0);
    printf("%ld\n", n);
    return 0;
}
