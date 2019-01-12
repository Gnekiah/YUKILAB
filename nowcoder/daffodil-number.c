/*
 * 春天是鲜花的季节，水仙花就是其中最迷人的代表，数学
 * 上有个水仙花数，他是这样定义的： “水仙花数”是指一
 * 个三位数，它的各位数字的立方和等于其本身，比
 * 如：153=1^3+5^3+3^3。 现在要求输出所有在m和n范围内
 * 的水仙花数。
 * */

#include <stdio.h>

int map[10];

int func(int m, int n, int x[]) {
    int ret = 0;
    for (int p=n; p >= m; p--) {
        if (p == (map[p/100] + map[p/10%10] + map[p%10]))
            x[ret++] = p;
    }
    return ret;
}

int main() {
    int m = 0, n = 0, ret = 0;
    int x[50];

    for (int i=0; i < 10; i++)
        map[i] = i*i*i;

    while(scanf("%d %d", &m, &n) != EOF) {
        ret = func(m, n, x);
        if (ret == 0)
            printf("no");
        while(ret--) {
            printf("%d", x[ret]);
            if (ret)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}
