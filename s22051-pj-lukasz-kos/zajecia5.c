/* 
Zajęcia 5

Każdy proces zwaraca swój numer - PID (process id) oraz PPID (parent process id). Umożliwia to tworzenie całych "drzewek" 
zależnych od siebie procesów.
Do uzyskania tych numerów można wykorzystać funkcje getpid() oraz getppid().  Aby je wywołać w kodzie należy dołączyć biblioteki 
<sys/types.h> oraz <unistd.h>
Istnieje również PGID(process group id), który identyfikuje grupę procesów. Z reguły proces macierzysty ma PGID równy swojemu PID, 
a proces potomny ma PGID równy PID procesu macierzystego.

fork() to funkcja w systemach uniksopodobnych, która "rozwidla" (fork) proces, który ją wywołał. Tworzona jest kopia procesu, 
określana jako proces potomny (child process, proces-dziecko, dziecko, potomek). Proces, który wywołał fork() to proces macierzysty 
(parent process, proces-rodzic, rodzic, proces pierwotny). 
PID dziecka jest unikatowy. PPID dziecka wskazuje na rodzica. 
Aby móc wywołać fork() w kodzie c należy dołączyć bibilotekę <unistd.h>

fork() zwraca poszczególne wartości:
-1 					jeśli nie udało się utorzyć procesu potomnego
0 					wysyłane do procesu potomnego
liczba całkowita 	wysyłana do procesu macierzystego, ta liczba to numer PID procesu potomnego


waitpid() to funkcja, która wstrzymuje wykonanie kodu do momentu, aż proces, którego PID lub PGID został ustalony poprzez argument, 
zmieni stan. 
Do zmiany stanu należą:
* zakończenie procesu
* zatrzymanie procesu poprzez sygnał
* wznowienie procesu poprzez sygnał
Aby użyć tej funkcji należy dołączyć biblioteki <sys/types.h> oraz <sys/wait.h>
*/
pid_t waitpid(pid_t pid, int *status, int options);
/* to po ludzku, np. */ 
waitpid(0, NULL, 0);
/*
W pid podajemy jaki proces potomny ma być targetowany:
< -1
czekaj na proces potomny, którego PGID jest równy wartości absolutnej pid
-1 
czekaj na jakikolwiek proces potomny
0
czekaj na proces potomny, którego PGID jest równy PGID wywołującego procesu
>0
czekaj na proces potomny, którego PID jest równy podanej wartosci pid

*status to wskaźnik do zwracanej wartości int, oznaczającej status. Aby zobaczyć co się za nią kryje, musisz dołączyć odpowiednie makra. 
Po szczegóły zajrzyj do manuala.
Jeśli nie interesują cię zwracane wartości to możesz wpisać NULL.

options to alternatywa stałych określających działanie funkcji. Szczegóły w manualu. Brak opcji oznaczamy 0.

Pochodną funkcją do waitpid() jest wait(). Ta ostatnia to inaczej: 
*/
waitpid(-1, &status, 0);
/*
czyli wait() wstrzymuje proces do czasu zmiany stanu przez dowolny proces potomny.
Można też zamiast odwołania do zmiennej status wpisać NULL i uzyskać, np.
*/
wait(NULL);