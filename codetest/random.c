#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFF_SIZE 16

inline void* wtf_next_pos(unsigned char* c, unsigned char* s, int n) {
    return s - c & (n-1);
}

unsigned int wtf_random(void) {
    unsigned char *buff;
    unsigned int retval;
    unsigned char *pos;
    int i = 0;

    buff = (unsigned char*)malloc(BUFF_SIZE * sizeof(unsigned char));
    pos = buff;
    
    for (; i < 40; i++) {
        pos = wtf_next_pos(pos, buff, BUFF_SIZE);
        printf("%d ", (char)pos);
    }
    retval = (int)pos;
    return retval;
}

int main() {
    wtf_random();
    return 0;
}
