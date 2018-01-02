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
