/*
 * 设有n个正整数，将他们连接成一排，组成一个最大的多位整数。
 * 如:n=3时，3个整数13,312,343,连成的最大整数为34331213。
 * 如:n=4时,4个整数7,13,4,246连接成的最大整数为7424613。
 * */

#include <stdio.h>

inline int padding(int m) {
    if (m < 10)
        m = m*100+m*10+m;
    else if (m < 100)
        m = m*10+(m/10);
    return m;
}

inline int making(int m, int n) {
    if (n < 10)
        m = m * 10 + n;
    else if (n < 100)
        m = m * 100 + n;
    else
        m = m * 1000 + n;
    return m;
}

inline int bigger(int m, int n) {
    int x, y;
    x = padding(m);
    y = padding(n);
    if (x > y)
        return 1;
    if (x < y)
        return 0;
    x = making(m,n);
    y = making(n,m);
    return x > y ? 1 : 0;
}

int func(int n, int x[]) {
    int i=0, j=0, tmp=0;
    for (i=n; i > 1; i--) {
        for (j=0; j < i-1; j++) {
            if (bigger(x[j+1], x[j])) {
                tmp = x[j+1];
                x[j+1] = x[j];
                x[j] = tmp;
            }
        }
    }
    return 0;
}

int main() {
    int n = 0;
    int i = 0;
    int x[100];
    
    scanf("%d", &n);
    while(scanf("%d",&x[i++]) != EOF) {
        if (getchar() != ' ') break;
    }
    
    func(n, x);
    for (i=0; i < n; i++) {
        printf("%d", x[i]);
    }
    printf("\n");
    return 0;
}
