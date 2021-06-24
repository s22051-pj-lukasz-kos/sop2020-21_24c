#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int agrc, char *agrv[]) {
    char input[64];
    pid_t pid;

    pid = getpid();
    printf("PID: %d\tPPID: %d\tPGID: %d\n", pid, getppid(), getpgrp());

    scanf("%s", input);

    return 0;
}