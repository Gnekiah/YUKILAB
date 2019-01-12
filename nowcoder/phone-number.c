/*
 * 继MIUI8推出手机分身功能之后，MIUI9计划推出一个电话号码分身的功
 * 能：首先将电话号码中的每个数字加上8取个位，然后使用对应的大写
 * 字母代替 （"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX",
 * "SEVEN", "EIGHT", "NINE"）， 然后随机打乱这些字母，所生成的字符
 * 串即为电话号码对应的分身。
 * */

#include <stdio.h>
#include <string.h>

/*Z0/W2/U4/X6/G8->S7->V5->I9->O1->H3*/
int main() {
    int n = 0, i = 0;
    char s[10000];
    /* Z O W H U V X S G I */
    int x[10] = {0};

    scanf("%d", &n);
    while(scanf("%s", s) != EOF) {
        memset(x, 0, sizeof(int)*10);
        n = strlen(s);
        while(n--) {
            switch(s[n]) {
            case 'G': x[0]++; break;
            case 'I': x[1]++; break;
            case 'Z': x[2]++; break;
            case 'O': x[3]++; break;
            case 'W': x[4]++; break;
            case 'H': x[5]++; break;
            case 'U': x[6]++; break;
            case 'V': x[7]++; break;
            case 'X': x[8]++; break;
            case 'S': x[9]++; break;
            default: break;
            }
        }
        x[9] -= x[8];
        x[7] -= x[9];
        x[1] -= (x[7] + x[8] + x[0]);
        x[3] -= (x[2] + x[4] + x[6]);
        x[5] -= x[0];
        for (i=0; i < 10; i++)
            while(x[i]-- > 0)
                printf("%d", i);
        printf("\n");
    }
    return 0;
}
