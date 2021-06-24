#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int i;
    pid_t pid;

    for(i = 0; i < 100; i++) {
        pid = fork();
        if(pid > 0) {
            wait(NULL);
            break;
        } else {
            printf("i=%d\tPID: %d, PPID: %d\n", i, getpid(), getppid());
        }
    }
    return 0;
}