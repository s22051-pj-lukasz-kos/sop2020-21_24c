#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void error(char *s) {
    perror(s);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    int gniazdo_klienta;


    /* W pierwszej kolejności należy ustawić gniazdo pod protokół TCP */
    gniazdo_klienta = socket(PF_INET, SOCK_STREAM, 0);
    /* i sprawdzić czy ten etap się powiódł */
    if(gniazdo_klienta < 0) {
        error("Nie udało się stworzyć gniazda klienta");
    }



    return 0;
}