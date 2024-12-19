#pragma once
#include "Service.h"
class ConsoleUI {
private:
	SongStore& srv;
public:
	ConsoleUI(SongStore& srv) :srv{ srv } {};
	ConsoleUI(const ConsoleUI& ot) = delete;

	void printMenu();
	void uiAdd();
	void uiSort();
	void uiFilter();
	void addDefaultSongs();
	void printSongs(const MyVector<Melodie>& allSongs);
	void run();
};
