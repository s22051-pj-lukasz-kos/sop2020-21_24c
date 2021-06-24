#include <stdio.h>
#include <unistd.h>

int main(int agrc, char *agrv[]) {
    printf("PID: %d\tPPID: %d\n", getpid(), getppid());

    return 0;
}