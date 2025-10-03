#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct page {
	int id;
	char url[50];
	char *description;
} Page, *TPage;

typedef struct stack {
	TPage page;
	struct stack *next;
} Stack, *TStack;

typedef struct tab {
	int id;
	struct page *currentPage;
	struct stack *backwardStack;
	struct stack *forwardStack;
} BTab, *Tab;

typedef struct tabsList {
	Tab tab;
	struct tabsList *next;
	struct tabsList *prev;
} tabsList, *TabsList;

typedef struct browser {
	struct tab *current;
	struct tabsList list;
} TBrowser, *Browser;

Browser initDL(Browser browser, FILE *f_out)
{
	// crearea listei dublu inlantuita cu santinela
	Tab implicit_tab;
	implicit_tab = (Tab)malloc(sizeof(BTab));
	if (implicit_tab == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		exit(1);
	}
	implicit_tab->id = 0;
	implicit_tab->backwardStack = implicit_tab->forwardStack = NULL;
	implicit_tab->currentPage = (TPage)malloc(sizeof(Page));
	if (implicit_tab->currentPage == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		exit(1);
	}
	implicit_tab->currentPage->id = 0;
	strcpy(implicit_tab->currentPage->url, "https://acs.pub.ro/");
	int lenght = strlen("Computer Science");
	implicit_tab->currentPage->description = (char *)malloc((lenght + 2) *
	sizeof(char));
	strcpy(implicit_tab->currentPage->description, "Computer Science\n");
	browser->list.prev = browser->list.next = &browser->list;
	TabsList node;
	node = (TabsList)malloc(sizeof(tabsList));
	if (node == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		exit(1);
	}
	node->tab = implicit_tab;
	node->next = node->prev = &browser->list;
	browser->list.next = browser->list.prev = node;
	browser->current = implicit_tab;
	return browser;
}

Browser NEW_TAB(Browser browser, int id_increment, FILE *f_out)
{
	Tab new_tab;
	new_tab = (Tab)malloc(sizeof(BTab));
	if (new_tab == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		exit(1);
	}
	TabsList node;
	node = (TabsList)malloc(sizeof(tabsList));
	if (node == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		exit(1);
	}
	new_tab->id = id_increment;
	// noul tab primeste id-ul preluat din main, id-ul fiind unic
	new_tab->backwardStack = new_tab->forwardStack = NULL;
	new_tab->currentPage = (TPage)malloc(sizeof(Page));
	if (new_tab->currentPage == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		free(new_tab->currentPage);
		exit(1);
	}
	new_tab->currentPage->id = 0;
	strcpy(new_tab->currentPage->url, "https://acs.pub.ro/");
	int lenght = strlen("Computer Science");
	new_tab->currentPage->description = (char *)malloc((lenght + 2) *
	sizeof(char));
	// alocam dinamic descrierea paginii
	strcpy(new_tab->currentPage->description, "Computer Science\n");
	node->tab = new_tab;
	node->next = &browser->list;
	node->prev = browser->list.prev;
	browser->list.prev->next = node;
	browser->list.prev = node;
	browser->current = new_tab;
	return browser;
}

int isEmptyStack(TStack stack)
{
	// verificam daca stiva este goala cu ajutorul acestei functii
	return stack == NULL;
}

TStack push(TStack stack, TPage new_page, FILE *f_out)
{
	// introducem o noua pagina in stive
	TStack stiva;
	stiva = (TStack)malloc(sizeof(Stack));
	if (stiva == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		return NULL;
	}
	stiva->page = new_page;
	stiva->next = stack;
	return stiva;
}

TStack pop(TStack stack)
{
	// scoatem o pagina din stiva
	TStack stiva;
	stiva = stack;
	stack = stack->next;
	free(stiva);
	return stack;
}

