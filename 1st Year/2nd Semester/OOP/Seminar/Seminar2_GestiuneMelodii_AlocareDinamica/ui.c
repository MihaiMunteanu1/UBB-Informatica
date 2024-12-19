#define _CRD_DBG_MALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>   // WinApi header

#include "service.h"

void printMenu() {
	printf("Aplicatie gestiune melodii.\n");
	printf("1. Adauga o melodie\n");
	printf("2. Filtreaza melodii dupa artist\n");
	printf("3. Afiseaza lista de melodii\n");
	printf("4. Iesire\n");
}

void printColoredText(char* message, int colorCode) {
	//albastru inchis: 1 sau 9
	//verde: 2 sau 10
	//rosu: 4 sau 12

	HANDLE  hConsole;
	

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// you can loop k higher to see more color choices
	
	SetConsoleTextAttribute(hConsole, colorCode);
	printf("%s",  message);
		//reset to default
		SetConsoleTextAttribute(hConsole, 7);
		



}
void testAll() {
	printf("jjjj");
	printf("Testare creare si distrugere melodie...");
	testCreateDestroyMelodie();
	printColoredText("done.\n",10);
	printf("Testare creare lista...");
	testCreateList();
	printColoredText("done.\n",10);
	printf("Testare adaugare in lista...");
	testAddToList();
	printColoredText("done.\n",10);
	printf("Testare stergere in lista...");
	testDeleteFromList();
	printColoredText("done.\n", 10);
	printf("Testare copiere lista...");
	testCopyList();
	printColoredText("done.\n", 10);
	printf("Testare adaugare service...");
	testAddService();
	printColoredText("done.\n", 10);
	printf("Testare filtrare service...");
	testFiltrareService();
	printColoredText("done.\n", 10);
	printColoredText("Teste incheiate cu succes.\n", 2);
	
	
}
void printMelodii(List* lista) {
	for (int i = 0; i < size(lista); i++) {
		Melodie m = getElem(lista, i);
		printf("Titlu: %s | Artist: %s | Durata: %lf\n", m.titlu, m.artist, m.durata);
	}
}

void uiAdaugaMelodie(ManagerMelodii* manager) {
	char titlu[30];
	char artist[30];
	double durata;
	getchar();
	printf("Titlu melodie: ");
	fgets(titlu,30, stdin);
	printf("Artist melodie: ");
	fgets(artist, 30, stdin);
	printf("Durata melodie:");
	scanf_s("%lf", &durata);
	titlu[strcspn(titlu, "\n")] = 0;
	artist[strcspn(artist, "\n")] = 0;


	int errorCode = adaugaMelodie(manager, titlu, artist, durata);
	if (errorCode != 0)
		printColoredText("Eroare: melodie invalida.\n", 4);
	else {
		printColoredText("Melodie adaugata cu succes.\n",2);
	}

	
}


void uiFiltreazaMelodie(ManagerMelodii* manager) {
	char artist[30];
	printf("String artist dupa care se filtreaza: ");
	getchar();
	fgets(artist, 30, stdin);
	artist[strcspn(artist, "\n")] = 0;
	List filteredList = filtreazaMelodie(manager, artist);
	printMelodii(&filteredList);
	destroy(&filteredList);
}

void adaugaDefault(ManagerMelodii* manager) {
	adaugaMelodie(manager, "Stairway to Heaven", "Led Zeppelin", 4.4);
	adaugaMelodie(manager, "Perfect strangers", "Deep Purple", 3.22);
	adaugaMelodie(manager, "Highway Star", "Deep Pruple", 10.3);
	adaugaMelodie(manager, "Nunta", "Phoenix", 4.03);
	adaugaMelodie(manager, "Vasiliscul si Aspida", "Phoenix", 3.22);




}
void run() {
	bool is_running = true;
	ManagerMelodii managerMelodii = createManagerMelodii();
	adaugaDefault(&managerMelodii);
	while (is_running) {
		printMenu();
		printf(">>>");
		short int option;
		scanf_s("%hd", &option);
		switch (option) {
		case 1:
			printf("Ati ales optiunea adaugare melodie.\n");
			uiAdaugaMelodie(&managerMelodii);
			break;
		case 2:
			printf("Filtreaza melodii dupa artist.\n");
			uiFiltreazaMelodie(&managerMelodii);
			break;
		case 3:
			printf("Lista de melodii este:\n");
			printMelodii(&managerMelodii.listaMelodii);
			break;
		case 4:
			is_running = false;
			destroyManager(&managerMelodii);
			break;
		default:
			printf("Optiune invalida.\n");
			break;
		}
		
	}
}

int main() {
	testAll();

	//run();
	_CrtDumpMemoryLeaks();
}