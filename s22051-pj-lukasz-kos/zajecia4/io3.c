/* zadanie 2 IO 2 oraz 3 */
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    FILE *f;
    FILE *fwb;
    FILE *frb;
    int numbers_quantity;
    int *numbers_arr;
    int loop;
    char filename[64];
    char *fname;
    bool flag = false;
    int *bin_buffer;

    /* obsługa algorytmów */
    if (argc == 1) {
        printf("Proszę wpisać nazwę pliku\n");
        scanf("%32s", filename);
        f = fopen(filename, "r"); 
    } else {
        for (loop = 1; loop < argc; loop++) {
            int out = strcmp(argv[loop], "--print");
            if(out == 0) {
                flag = true;
            } else {
                fname = argv[loop];
                f = fopen(fname, "r");
            }
        }
    } 

    if(f == NULL) {
        printf("Plik nie istnieje\n");
        return 1;
    }

    fscanf(f, "%d\n", &numbers_quantity);
    /* alokacja pamięci dla tablicy */
    numbers_arr = (int *) malloc(numbers_quantity * sizeof(numbers_quantity));
    
    /* fscanf traktuje plik jako strumień, który przeszukuje względem wzorca format 
       do momentu napotkania EOF */
    for (loop = 0; loop < numbers_quantity; loop++) {
        int number;
        fscanf(f, "%d\n", &number);
        numbers_arr[loop] = number;
        printf("Dane w pliku: %d\n", numbers_arr[loop]);
    }

    /* zamknięcie strumienia do odczytu pliku */
    if (f != NULL) {
        fclose(f);
    }

    /* strumień zapisu do pliku binarnego */
    fwb = fopen("io2.bin", "wb");
    /* strumień odczytu z pliku binarnego */
    frb = fopen("io2.bin", "rb");

    /* zapis do pliku binarnego w odwrotnej kolejności */
    for (loop = numbers_quantity-1; loop >= 0; loop--) {
        fwrite(&numbers_arr[loop], sizeof(*numbers_arr), 1, fwb);
    }

    /* zamykanie strumienia zapisu pliku binarnego */
    if (fwb != NULL) {
        fclose(fwb);
    }

    /* odczyt z pliku binarnego */
    if(flag) {
        printf("Dane z pliku binarnego (w odwrotnej kolejności):\n");
        bin_buffer = (int *) malloc(numbers_quantity * sizeof(int));

        /*fread(bin_buffer, sizeof(bin_buffer), 1, frb);*/
        for (loop = 0; loop < sizeof(bin_buffer); loop++) {
            fread(&bin_buffer[loop], sizeof(*bin_buffer), 1, frb);
            printf("%x\n", bin_buffer[loop]);
        } 
    }

    /* zamykanie strumienia odczytu pliku binarnego */
    if (frb != NULL) {
        fclose(frb);
    }
    /* zwalnianie pamięci alokowanej pod tablice */
    if (numbers_arr != NULL) {
        free(numbers_arr);
    }
    if (bin_buffer != NULL) {
        free(bin_buffer);
    }

    return 0;
}