#include "service.h"
#include <assert.h>
#include <stdio.h>
ManagerMelodii createManagerMelodii()
{
	ManagerMelodii manager;
	manager.listaMelodii = createEmpty();
	return manager;
}
int adaugaMelodie(ManagerMelodii* manager, char* titlu, char* artist, double durata)
{
	Melodie m = createMelodie(titlu, artist, durata);
	int valCode = valideazaMelodie(m);
	if (valCode != 0) {
		destroyMelodie(&m);
		return valCode;
	}
	add(&manager->listaMelodii, m);
	return 0;
}


List filtreazaMelodie(ManagerMelodii* manager, char* artistStr)
{
	if (artistStr == NULL || strlen(artistStr) == 0)
		return copyList(&manager->listaMelodii);
	List filteredList = createEmpty();
	for (int i = 0; i < size(&manager->listaMelodii); i++) {
		Melodie m = getElem(&manager->listaMelodii, i);
		if (strstr(m.artist, artistStr) != NULL)
			add(&filteredList, copyMelodie(&m));
	}
	return filteredList;
}

void destroyManager(ManagerMelodii* manager) {
	destroy(&manager->listaMelodii);
}
void testAddService()
{
	ManagerMelodii testManager = createManagerMelodii();
	int errorCode = adaugaMelodie(&testManager, "", "Led Zeppelin", 3.21);
	assert(errorCode == 1);
	List allSongs = filtreazaMelodie(&testManager, NULL);
	assert(size(&allSongs) == 0);
	destroy(&allSongs);

	errorCode = adaugaMelodie(&testManager, "Tom Sawyer", "", 3.21);
	assert(errorCode == 2);
	allSongs = filtreazaMelodie(&testManager, NULL);
	assert(size(&allSongs) == 0);
	destroy(&allSongs);


	errorCode = adaugaMelodie(&testManager, "Tom Sawyer", "Rush", 100);
	assert(errorCode == 3);
	allSongs = filtreazaMelodie(&testManager, NULL);
	assert(size(&allSongs) == 0);
	destroy(&allSongs);


	errorCode = adaugaMelodie(&testManager, "Fortunate Son", "CCR", 4.12);
	assert(errorCode == 0);

	allSongs = filtreazaMelodie(&testManager, NULL);
	assert(size(&allSongs) == 1);
	destroy(&allSongs);

	destroyManager(&testManager);
}


void testFiltrareService()
{

	ManagerMelodii testManager = createManagerMelodii();
	int errorCode = adaugaMelodie(&testManager, "Fata verde", "Phoenix", 3.21);
	assert(errorCode == 0);
	errorCode = adaugaMelodie(&testManager, "Tom Sawyer", "Rush", 3.21);
	assert(errorCode == 0);
	errorCode = adaugaMelodie(&testManager, "Nunta", "Phoenix", 4.23);
	assert(errorCode == 0);
	errorCode = adaugaMelodie(&testManager, "Stairway to Heaven", "Led Zeppelin", 5.1);
	assert(errorCode == 0);

	List filteredList1 = filtreazaMelodie(&testManager, NULL);
	assert(size(&filteredList1) == 4);
	destroy(&filteredList1);

	List filteredList2 = filtreazaMelodie(&testManager, "Zeppelin");
	assert(size(&filteredList2) == 1);
	destroy(&filteredList2);

	List filteredList3 = filtreazaMelodie(&testManager, "Phoenix");
	assert(size(&filteredList3) == 2);
	destroy(&filteredList3);

	List filteredList4 = filtreazaMelodie(&testManager, "Floyd");
	assert(size(&filteredList4) == 0);
	destroy(&filteredList4);

	destroyManager(&testManager);
}
