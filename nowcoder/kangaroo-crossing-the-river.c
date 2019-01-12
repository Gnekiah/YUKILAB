/*
 *一只袋鼠要从河这边跳到河对岸，河很宽，但是河中间打了很多
 * 桩子，每隔一米就有一个，每个桩子上都有一个弹簧，袋鼠跳
 * 到弹簧上就可以跳的更远。每个弹簧力量不同，用一个数字代
 * 表它的力量，如果弹簧力量为5，就代表袋鼠下一跳最多能够跳
 * 5米，如果为0，就会陷进去无法继续跳跃。河流一共N米宽，袋
 * 鼠初始位置就在第一个弹簧上面，要跳到最后一个弹簧之后就
 * 算过河了，给定每个弹簧的力量，求袋鼠最少需要多少跳能够
 * 到达对岸。如果无法到达输出-1
 * */

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
