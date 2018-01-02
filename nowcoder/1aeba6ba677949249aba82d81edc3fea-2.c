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
