#include <unistd.h>
#include <sys/types.h>
int x = 4;
pid_t t[4];
void death(void) {while(1){}}
int main() {
    while(x--) {
        t[x] = fork();
        if (!t[x]) death();
    }
    death();
    return 0; 
}
