#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int i;
    pid_t master_pid;
    
    master_pid = getpid();
    printf("Master PID: %d\n", master_pid);
    for(i = 0; i < 100; i++) {
        if(getpid() == master_pid){
            if(fork() == 0){
                printf("i=%d\tPID: %d, PPID: %d\n", i, getpid(), getppid());
                fflush(stdout);
            }
        }
    }
    if(master_pid == getpid()){
        waitpid(0,NULL,0);
        printf("Rodzic zaczekał, koniec\n");
    }
    return 0;
}
