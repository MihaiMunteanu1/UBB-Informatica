#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include "UI.h"
#include <iostream>
using std::cout;
using std::endl;
void testAll() {
	testeDomain();
	cout << "Finished domain tests." << endl;
	testeRepo();
	testeFileRepo();
	cout << "Finished repo tests." << endl;
	testeService();
	cout << "Finished service tests." << endl;

}
void startApp() {
	MelodieRepository repo;
	//MelodieRepositoryFile repo{"songs.txt"};
	
	MelodieValidator val;
	MelodieStore srv{ repo,val };
	ConsoleUI ui{ srv };

	ui.run();
}
int main() {
	testAll();
	startApp();
	_CrtDumpMemoryLeaks();
	return 0;

}