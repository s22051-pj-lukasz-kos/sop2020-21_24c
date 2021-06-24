#include <stdio.h>
#include <unistd.h>

int main(int agrc, char *agrv[]) {
    char input[64];


    printf("PID: %d\tPPID: %d\n", getpid(), getppid());

    scanf("%s", input);

    return 0;
}