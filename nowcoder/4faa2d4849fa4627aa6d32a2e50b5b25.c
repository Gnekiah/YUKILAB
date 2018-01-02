#include <stdio.h>
#define max(x,y) (x>y?x:y)

int main() {
    int i = 0, j = 0, n = 0;
    int x[1000] = {0}, y[1000] = {0};
    
    y[0] = 1;
    scanf("%d", &i);
    while(scanf("%d %d ",&i, &j) != EOF) {
        if (x[i]++ < 2) {
            y[j] = y[i] + 1;
            n = max(n, y[j]);
        }
    }
    printf("%d\n", n);
    return 0;
}