Browser CLOSE(Browser browser, FILE *f_out)
{
	// tab-ul cu id=0 nu se poate inchide niciodata
	if (browser->current->id == 0) {
		fprintf(f_out, "403 Forbidden\n");
	} else {
		TabsList tab = browser->list.next;
		while (tab->tab != browser->current && tab != &browser->list)
		{
			tab = tab->next;
		}
		tab->prev->next = tab->next;
		tab->next->prev = tab->prev;
		browser->current = tab->prev->tab;
		// eliberarea memoriei alocate cu malloc de catre tab-ul respectiv
		// se elibereaza tot ce tine atat de tab, cat si de continutul lui
		TStack stack = tab->tab->backwardStack;
		TPage next_page;
		while (!isEmptyStack(stack)) {
			next_page = stack->page;
			if (next_page != NULL) {
				free(next_page->description);
				free(next_page);
			}
			TStack stiva = stack;
			stack = stack->next;
			free(stiva);
		}
		stack = tab->tab->forwardStack;
		while (!isEmptyStack(stack)) {
			next_page = stack->page;
			if (next_page != NULL) {
				free(next_page->description);
				free(next_page);
			}
			TStack stiva = stack;
			stack = stack->next;
			free(stiva);
		}
		free(tab->tab->currentPage->description);
		free(tab->tab->currentPage);
		free(tab->tab);
		free(tab);
	}
	return browser;
}

Browser OPEN_ID(Browser browser, int id, int id_maxim, FILE *f_out)
{
	// daca id-ul este mai mare decat ultimul id creat vreodata, se afiseaza
	// mesajul de eroare
	if (id > id_maxim) {
		fprintf(f_out, "403 Forbidden\n");
	} else {
		TabsList tab = browser->list.next;
		while (tab != &browser->list && id != tab->tab->id) {
			tab = tab->next;
		}
		if (tab == &browser->list) {
			// asta se intampla in cazul in care tab-ul a fost sters din lista
			fprintf(f_out, "403 Forbidden\n");
		} else {
			browser->current = tab->tab;
		}
	}
	return browser;
}

Browser NEXT(Browser browser)
{
	// cautam sa ajungem la tab-ul curent
	TabsList tab = browser->list.next;
	while (tab != &browser->list) {
		if (tab->tab == browser->current) {
			break;
		}
		tab = tab->next;
	}
	// trecem apoi la urmatorul tab
	if (tab->next == &browser->list) {
		browser->current = browser->list.next->tab;
		return browser;
	}
	tab = tab->next;
	browser->current = tab->tab;
	return browser;
}

Browser PREV(Browser browser)
{
	// cautam sa ajungem la tab-ul curent
	TabsList tab = browser->list.next;
	while (tab != &browser->list) {
		if (tab->tab == browser->current) {
			break;
		}
		tab = tab->next;
	}
	// trecem apoi la tab-ul anterior
	if (tab->prev == &browser->list) {
		browser->current = browser->list.prev->tab;
		return browser;
	}
	tab = tab->prev;
	browser->current = tab->tab;
	return browser;
}

Browser BACKWARD(Browser browser, FILE *f_out)
{
	TStack stack = browser->current->backwardStack;
	Tab tab = browser->current;
	// daca stiva Backward este goala, se afiseaza mesajul de eroare
	if (isEmptyStack(stack)) {
		fprintf(f_out, "403 Forbidden\n");
		return browser;
	} else {
		// se acceseaza ultima pagina din stiva iar cea curenta se muta
		// in stiva Forward
		tab->forwardStack = push(tab->forwardStack, tab->currentPage, f_out);
		tab->currentPage = tab->backwardStack->page;
		tab->backwardStack = pop(tab->backwardStack);
	}
	return browser;
}

Browser FORWARD(Browser browser, FILE *f_out)
{
	TStack stack = browser->current->forwardStack;
	Tab tab = browser->current;
	// daca stiva Forward este goala, se afiseaza mesajul de eroare
	if (isEmptyStack(stack)) {
		fprintf(f_out, "403 Forbidden\n");
		return browser;
	} else {
		// se acceseaza ultima pagina din stiva iar cea curenta se muta
		// in stiva Backward
		tab->backwardStack = push(tab->backwardStack, tab->currentPage, f_out);
		tab->currentPage = tab->forwardStack->page;
		tab->forwardStack = pop(tab->forwardStack);
	}
	return browser;
}

Browser PAGE_ID(Browser browser, int id, char *url, char *description,
	FILE *f_out)
{
	Tab tab = browser->current;
	// se goleste stiva Forward
	while (!isEmptyStack(tab->forwardStack)) {
		free(tab->forwardStack->page->description);
		free(tab->forwardStack->page);
		tab->forwardStack = pop(tab->forwardStack);
	}
	// pagina curenta se adauga in stiva Backward
	tab->backwardStack = push(tab->backwardStack, tab->currentPage, f_out);
	tab->currentPage = (TPage)malloc(sizeof(Page));
	if (tab->currentPage == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		exit(1);
	}
	// se atribuie datele pentru noua pagina curenta
	tab->currentPage->id = id;
	strcpy(tab->currentPage->url, url);
	tab->currentPage->description = description;
	return browser;
}

