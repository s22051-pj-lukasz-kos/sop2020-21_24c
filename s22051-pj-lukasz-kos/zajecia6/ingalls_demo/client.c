#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
/* dołączony w celu zastosowania struktury hostent */
#include <netdb.h> 

/* obsługa błędów */
void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    /* struktura z adresem serwera */
    struct sockaddr_in serv_addr;

    /* struktura do przechowywania adresu hosta
    struct  hostent {
        char    *h_name;         oficjalna nazwa hosta 
        char    **h_aliases;     lista nazw symbolicznych 
        int     h_addrtype;      typ adresu hosta, AF_INET 
        int     h_length;        długość adresu w bitach 
        char    **h_addr_list;}; wskaźnik na listę adresów sieciowych, które kryją się za nazwą hosta 
        #define h_addr  h_addr_list[0]   pierwszy adres z listy powyżej, nie musisz go przekazywać, 
                                            ale możesz się do niego odwołać. 
    */ 
    struct hostent *server;
    char buffer[256];

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    /* nr portu przejęty z listy argumentów podczas wywołania */
    portno = atoi(argv[2]);

    /* tworzy nowe gniazdo po stronie klienta
        i zwraca deskryptor pliku do gniazda
        AF_INET - adres format
        SOCK_STREAM - połączenie podobne do potoku, ale dwukierunkowe
        trzeci argument to protocol=0. OS sam dobiera domyślne protokoły
        (TCP - SOCK_STREAM, UDP - SOCK_DGRAM) */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* jeśli podczas tworzenia deskryptora pliku do gniazda coś się nie uda, zwróci -1 */ 
    if (sockfd < 0) 
        error("ERROR opening socket");

    /* argv[1] zawiera nazwę hosta w Internecie, np. cheerios@cs.rpi.edu. 
        gethostbyname tworzy wskaźnik do struktury hostent zawierającą taką nazwę symboliczną */
    server = gethostbyname(argv[1]);

    /* obsługa błędu w razie jakby nie udało się stworzyć nazwy hosta */
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    /* ustawia wszystkie wartości w buforze na zero */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    /* definiowanie formatu adresu serwera i portu
        sin_family - format adresu, AF_INET */
    serv_addr.sin_family = AF_INET;

    /* funkcja do kopiowania łańcucha znaków */
    bcopy((char *)server->h_addr, /* kopiuje adres hosta... */
         (char *)&serv_addr.sin_addr.s_addr, /* ...do elementu struktury definiującej adres IPv4 */
         server->h_length); /* długość adresu w bitach, bcopy tego wymaga */
    
    /* sin_port - numer portu, ale musi być przekazany w formacie network byte order.
        Dlatego używamy funkcji htons */     
    serv_addr.sin_port = htons(portno);
    
    /* Następnie należy połączyć gniazdo klienta z adresem serwera używając connect(). */
    if (connect(sockfd, /* gniazdo po stronie klienta */
        (struct sockaddr *)&serv_addr, /* adres serwera */
        sizeof(serv_addr)) /* długość adresu serwera */
        < 0) /* obsługa błędu, gdy nie da się ustanowić połączenia */
        error("ERROR connecting");

    /* Komunikacja z serwerem. Używamy do tego celu read oraz write opartego o gniazdo klienta */
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    return 0;
}