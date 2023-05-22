#include "kernel/types.h"
#include "user/user.h"

int main() {
    int p[2];
    pipe(p);
    for (int i = 2; i <= 35; i++) {
        if (write(p[1], &i, 4) != 4) {
            printf("Write %d error.\n", i);
            exit(1);
        }
    }
    int i;
    do {
        close(p[1]);
        if (fork()) {
            wait((int *)0);
            exit(0);
        } else {
            int buf[34], cur, t;
            i = 0;
            if (read(p[0], &cur, 4) != 4) {
                printf("Read error.\n");
                exit(1);
            }
            printf("prime %d\n", cur);
            while (read(p[0], &t, 4)) {
                if (t % cur)
                    buf[i++] = t;
            }
            close(p[0]);
            pipe(p);
            for (int j = 0; j < i; j++)
                if (write(p[1], buf + j, 4) != 4) {
                    printf("Write %d error.\n", buf[j]);
                    exit(1);
                }
        }
    } while (i);
    exit(0);
}
