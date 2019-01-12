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
long MAX(long x, long y) { return x > y ? x : y; }

int func(int* left, int* right, long max) {
    long sum = 0;
    int *min = left;
    int *l=left, *r=right;

    if (l+1 == r) 
        return MAX(max, *l**l);

    while(l!=r) {
        if (*min > *l) 
            min = l;
        sum += *l++;
    }
    max = MAX(max, sum**min);

    if (min == left) {
        max = MAX(max, func(left+1, right, max));
    }
    else if(min+1 == right) {
        max = MAX(max, func(left, right-1, max));
    } else {
        max = MAX(max, func(left, min, max));
        max = MAX(max, func(min+1, right, max));
    }
    return max;
}

int main() {
    long n = 0;
    int i = 0;
    int x[500000];
    
    scanf("%ld", &n);
    while(scanf("%d",&x[i++]) != EOF) {
        if (getchar() != ' ') break;
    }
    
    n = func(&x[0], &x[i], 0);
    printf("%ld\n", n);
    return 0;
}
