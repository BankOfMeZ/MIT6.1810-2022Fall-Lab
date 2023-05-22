#include "kernel/types.h"
#include "user/user.h"

int main() {
    int p[2];
    char buf[1];
    pipe(p);
    write(p[1], "i", 1);
    int pid = fork();
    if (!pid) {
        int n = read(p[0], buf, 1);
        write(p[1], "o", 1);
        if (n == 1) {
            printf("%d: received ping\n", getpid());
            exit(0);
        }
        else {
            printf("Child reads error.\n");
            exit(1);
        }
    } else {
        wait((int *)0);
        int n = read(p[0], buf, 1);
        if (n == 1) {
            printf("%d: received pong\n", getpid());
            exit(0);
        }
        else {
            printf("Parent reads error.\n");
            exit(1);
        }
    }
}
