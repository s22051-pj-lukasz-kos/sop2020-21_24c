#include <stdio.h>

int main() 
{
    int suma = 0;
    int input = 0;

    /* funkcja scanf działa na wskaźnikach
       w przeciwieństwie do printf, który wykorzystuje wartości */
    while(scanf("%d\n", &input) > 0) { 
        suma += input;
    }
    printf("%d\n", suma);

    return suma;
}
