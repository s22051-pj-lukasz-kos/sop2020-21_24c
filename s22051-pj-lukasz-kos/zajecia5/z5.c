#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int input;
    int liczba=atoi(argv[1]);
    pid_t pid = fork();

    if(pid > 0) {
        int suma = 0;
        int i;
        
        for(i = 0; i <= liczba; i++) {
            suma += i;
        }
        waitpid(0, NULL, 0);
        printf("Rodzic, suma: %d\n", suma);
    } else if(pid == 0) {
        int i;
        for (i = 1; i <= liczba; i+=2) {
            printf("Dziecko, liczba nieparzysta: %d\n", i);
        }
    } else {
        printf("Nie udało się utworzyć dziecka\n");
    }
    return 0;
}
