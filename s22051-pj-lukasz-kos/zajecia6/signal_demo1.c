/* Program przechwytuje sygnał przerwania SIGINT, 
    wyświetla komunikat i pozwala na dalsze działanie 
    Obsługa sygnałów poprzez sigaction nie jest standardem ANSI C. 
    Dlatego najpierw zdefiniowałem makro, które zaimplementuje standard POSIX.1, 
    który umożliwi mi na taką obsługę */
#define _POSIX_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void install_handler(void);
void catch_sigint(int);

int main() {
    char x = '1'; 
    /* umieszcza handler sygnału na samym początku programu */
    install_handler();

    while (x != '0') {
        fflush(stdout);
        printf("Podaj 0 by zakończyć: ");
        x = getchar();
    }
    return 0;
}

/* Funkcja określająca działanie w przypadku przechwycenia określonego sygnału.
    Nazwa dowolna */
void catch_sigint(int signum) {
    install_handler();
    printf("Handler triggered. s = %d\n", signum);
}

/* Zdefiniowanie handlera pod sygnał. Nie trzeba tworzyć osobnej funkcji, 
    można to wszystko umieścić na początku bloku main()
    Nazwa dowolna */
void install_handler(void) {
    /* Struktura z biblioteki <signal.h> do ustalenia procedury obsługi sygnału. 
        Poszczególne jej elementy są definiowane dalej */
    struct sigaction setup_action;
    
    /* Typ sigset_t pochodzi z <signal.h> */
    sigset_t block_mask;
    
    /* Funkcja z biblioteki <signal.h> do generowania pustego zbióru sygnałów, 
        który wykorzystamy w strukturze sigaction do zdefiniowania sa_mask */
    sigemptyset(&block_mask);

    /* Tutaj ustawiasz nowe procedury obsługi sygnału. Domyślne to: 
        SIG_DFL (signal default, domyślna obsługa), 
        SIG_IGN (ignorowanie sygnału).
		Można również ustawic wskaźnik na własną funkcję, która zadziała 
        w przypadku przechwycenia sygnału. */
    setup_action.sa_handler = &catch_sigint;

    /* Zbiór sygnałów, które będą przechwytywane PONAD TO co zdefiniujemy w funkcji sigaction. 
        Stąd nazwa maska.
		Jako, że chcemy przechwycić tylko jeden sygnał, to ta maska może pozostać pusta. 
		Puste maski generuje się funkcją int sigemptyset(sigset_t *set). */
    setup_action.sa_mask = block_mask;

    /* Ustanawia flagi do kontroli sygnału, szczegóły w linku. 
        https://www.gnu.org/software/libc/manual/html_node/Flags-for-Sigaction.html#Flags-for-Sigaction
        Na nasze potrzeby ustawiamy 0. */
    setup_action.sa_flags = 0;

    /* Właściwa funkcja z biblioteki <signal.h> do obsługi przechwyconego sygnału 
        int sigaction (int signum, const struct sigaction *restrict action, strict sigaction *restrict old-action)
        signum - określa sygnał, który chcemy przechwycić. Lista sygnałów pod linkiem
            https://man7.org/linux/man-pages/man7/signal.7.html
        action - struktura, w której zdefiniowaliśmy nowe procedury obsługi sygnału, maskę i flagi
        old-action - zwraca DOMYŚLNĄ strukturę obsługi sygnału. 
            Nie potrzebujemy tego więc ustawiamy NULL.
        */
    sigaction(SIGINT, &setup_action, NULL);
}