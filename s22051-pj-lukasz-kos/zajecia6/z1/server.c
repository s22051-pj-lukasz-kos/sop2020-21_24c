#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
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
void error(char*);

int main (int argc, char *argv[]) {
    int gniazdo_nasluchowe, gniazdo_polaczeniowe;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_addr_len;
    
    /* 
    W pierwszej kolejności tworzę gniazdo serwerowe do późniejszego nasłuchu 
    Podane wartości są domyślne dla TCP 
    Jeśli nie uda się utworzyć gniazda, socket() zwróci -1
    */
    gniazdo_nasluchowe = socket(PF_INET,SOCK_STREAM,0);
    if(gniazdo_nasluchowe < 0) {
        error("Gniazdo serwera nie zostało utworzone");
    }

    /*
    Następnie wypełniamy strukturę zawierającą adres sieciowy serwera
    */
    serv_addr.sin_family = AF_INET; /* adress family Internet, format adresu */
    serv_addr.sin_addr.s_addr = INADDR_ANY; /* POEKSPERYMENTOWAĆ z adresem IPv4, network byte order 
        INADDR_ANY - dowolny przychodzący adres
        INADDR_LOOPBACK - 127.0.0.1, localhost
        Do tworzenia adresu w formacie network byte order należy użyć funkcji 
        int inet_aton (const char *name, struct in_addr *addr) 
        gdzie name to adres IPv4 jako ciąg cyfr i kropek.
        Jeśli adres nie jest poprawny to funkcja zwróci 0 */
    serv_addr.sin_port = htons(9091); /* numer portu w network byte order (dlatego używam funkcji htons) */

    /* 
    Następnie łączę gniazdo z adresem przy użyciu bind().
    Jeśli próba połączenia się nie powiedzie to bind() zwróci -1 */
    if(bind(gniazdo_nasluchowe, &serv_addr, sizeof(serv_addr) < 0)) {
        error("Nie udało się połączyć gniazda z adresem przy pomocy bind()");
    }

    /* 
    Następnie trzeba zrobić nasłuch na gniazdo po to, aby serwer mógł zaakceptować połączenie na gnieździe.
    Jeśli nasłuch się nie powiedzie, funkcja zwróci wartość -1 */
    if(listen(gniazdo_nasluchowe, 5) < 0) {
        error("Niemożliwe ustanowienie nasłuchu na gniazdo sieciowe.");
    }

    /* Następnie można zaakceptować nadchodzące połączenie funkcją accept(), 
    które tworzy nowe gniazdo do komunikacji z klientem.
    Wskaźniki na adres i długość adresu dotyczą adresu KLIENTA */
    cli_addr_len = sizeof(cli_addr);
    gniazdo_polaczeniowe = accept(gniazdo_nasluchowe, &cli_addr, &cli_addr_len);
    if(gniazdo_polaczeniowe < 0) {
        error("Serwer nie zaakceptował połączenia.");
    }

    /* Teraz następuje przesyłanie danych */


    return 0;
}

void error(char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}