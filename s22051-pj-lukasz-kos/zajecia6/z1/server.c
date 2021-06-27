#include <stdio.h>
#include <stdlib.h> /* funkcja exit */
#include <sys/socket.h>
//#include <sys/types.h>
#include <netinet/in.h>

/* 
Po stronie serwera należy:
1. Utworzyć gniazdo przy pomocy socket()
2. Ustalić adres IPv4 dla serwera przy użyciu struktury sockaddr_in
3. Połączyć gniazdo z adresem używając bind(). 
4. Nasłuchiwać połączeń przy użyciu listen()
5. Akceptować połączenia przy użyciu accept()
6. Wysyłać i otrzymywać dane poprzez write() i read() 
*/


/* Funkcja do obsługi błędów. Przyjmuje argument *s, określający komunikat błędu wyświetlony na stderr.
   Na końcu funkcja zamyka program z wartością EXIT_FAILURE */
void error(char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}

int main (int argc, char *argv[]) {
    int gniazdo;
    struct sockaddr_in serv_adrr;
    
    /* 
    W pierwszej kolejności tworzę gniazdo serwerowe do późniejszego nasłuchu 
    Podane wartości są domyślne dla TCP 
    Jeśli nie uda się utworzyć gniazda, socket() zwróci -1
    */
    gniazdo = socket(PF_INET,SOCK_STREAM,0);
    if(gniazdo < 0) {
        error("Gniazdo serwera nie zostało utworzone");
    }

    /*
    Następnie wypełniamy strukturę zawierającą adres sieciowy serwera
    */
    serv_adrr.sin_family = AF_INET; /* adress family Internet, format adresu */
    serv_adrr.sin_addr.s_addr = INADDR_ANY; /* POEKSPERYMENTOWAĆ z adresem IPv4, network byte order 
        INADDR_ANY - dowolny przychodzący adres
        INADDR_LOOPBACK - 127.0.0.1, localhost
        Do tworzenia adresu w formacie network byte order należy użyć funkcji 
        int inet_aton (const char *name, struct in_addr *addr) 
        gdzie name to adres IPv4 jako ciąg cyfr i kropek.
        Jeśli adres nie jest poprawny to funkcja zwróci 0 */
    serv_adrr.sin_port = htons(9091); /* numer portu w network byte order (dlatego używam funkcji htons) */

    /* 
    Następnie łączę gniazdo z adresem przy użyciu bind().
    Jeśli próba połączenia się nie powiedzie to bind() zwróci -1
    */
    if(bind(gniazdo, &serv_adrr, sizeof(serv_adrr) < 0)) {
        error("Nie udało się połączyć gniazda z adresem przy pomocy bind()");
    }

    /* 
    Następnie trzeba zrobić nasłuch na gniazdo po to, aby serwer mógł zaakceptować połączenie na gnieździe.
    Jeśli nasłuch się powiedzie, funkcja zwróci wartość -1
    */
    if(listen(gniazdo, 5)) {
        error("Niemożliwe ustanowienie nasłuchu na gniazdo sieciowe.");
    }




    return 0;
}