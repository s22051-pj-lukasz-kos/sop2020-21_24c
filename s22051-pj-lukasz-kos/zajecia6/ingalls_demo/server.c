/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

/* obsługa błędów */
void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    /* struktura, w której zawarty będzie adres 
        serv_addr to adres serwera
        cli_addr to adres klienta */
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    /* jako argument musisz podać numer portu */
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    /* tworzy nowe gniazdo 
        AF_INET - adres format
        SOCK_STREAM - połączenie podobne do potoku, ale dwukierunkowe
        trzeci argument to protocol=0. OS sam dobiera domyślne protokoły
        (TCP - SOCK_STREAM, UDP - SOCK_DGRAM) */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* tworzy deskryptor pliku do gniazda
        jeśli coś się nie uda, zwróci -1 */ 
    if (sockfd < 0) 
        error("ERROR opening socket");
    /* ustawia wszystkie wartości w buforze na zero */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    /* nr portu przejęty z listy argumentów podczas wywołania */
    portno = atoi(argv[1]);

    /* definiowanie adresu 
        sin_family - format adresu, AF_INET */
    serv_addr.sin_family = AF_INET;
    /* sin_addr - struktura in_addr, zawierająca adres IPv4 hosta. 
            OS zastępuje INADDR_ANY faktycznym adresem maszyny */
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    /* sin_port - numer portu, ale musi być przekazany w formacie network byte order.
            Dlatego używamy funkcji htons */
    serv_addr.sin_port = htons(portno);

    /* Wiążemy ze sobą gniazdo serwera oraz jego adres (wraz z portem) */
    if (bind(sockfd, /* deskryptor gniazda */
            (struct sockaddr *) &serv_addr, /* struktura z adresem (wraz z portem) */
            sizeof(serv_addr)) /* rozmiar adresu */
            < 0) /* bind zwraca -1 jak coś się nie powiedzie */
        error("ERROR on binding");
    
    /* nasłuch na gniazdo. 5 to maksymalna liczba czekających połączeń 
        (działa na większości systemach) */
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    /* akceptuje połączenie z klientem. Zwraca deskryptor pliku do 
        nowego gniazda, które będzie odpowiadać za komunikację z klientem */
    newsockfd = accept(sockfd,  /* stare gniazdo nasłuchowe */
        (struct sockaddr *) &cli_addr,  /* adres klienta */
        &clilen);   /* długość adresu klienta */
    /* obsługa błędu przy próbie akceptacji połączenia z klientem */
    if (newsockfd < 0) 
        error("ERROR on accept");

    /* Komunikacja z klientem. Używamy do tego celu read oraz write opartego o nowe gniazdo */
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    n = write(newsockfd,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");
    return 0; 
}