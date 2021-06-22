#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc == 2) {
        int i, j;
        /* atoi konwertuje ciąg znaków na integer */
        int ilosc_wierszy = atoi(argv[1]);
        printf("Wiersze: %d\n", ilosc_wierszy); 
        for(i = 1; i <= ilosc_wierszy; i++) {
            for (j = 0; j < ilosc_wierszy - i; j++) {
                printf(" ");
            }
            for (j = 0; j < i*2-1 ; j++) {
                printf("*");
            }
            printf("\n");    
        }
    }
    return 0;
}
