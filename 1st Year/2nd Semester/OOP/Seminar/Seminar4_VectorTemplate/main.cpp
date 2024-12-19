#define _CRT_DBG_MALLOC
#include "UI.h"
#include "vector_tests.h"
#include <iostream>
#include <crtdbg.h>
using std::cout;
using std::endl;
void testAll() {
	testAllForVector();
	cout << "Finished template vector tests." << endl;

	testeDomain();
	cout << "Finished domain tests." << endl;
	testeRepo();
	cout << "Finished repo tests." << endl;
	testeService();
	cout << "Finished service tests." << endl;



}
void startApp() {
	SongRepository repo;
	SongValidator val;
	SongStore srv{ repo,val };
	ConsoleUI ui{ srv };

	ui.run();
}
int main() {
	testAll();
	startApp();
	_CrtDumpMemoryLeaks();
}