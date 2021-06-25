#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t pid_fork_a;
    pid_t pid_fork_a2;
    pid_t pid_fork_b;
    pid_t pid_fork_b2;
    pid_t pid_fork_c;
    pid_t pid_fork_c2;

    printf("A. PID: %d\tPPID: %d\n", getpid(), getppid());
    pid_fork_a = fork();
    waitpid(0,NULL,0);
    if(pid_fork_a > 0) {
        pid_fork_a2 = fork();
        waitpid(0,NULL,0);
        if(pid_fork_a2 == 0) {
            printf("C. PID: %d\tPPID: %d\n", getpid(), getppid());
            pid_fork_c = fork();
            waitpid(0,NULL,0);
            if(pid_fork_c > 0) {
                pid_fork_c2 = fork();
                waitpid(0,NULL,0);
                if(pid_fork_c2 == 0) {
                    printf("G. PID: %d\tPPID: %d\n", getpid(), getppid());
                }
            } else if (pid_fork_c == 0) {
                printf("F. PID: %d\tPPID: %d\n", getpid(), getppid());
            }
        }
    } else if (pid_fork_a == 0){
        printf("B. PID: %d\tPPID: %d\n", getpid(), getppid());
        pid_fork_b = fork();
        waitpid(0,NULL,0);
        if (pid_fork_b > 0) {
            pid_fork_b2 = fork();
            waitpid(0,NULL,0);
            if(pid_fork_b2 == 0) {
                printf("E. PID: %d\tPPID: %d\n", getpid(), getppid());
            }
        } else if (pid_fork_b == 0){
            printf("D. PID: %d\tPPID: %d\n", getpid(), getppid());
        }
    }
    return 0;
}