Lupsa Alexandra-Cristina - 312CC

Explicarea codului:

	Voi explica mai intai ce face fiecare functie in parte, apoi modul in care
se leaga cu main-ul. Am denumit structurile cu typedef pentru a avea o structura
similara cu cele de la laborator dar am pastrat aceleasi variabile sub aceeasi
forma in modul in care erau prezentate in enunt.
	Functia initDL initializeaza lista dublu inlantuita cu santinela, respectiv
browserul cu primul tab avand id-ul 0, tab care la randul lui se deschide
totodata cu prima pagina, cea implicita.
	Functia NEW_TAB deschide un nou tab care primeste la randul lui pagina
implicita, tab-urile au un ID unic care creste la fiecare apelare a functiei in
main. Variabila id_increment se ocupa de cresterea id-ului la fiecare apel al
functiei.
	Imediat dupa se afla functiile aferente stivelor, push, pop si isEmptyStack
care ajuta la adaugarea si scoaterea paginilor.
	Functia CLOSE cauta tab-ul curent si il elimina, noul tab curent devenind
cel din stanga sa. La finalul functiei, elimin toata memoria alocata dinamic
atat din cele doua stive ce administreaza paginile din tab, cat si din tab.
	Functia OPEN_ID deschide tab-ul cu id-ul respectiv, verificand mai intai
daca id-ul este mai mare decat id-ul maxim. Daca se intampla acest lucru, se
afiseaza mesajul de eroare. In caz contrar, cautam tab-ul in lista si daca
ajungem la nodul santinela, inseamna ca nu exista si afisam mesajul de eroare.
	Functiile NEXT si PREV se muta in tab-ul urmator, respectiv cel precedent
tab-ului curent.
	Functiile FORWARD si BACKWARD afiseaza ultima pagina din stiva respectiva.
Se apeleaza functia isEmptyStack, iar in cazul in care stiva este goala se
afiseaza mesajul de eroare.
	Functia PAGE_ID deschide pagina cu anumit id. La inceputul main-ului, am
folosit functia salvare_fisier, care imi salveaza linie cu linie fisierul si
adauga fiecare linie alocata dinamic cu strdup in vectorul de cuvinte operatii.
Variabila comenzi memoreaza numarul de linii al fisierului. Astfel, la
for-ul din main care reia liniile fisierului de intrare, prima linie reprezinta
numarul de pagini, reprezentat sub variabila nr_pag. La apelul functiei PAGE_ID
daca nr_pag este 0, se va afisa mesajul de eroare. In caz contrar, se va intra
in functia citire_elemente_pagina, care cauta linia la care se afla pagina cu
id-ul respectiv. In cazul in care acesta nu exista, se afiseaza mesajul de
eroare. In caz contrar, functia citire_elemente_pagina returneaza descrierea
alocata dinamic. Revenind in main, in cazul in care a fost gasit id-ul si
descrierea nu este NULL, se deschide prin PAGE_ID pagina cu id-ul respectiv in
tab-ul curent.
	Functia PRINT afiseaza atat tab-urile incepand de la cel curent, cat si
descrierea paginii curente aferente tab-ului curent.
	In main, atunci cand se apeleaza PRINT HISTORY ID, mai intai se verifica
prin variabila eroare daca tab-ul cu id-ul respectiv exista, in caz contrar
functia va afisa mesajul de eroare. Altfel, se vor afisa url-urile din stiva
Forward, din pagina curenta si ulterior din stiva Backward.
	La finalul prelucrarii intregului fisier de intrare prin for-ul din main,
se elibereaza memoria alocata dinamic a fiecarei linii din vectorul operatii,
iar apoi prin functia free_valgrind se goleste lista dublu inlantuita, lista a
carui nod contine fiecare cele doua stive si pagina curenta, cu descriere, toate
fiind golite la randul lor prin intermediul acestei functii.
37.ComplexTest.in: 2/2
  Valgrind PASSED
38.ComplexTest.in: 2/2
  Valgrind PASSED

Total: 100/100
Valgrind: 20/20