void PRINT(Browser browser, FILE *f_out)
{
	TabsList tab = browser->list.next;
	// se cauta a se ajunge la tab-ul curent
	while (tab != &browser->list && tab->tab != browser->current) {
		tab = tab->next;
	}
	TabsList current = tab;
	// acesta se afiseaza primul
	fprintf(f_out, "%d", tab->tab->id);
	tab = tab->next;
	if (tab == &browser->list) {
		tab = tab->next;
	}
	// urmeaza afisarea tuturor tab-urilor ce urmeaza pana se ajunge iar la cel
	// curent
	while (tab != &browser->list && tab->tab != current->tab) {
		fprintf(f_out, " %d", tab->tab->id);
		tab = tab->next;
		if (tab == &browser->list) {
			tab = tab->next;
		}
	}
	fprintf(f_out, "\n");
	// se afiseaza descrierea paginii curente
	fprintf(f_out, "%s", browser->current->currentPage->description);
}

void PRINT_HISTORY_ID(Browser browser, FILE *f_out, int id, int eroare)
{
	// daca tab-ul nu exista, se afiseaza mesajul de eroare
	if (eroare == 1) {
		fprintf(f_out, "403 Forbidden\n");
	} else {
		TabsList tabs = browser->list.next;
		while (tabs != &browser->list && id != tabs->tab->id) {
			tabs = tabs->next;
		}
		// daca se cauta tab-ul si nu se gaseste, se afiseaza mesajul de eroare
		if (tabs == &browser->list) {
			fprintf(f_out, "403 Forbidden\n");
			return;
		}
		Tab tab = tabs->tab;
		TStack new_forward = NULL;
		TStack new_backward = NULL;
		TStack parcurgere;
		parcurgere = tab->forwardStack;
		while (parcurgere != NULL) {
			new_forward = push(new_forward, parcurgere->page, f_out);
			parcurgere = parcurgere->next;
		}
		// se afiseaza url-urile aferente stivei Forward, de la prima pagina
		// adaugata
		while (new_forward != NULL) {
			fprintf(f_out, "%s\n", new_forward->page->url);
			new_forward = new_forward->next;
		}
		// se afisaza url-ul paginii curente
		fprintf(f_out, "%s\n", tab->currentPage->url);
		new_backward = tab->backwardStack;
		// se afiseaza url-urile aferente stivei Backward, de la ultima pagina
		// adaugata
		while (new_backward != NULL) {
			fprintf(f_out, "%s\n", new_backward->page->url);
			new_backward = new_backward->next;
		}
	}
}

void salvare_fisier(FILE *f, char *operatie[500], int *comenzi)
{
	// salvam fiecare linie a fisierului in aceasta functie
	char input[200];
	while (fgets(input, 200, f)) {
		for (int i = 0; input[i] != '\0'; i++) {
			if (input[i] == '\n') {
				input[i] = '\0';
				break;
			}
		}
		operatie[*comenzi] = strdup(input);
		(*comenzi)++;
	}
}

char *citire_elemente_pagina(char *operatie[500], int comenzi, int id,
	char *url, FILE *f_out)
{
	// in aceasta functie se cauta si se returneaza descrierea sau NULL
	int line_url, line_descriere, index = 0;
	for (int i = 0; i < comenzi; i++) {
		if (atoi(operatie[i]) == id) {
			line_url = i + 1;
			line_descriere = i + 2;
			index = 1;
		}
	}
	if (index == 0) {
		fprintf(f_out, "403 Forbidden\n");
		return NULL;
	} else {
		strcpy(url, operatie[line_url]);
		int lenght = strlen(operatie[line_descriere]);
		char *description = (char *)malloc((lenght + 2) * sizeof(char));
		if (description == NULL) {
			fprintf(f_out, "Eroare la alocarea memoriei!");
			exit(1);
		}
		strcpy(description, operatie[line_descriere]);
		// adaugam '\n' la finalul descrierii
		description[lenght] = '\n';
		description[lenght + 1] = '\0';
		return description;
	}
}

