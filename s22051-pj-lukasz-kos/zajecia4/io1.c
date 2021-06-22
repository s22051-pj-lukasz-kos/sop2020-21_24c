#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char **argv) 
{
    FILE *f;
    int numbers_quantity;
    int *numbers_arr;
    int loop;
    char filename[64];

    if (argc == 2) {
        f = fopen(argv[1], "r");
    } else if (argc == 1) {
        printf("Proszę wpisać nazwę pliku\n");
        scanf("%s", filename);
        f = fopen(filename, "r");
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

    if (f != NULL) {
        fclose(f);
    }

    for (loop = numbers_quantity-1; loop >= 0; loop--) {
        printf("Dane w odwrotnej kolejności: %d\n", numbers_arr[loop]);
    }

    if (numbers_arr != NULL) {
        free(numbers_arr);
    }

    return 0;
}