#include <stdlib.h>
#include <stdio.h>

int forAll(int *tab, int ilosc, int (*f)(int, int));
int minimum (int v, int next);
int maksimum (int v, int next);
int suma (int v, int next);

int main(int argc, char *argv[]){
    int z;
    int n;
    int i;
    int *tab;
    int wynik;
    int (*funkcje[3])(int, int);
    funkcje[0] = suma;
    funkcje[1] = minimum;
    funkcje[2] = maksimum;

    printf("wpisz ile chcesz wprowadzić liczb.\n");
    scanf("%d", &n);

    /* alokuję pamięć pod tablicę */
    tab = (int*) malloc(n * sizeof(int));

    printf("Wpisz poszczególne liczby:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &tab[i]);
    }

    printf("Co chcesz zrobić?\n1. Znajdź minimum\n2. Znajdź maksimum\n0. Oblicz sumę\n");
    scanf("%d",&z);

    wynik = forAll(tab, n, funkcje[z]);
    
    printf("Wynik wynosi: %d\n", wynik);

    /* zwolnienie alokowanego bloku */
    free(tab);

    return 0;
}

int forAll(int *tab, int ilosc, int (*f)(int, int)) {
    int v = tab[0];
    int i;

    for(i = 1; i < ilosc; i++) {
        v = f(v, tab[i]);
    } 
    return v;
}

int minimum (int v, int next) {
    if(v>next) {
        v = next;
    }
    return v;
}

int maksimum (int v, int next) {
    if(v<next) {
        v = next;
    }
    return v;
}

int suma (int v, int next) {
    return (v+next);
}