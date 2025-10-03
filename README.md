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

-= TEMA 1 SDA =-

README: 5/5
01.When_NoPagesProviedAndPrintIsTheOnlyOperation_Should_PrintTab0.in: 5/5
  Valgrind PASSED
02.When_NoPagesProviedAnd3TabsOpen_Should_PrintTabs.in: 5/5
  Valgrind PASSED
03.When_NoPagesProviedAnd3TabsOpenAnd2TabsClosed_Should_PrintTabs.in: 2/2
  Valgrind PASSED
04.When_NoPagesProviedAnd1TabsOpenAnd2TabsClosed_Should_ReturnOnlyError.in: 2/2
  Valgrind PASSED
05.When_NoPagesProviedAnd1TabsOpenAnd2TabsClosedAndPrint_Should_ReturnErrorAnd
PrintDefaultTab.in: 3/3
  Valgrind PASSED
06.When_NoPagesProviedAnd2TabsOpenAnd1TabsClosedAndPrintAnd1TabsOpenAndPrint_
Should_PrintMultipleTimes.in: 3/3
  Valgrind PASSED
07.When_NoPagesProviedAnd2TabsOpenAndOpenAndPrint_Should_PrintInTheCorrect
Order.in: 2/2
  Valgrind PASSED
08.When_NoPagesProvieAndOpenTabThatDoesNotExists_Should_ReturnError.in: 3/3
  Valgrind PASSED
09.When_NoPagesProvieAndMultipleNewTabsAndOpenAndPrint_Should_PrintCorrect
Order.in: 3/3
  Valgrind PASSED
10.When_NoTabsAndNextAndPrint_Should_PrintTabs.in: 3/3
  Valgrind PASSED
11.When_NoTabsAndPrevAndPrint_Should_PrintTabs.in: 3/3
  Valgrind PASSED
12.When_NewTabsAndNextAndPrint_Should_PrintTabs.in: 3/3
  Valgrind PASSED
13.When_NewTabsAndPrevAndPrint_Should_PrintTabs.in: 3/3
  Valgrind PASSED
14.When_NewTabsAndPrevsAndNextsAndPrint_Should_PrintTabs.in: 2/2
  Valgrind PASSED
15.When_NewTabsAndClosesAndPrevsAndNextsAndPrint_Should_PrintTabs.in: 2/2
  Valgrind PASSED
16.When_NewTabsAndClosesAndOpensAndPrevsAndNextsAndPrint_Should_Print
Tabs.in: 2/2
  Valgrind PASSED
17.When_PagesAndNewTabsAndClosesAndOpensAndPrevsAndNextsAndPrints_Should_
PrintTabs.in: 3/3
  Valgrind PASSED
18.When_NoPagesProviedAndPage_Should_ReturnError.in: 2/2
  Valgrind PASSED
19.When_PagesAndPageThatDoesNotExists_Should_ReturnError.in: 2/2
  Valgrind PASSED
20.When_PagesAndPageAndPrint_Should_PrintCurrentPage.in: 2/2
  Valgrind PASSED
21.When_PagesAnd2NewTabsAndPageAndPrintAndPageAndPrint_Should_PrintMultiple
Times.in: 3/3
  Valgrind PASSED
22.PrintHistory_NoPages_Basic.in: 2/2
  Valgrind PASSED
23.PrintHistory_NoPages_Basic_Error.in: 2/2
  Valgrind PASSED
24.PrintHistory_Pages_Basic.in: 3/3
  Valgrind PASSED
25.Backward_NoPages_Basic_Error.in: 2/2
  Valgrind PASSED
26.Backward_Pages_Basic.in: 2/2
  Valgrind PASSED
27.Backward_Pages_Basic_Error.in: 3/3
  Valgrind PASSED
28.Forward_NoPages_Basic_Error.in: 2/2
  Valgrind PASSED
29.Forward_Pages_Basic.in: 2/2
  Valgrind PASSED
30.Forward_Pages_Basic_Error.in: 3/3
  Valgrind PASSED
31.ComplexTest.in: 2/2
  Valgrind PASSED
32.ComplexTest.in: 2/2
  Valgrind PASSED
33.ComplexTest.in: 2/2
  Valgrind PASSED
34.ComplexTest.in: 2/2
  Valgrind PASSED
35.ComplexTest.in: 2/2
  Valgrind PASSED
36.ComplexTest.in: 2/2
  Valgrind PASSED
37.ComplexTest.in: 2/2
  Valgrind PASSED
38.ComplexTest.in: 2/2
  Valgrind PASSED

Total: 100/100
Valgrind: 20/20