/*
 * 给定一个句子（只包含字母和空格）， 将句子中的单词位置
 * 反转，单词用空格分割, 单词之间只有一个空格，前后没有
 * 空格。 比如： （1） “hello xiao mi”-> “mi xiao hello”
 * */

#include <stdio.h>
#include <string.h>

int main() {
    int n = 0, i = 0;
    char s[1000];
    char *p;
    while(gets(s)) {
        n = strlen(s);
        for (i=0; i < n; i++) {
            if (s[i] == ' ')
                s[i] = '\0';
        }
        while (n--) {
            if (s[n] == '\0') {
                p = &s[n+1];
                printf("%s ", p);
            }
        }
        printf("%s\n", s);
    }
    return 0;
}
