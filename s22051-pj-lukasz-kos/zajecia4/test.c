#include <stdio.h>

int main(int argc, char *argv[]) {
    char arr[64];
    char *p;
    char *arg[] = {"raz\n", "dwa\n", "trzy\n"};

    if (argc > 1) {
        printf("wpisz głupoty\n");
        scanf("%32s", arr);
        printf("głupota: %s\n", arr);
    } else {
        p = arg[1];
        printf("Tablica argumentów: %s", arg[1]);
        printf("Tablica zewnętrzna: %s", p);
    }
   
    return 0;
}