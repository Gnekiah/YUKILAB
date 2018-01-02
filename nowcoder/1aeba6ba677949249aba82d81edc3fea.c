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
