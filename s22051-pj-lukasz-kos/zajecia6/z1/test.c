#include <stdio.h>
#include <netinet/in.h>

int main() {
    printf("Porty zarezerwowane: %d\nPorty użytkownika: %d\n", IPPORT_RESERVED, IPPORT_USERRESERVED);
    return 0;
}