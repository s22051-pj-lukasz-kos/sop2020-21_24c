# Zajęcia 6
## Obsługa sygnałów
W pierwszej kolejności należy dołączyć bibliotekę `<signal.h>`. Jednakże...
Z racji tego, że część funkcji tej biblioteki (np. typ `sigset_t` czy struktura `sigaction`) nie stanowi standartu języka ANSI C, to należy je zdefiniować przy użyciu makra. Przed 'blokiem' `#include` należy dopisać
```c
#define _POSIX_SOURCE
```
Co pozwoli na użycie funkcjonalności standardu POSIX w wersji 1. Oczywiście można to zrobić na wiele sposobów, po szczegóły odsyłam [TU](https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html#Feature-Test-Macros).

Generalnie sygnał jest to przerwanie dostarczone do procesu. Systemy operacyjne używają sygnałów do raportowania wyjątkowych sytuacji np. błędów, eventów czy próśb.
Linux umożliwia przechwycenie sygnału oraz zmianę jego standardowego zachowania poprzez użycie funkcji `signal()` lub `sigaction()`.
`sigaction()` ma to samo zastosowanie co funkcja `signal()`, aczkolwiek pozwala na znacznie większą kontrolę poprzez zdefiniowanie flag w strukturze (SIC) `sigaction`.
```c
struct sigaction {
	/* tutaj ustawiasz nową procedurę obsługi.
	Domyślne to: SIG_DFL (signal default, domyślna obsługa) lub SIG_IGN (ignorowanie sygnału).
	Można również ustawić wskaźnik na własną funkcję obsługującą sygnał. */
	sighandler_t sa_handler

	/* Zbiór sygnałów, które będą przechwytywane PONAD TO co zdefiniujemy w funkcji sigaction. Stąd nazwa maska.
	Jako, że chcemy przechwycić tylko jeden sygnał, to ta maska może pozostać pusta. 
	Puste maski generuje się funkcją int sigemptyset(sigset_t *set). */
	sigset_t sa_mask

	/* Ustanawia flagi do kontroli sygnału, szczegóły w linku. Na nasze potrzeby ustawiamy 0.
	https://www.gnu.org/software/libc/manual/html_node/Flags-for-Sigaction.html#Flags-for-Sigaction */
	int sa_flags
}
```
A teraz sama FUNKCJA sigaction
```c
int sigaction 
	(int signum, /* Sygnał, który chcemy przechwycić */
	 const struct sigaction *restrict action, /* wskaźnik na wyżej opisaną strukturę */
	 strict sigaction *restrict old-action) /* zwraca DOMYŚLNĄ strukturę obsługi sygnału, ustawiamy NULL */
```
Lista sygnałów do przechwycenia znajduje się [TUTAJ](https://man7.org/linux/man-pages/man7/signal.7.html).
Po tak zdefiniowanej strukturze sigaction oraz użytej funkcji `sigaction()`, należy przede wszystkim pamiętać, że napisaną przez nas funkcję do obsługi sygnału, deklarujemy w strukturze `sigaction` przekazując wskaźnik do funkcji pod element `sa_handler`.
## Gniazda
Gniazda to uogólniony kanał komunikacji międzyprocesorowej. Podobnie jak potok, gniazdo jest reprezentowane jako deskryptor pliku.
Gniazda obsługują komunikację między niepowiązanymi procesami, a nawet między procesami działającymi na różnych komputerach, które komunikuja się przez sieć.
Aby moć zastosować funkcje związane z gniazdami oraz stworzyć gniazdo, należy dołączyć w kodzie bibliotekę `<sys/socket.h>`

Gniazdo tworzymy funkcją `socket()`
```c
int socket (int namespace, /* PF_LOCAL (lokalna przestrzeń nazw) lub PF_INET (internetowa przestrzeń nazw) */
	    int style, /* rodzaj gniazda, na nasze potrzeby SOCK_STREAM */
	    int protocol) /* 0 oznacza domyślny protokół */
```
`socket()` zwraca deskryptor pliku do gniazda. Jeśli operacja się nie powiedzie to zwróci -1.

Gdy skończyłeś korzystać z gniazda, możesz go zamknąć funkcją `close()`.
Można ustanawiać pary gniazd za pomocą funkcji `socketpair()`. Ich działanie jest bardzo podobne do potoku i kolejki FIFO, z tą różnicą, że komunikacja jest dwukierunkowa.

Połączenie internetowe jest asymetryczne: jedna strona (klient) żąda połączenia, podczas gdy druga strona (serwer) tworzy gniazdo i czeka na żądanie połączenia.
### Po stronie serwera.
Nazwa gniazda to adres. Nowo stworzone gniazdo (przy pomocy funkcji `socket()`) nie ma adresu. Bez adresu inne procesy nie ustalą połączenia z gniazdem.

Adres gniazda w internetowej przestrzenii nazw składa się z adresu internetowego urządzenia oraz numeru portu, który rozróżnia gniazda dla danego urządzenia. Zakres portów to 16 bit (0 - 65535). 
Standardowe serwery mają zarezerwowany zakres portów, szczegóły dalej.

Aby użyć typów danych niezbędnych do zdefiniowania formatu adresu gniazda w internetowej przestrzenii nazw należy dołączyć bibliotekę `<netinet/in.h>` i użyć struktury, opisujących adres w zależności od protokołu
```c
struct sockaddr_in {
	sa_family_t sin_family /* format adresu, AF_INET */
	struct in_addr sin_addr /* adres IPv4 w formacie network byte order */
	unsigned short int sin_port /* numer portu w formacie network byte order */
}
```
Aby przekazać adres IPv4 jako network byte order można użyć funkcji
```c
int inet_aton (const char *name, struct in_addr *addr)
```
gdzie `name` to adres IPv4 jako łańcuch, a `addr` to wskaźnik na element struktury `sockaddr_in`.
Funkcja zwraca 0 jeśli adres nie jest poprawny.

Można poza tym do elementu `sin_addr` przekazać stałe takie jak:
- `INADDR_LOOPBACK` - localhost
- `INADDR_ANY` - dowolny adres przychodzący
- `INADDR_NONE` - głównie do obsługi błędów
- `INADDR_BROADCAST` - broadcast message

Aby przekazać numer portu w formacie network byte order należy użyć funkcji `htons(uint16_t)`.

Numery portów poniżej 1024 są zarezerwowane dla standardowych serverów takich jak *finger* i *telnet* i jedynie root ma do nich dostęp.
Numery portów równe i większe od 5000 to numery zarezerwowane dla serwerów i nie będą wykorzystywane automatycznie przez system.

Po tych wstępnych konfiguracjach należy przypisać gniazdu adres. Do tego służy funkcja `bind()`. 
```c
int bind (int socket, struct sockaddr *addr, socklen_t length)
```
Jeśli próba połączenia gniazda z adresem się nie powiedzie, funkcja zwróci wartość -1.

Następnie trzeba zrobić nasłuch na gniazdo po to, aby serwer mógł zaakceptować połączenie na gnieździe. Do tego służy funkcja `listen()`.
```c
int listen (int socket, int n) /* n określa długość kolejki nadchodzących połączeń, ustaw 5 */
```
Jeśli ustanowienie nasłuchu się nie powiedzie, funkcja zwróci wartość -1.

Następnie można zaakceptować nadchodzące połączenie funkcją `accept()`. `accept()` tworzy nowe gniazdo do komunikacji. Wówczas funkcja zwraca deskryptor do nowego gniazda, które stanowi część połączenia.
Natomiast pierwotne gniazdo służy do nasłuchu kolejnych, pozostałych połączeń.
```c
int accept (int socket, /* stare gniazdo nasłuchowe */
			struct sockaddr *addr, /* adres klienta */
			socklen_t *length_ptr) /* WSKAŹNIK na długość adresu klienta */
```  
Jeśl nastąpi błąd, funkcja zwróci -1.

Do przesyłania danych możesz użyć funkcji `send()` lub `write()`. `write()` nie ma argumentu flags.
```c
ssize_t send (int socket, const void *buffer, size_t size, int flags)
int write(int file_descriptor, char *buffer, int size)
```
Do odbierania danych służy `recv()` lub `read()` (poodobnie jak wyżej).
```c
ssize_t recv (int socket, void *buffer, size_t size, int flags)
int read(int file_descriptor, char *buffer, int size)
```
### Po stronie klienta
W pierwszej kolejności należy ustawić gniazdo po stronie klienta. Robi się to podobnie jak na serwerze. 
Następnie należy zdefiniować nazwy hosta dla serwera (w tym m.in. nazwy symboliczne, np. gnu.org).
Taką nazwę ustalamy u klienta (bo to on z niego korzysta) używając struktury `hostent` z biblioteki `<netdb.h>`.
```c
struct hostent {
	char *h_name; /* oficjalna nazwa hosta */
	char **h_aliases; /* lista nazw symbolicznych */
	int h_addrtype; /* typ adresu hosta, AF_INET */
	int h_length; /* długość adresu w bitach */
	char **h_addr_list; /* wskaźnik na listę adresów sieciowych, które kryją się za nazwą hosta */
};
```
Do tworzenia takiej struktury służy funkcja `gethostbyname()`, która zwraca wskaźnik do struktury `hostent`.
```c
struct hostent * gethostbyname (const char *name)
```
Potem definiujemy format adresu po stronie SERWERA i jego port (wykorzystując strukturę `sockaddr_in`). Robi się to tak samo jak na serwerze.

Następnie należy połączyć gniazdo klienta z adresem serwera używając connect().
```c
int connect (int socket, /* gniazdo po stronie klienta */
	     struct sockaddr *addr, /* adres serwera */
	     socklen_t length) /* długość adresu serwera */
```
Na końcu dokonujemy komunikacji z serwerem opierając się na funkcjach `read()` oraz `write()`. Deskryptor pliku dla obu funkcji to gniazdo klienta.
## W SKRÓCIE
Po stronie **klienta** należy:
1. Utworzyć gniazdo przy pomocy `socket()`
2. Połączyć gniazdo z adresem serwera używając `connect()`
3. Wysyłać i otrzymywać dane poprzez `write()` i `read()`

Po stronie **serwera** należy:
1. Utworzyć gniazdo przy pomocy `socket()`
2. Ustalić adres IPv4 dla serwera przy użyciu struktury `sockaddr_in`
3. Połączyć gniazdo z adresem używając `bind()`
4. Nasłuchiwać połączeń przy użyciu `listen()`
5. Akceptować połączenia przy użyciu `accept()`
6. Wysyłać i otrzymywać dane poprzez `write()` i `read()`
