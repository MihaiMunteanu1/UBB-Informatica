#pragma once
#include "Service.h"
class ConsoleUI {
private:
	MelodieStore& srv;
public:
	ConsoleUI(MelodieStore& srv) :srv{ srv } {};
	ConsoleUI(const ConsoleUI& ot) = delete;

	void printMenu();
	void printPlaylistMenu();
	void uiAdd();
	void uiSort();
	void uiFilter();
	void uiPlayList();
	void uiAddToPlaylist();
	void uiAddRandomToPlaylist();
	void uiEmptyPlaylist();
	//void addDefaultMelodies();
	void printMelodies(const vector<Melodie>& allMelodies);
	void run();
};
