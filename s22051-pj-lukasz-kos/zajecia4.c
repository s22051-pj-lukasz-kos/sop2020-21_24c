/*
Wstęp do C

Kompilacji programów dokonujemy poprzez polecenie: 
*/
gcc -Wall -pedantic -ansi kod.c -o kod
/*
gdzie:
gcc 		- kompilator GNU Compiler Collection
-Wall 	    - wyświetla dodatkowe ostrzeżenia dotyczące struktury kodu
-pedantic   - wyświetla ostrzeżenia wynikające ze standardu ISO C
-ansi 		- uściśla standard kodowania na ANSI C (C89)
-o 			- nazwa pliku wykonywalnego


Zadanie 1

Wprowadzając dane należy pamiętać, że scanf operuje na wskaźnikach, 
w przeciwieństwie do printf, który wykorzystuje wartości.

Do funkcji main można przekazać argumenty wiersza poleceń dzięki dwóm parametrom. 
*/
int main(int argc, char **argv) {}
/*
argc, od argument count, oznacza ilość argumentów, przekazanych do programu podczas wywołania.
**argv, od argument vector, to wskaźnik do tablicy ciągów znakowych, która zawiera przekazane argumenty.
Zamiast "char **argv" można napisać "char *argv[]".
argv[0] to nazwa programu, która została użyta do jego wywołania. 
Przekazane argumenty zaczynają się od indeksu 1.
Jeżeli argc==1, oznacza to, że nie przekazano żadnych argumentów wiersza poleceń

atoi to funkcja, która znajduje się w bibliotece stdlib.h. Konwertuje ciąg znaków na int. 
*/
int atoi(const char *s)
/*

Zadanie 2

Aby móc dokonywać operacji na plikach należy w pierwszej kolejności utworzyć do niego wskaźnik, 
na którym będą operować pozostałe funkcje z biblioteki stdio.h. 
Do tego celu służy funkcja fopen z tejże biblioteki.
fopen otwiera plik o podanej nazwie i zwraca stumień albo NULL, jeżeli operacja nie zakończy się powodzeniem.
*/
FILE *fp = fopen("plik.txt", 'r');
/* 
Pierwszy argument fopen to nazwa pliku. Drugi argument to tryb dostępu. Wyróżniamy:
r	do odczytu
w 	do zapisu, usuwa wcześniejszą zawartość
a	dołączanie danych; otwiera lub tworzy plik tekstowy do zapisu na końcu tego pliku
r+ 	otwiera plik tekstowy do aktualizacji, odczytywanie i zapisywanie
w+ 	zakłada plik tekstowy do aktualizacji, usuwa wcześniejszą zawartość
a+ 	dołączanie danych, otwiera lub tworzy plik tekstowy do aktualizacji i zapisywania na końcu tego pliku
Jeżeli tryb zawiera po pierwszej literze dodatkowo b, na przykład "rb" lub "w+b", sygnalizuje to plik binarny.

Do odczytu i zapisu pliku służą funkcje fscanf i fprintf, również zawarte w bibliotece stdio.h
Funkcja fscanf odczytuje dane ze strumienia. Odczytem kieruje ciąg znaków format. 
Wartości są przypisywane poszczególnym argumentom, które są wskaźnikami. 
fscanf zwraca EOF, jeżeli przed pierwszą konwersją wykryty zostanie koniec pliku lub wystąpi błąd.
*/
int fscanf(FILE *stream, const char *format, ...)
/* 
czyli po ludzku na przykład 
*/
int number;
fscanf(fp, "%d\n", &number);
/* 

Po skończonej pracy na pliku należy użyć funkcji 
*/
fclose(fp);
/* 
by zapisać buforowane dane, zwolnić alokowane bufory i zamknąć strumień (zwolnić wskaźnik). 
Ponieważ większość systemów operacyjnych nakłada pewne ograniczenie na liczbę plików 
jednocześnie otwieranych przez program, zwalnianie niepotrzebnych wskaźników pliku należy do dobrej praktyki. 
*/
strcmp(s,t) /* porównuje ciąg znaków pod kątem alfabetycznym i zwraca wartość ujemną, zero lub 
dodatnią dla s<t, s==t lub s>t. Funkcja znajduje się w bibliotece string.h */

printf(const char *format, ...) /* drukuje format na standardowe wyjście. */
scanf(const char *format, ...) /* przechwytuje dane ze standardowego wejścia. 
    Aby wprowadzić ciąg znaków to trzeba się odwołać do tablicy o określonym rozmiarze, 
    bowiem odwołanie do wskaźnika nie zapisze żadnej wartości, np. 
*/
char str[32];
scanf("%s", str);
/* 

Do zapisu i odczytu pliku binarnego można wykorzystać funkcje fprint oraz fwrite. 
W przypadku fread zapisujemy strumień 'stream' do tablicy 'ptr' 
co najwyżej 'nobj' obiektów o rozmiarze 'size'. Funkcja zwraca liczbę odczytanych obiektów. 
*/
size_t fread(void *ptr, size_t size, size_t nobj, FILE *stream)
/* czyli np. */
FILE *frb;
int i;
 fread(&i, sizeof(int), 1, frb);
/*
Podobnie będzie w przypadku fwrite, z tą różnicą, że z tablicy ptr zapisujemy do pliku 
*/
 fwrite(&i, sizeof(int), 1, frb);
/* 
Aby utworzyć tablicę dynamiczną, to należy dla niej ulokować zakres pamięci. 
Do tego celu służy funkcja malloc z biblioteki stdlib.h Funkcja ta zwraca wskaźnik do obszaru pamięci 
pozwalającego przechowywać obiekt o rozmiarze size (lub NULL, jeżeli żądanie nie może zostać zrealizowane).
Zawartość nie jest inicjalizowana. np. 
*/
int *buffer;
 buffer = (int *) malloc(numbers_quantity * sizeof(int));
/* 
Obszar pamięci zarezerwowany tą funkcją jest blokowany przed dostępem, więc przed zakończeniem programu 
należy ten wskaźnik zwolnić funkcją 'free'
*/
free(buffer);
/*
Typ bool (boolean, logiczny) nie występuje w standardzie C89, dlatego należy go dołączyć 
dodatkową biblioteką stdbool.h. 


Zadanie 3
Jako jeden z argumentów funkcji możemy przekazać wskaźnik do innej funkcji (np. w celu uzyskania 
zwracanej wartości od tej funkcji). 
Taką funkcję,  wykorzystującą wskaźnik do innej funkcji, deklarujemy np. tak:
*/
int forAll(int jakis_argument, int (*f)(int, int));

/*
Można również tworzyć tablice wskaźników do funkcji. Załóżmy, że mamy funkcję:
*/
int suma(int pierwsza, int druga);
/*
Wówczas tablica ze wskaźnikiem oraz jej definicja będzie wyglądać tak:
*/
int (*funkcje[3])(int, int);
funkcje[0] = suma;