Browser free_valgrind(Browser browser)
{
	// se elimina toata memoria alocata dinamic cu malloc in aceasta functie
	TabsList tabs = browser->list.next;
	TabsList next_node;
	while (tabs != &browser->list) {
		next_node = tabs->next;
		TStack stack = tabs->tab->backwardStack;
		TPage next_page;
		while (!isEmptyStack(stack)) {
			next_page = stack->page;
			if (next_page != NULL) {
				free(next_page->description);
				free(next_page);
			}
			TStack stiva = stack;
			stack = stack->next;
			free(stiva);
		}
		stack = tabs->tab->forwardStack;
		while (!isEmptyStack(stack)) {
			next_page = stack->page;
			if (next_page != NULL) {
				free(next_page->description);
				free(next_page);
			}
			TStack stiva = stack;
			stack = stack->next;
			free(stiva);
		}
		free(tabs->tab->currentPage->description);
		free(tabs->tab->currentPage);
		free(tabs->tab);
		free(tabs);
		tabs = next_node;
	}
	browser->list.next = &browser->list;
	browser->list.prev = &browser->list;
	return browser;
}

int main()
{
	FILE *f = fopen("tema1.in", "r");
	FILE *f_out = fopen("tema1.out", "w");
	char *operatie[500], url[50];
	int comenzi = 0, id_increment = 0, nr_pag, open, page, eroare = 0;
	// apelarea functiei care salveaza linie cu linie fisierul tema1.in
	salvare_fisier(f, operatie, &comenzi);
	Browser browser = (Browser)malloc(sizeof(TBrowser));
	if (browser == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		exit(1);
	}
	browser = initDL(browser, f_out);
	// reluarea linie cu linie a fisierului de intrare salvat in operatii
	for (int i = 0; i < comenzi; i++) {
		nr_pag = atoi(operatie[0]);
		if (strcmp(operatie[i], "NEW_TAB") == 0) {
			id_increment++;
			// id_increment face ca fiecare tab sa primeasca un id unic
			browser = NEW_TAB(browser, id_increment, f_out);
		}
		if (strcmp(operatie[i], "CLOSE") == 0) {
			browser = CLOSE(browser, f_out);
		}
		if (strcmp(operatie[i], "PRINT") == 0) {
			PRINT(browser, f_out);
		}
		if (operatie[i][0] == 'O' && operatie[i][1] == 'P' &&
			operatie[i][2] == 'E' && operatie[i][3] == 'N') {
			open = atoi(operatie[i] + 5);
			browser = OPEN_ID(browser, open, id_increment, f_out);
		}
		if (strcmp(operatie[i], "NEXT") == 0) {
			browser = NEXT(browser);
		}
		if (strcmp(operatie[i], "PREV") == 0) {
			browser = PREV(browser);
		}
		if (operatie[i][0] == 'P' && operatie[i][1] == 'A' &&
			operatie[i][2] == 'G' && operatie[i][3] == 'E') {
			page = atoi(operatie[i] + 5);
			if (nr_pag == 0) {
				fprintf(f_out, "403 Forbidden\n");
			} else {
				char *description = citire_elemente_pagina(operatie,
					comenzi, page, url, f_out);
				if (description != NULL) {
					browser = PAGE_ID(browser, page, url, description, f_out);
				}
			}
		}
		if (operatie[i][0] == 'P' && operatie[i][1] == 'R' &&
			operatie[i][2] == 'I' && operatie[i][3] == 'N' &&
			operatie[i][4] == 'T' && operatie[i][5] == '_') {
			open = atoi(operatie[i] + 14);
			eroare = 0;
			if (open > id_increment) {
				eroare = 1;
			}
			PRINT_HISTORY_ID(browser, f_out, open, eroare);
		}
		if (strcmp(operatie[i], "BACKWARD") == 0) {
			browser = BACKWARD(browser, f_out);
		}
		if (strcmp(operatie[i], "FORWARD") == 0) {
			browser = FORWARD(browser, f_out);
		}
	}
	// se elibereaza memoria alocata de fiecare linie a fisierului
	for (int i = 0; i < comenzi; i++) {
		free(operatie[i]);
	}
	// se elibereaza memoria alocata dinamic
	browser = free_valgrind(browser);
	free(browser);
	fclose(f);
	fclose(f_out);
	return 0;
}