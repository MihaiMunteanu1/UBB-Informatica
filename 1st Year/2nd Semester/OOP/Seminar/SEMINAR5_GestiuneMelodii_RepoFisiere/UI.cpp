#pragma once
#include "UI.h"
#include <iostream>
using namespace std;
void ConsoleUI::printMenu() {
	cout << "Comenzi disponibile:" << endl;
	cout << "1. Adauga melodie" << endl;
	cout << "2. Filtreaza melodii" << endl;
	cout << "3. Sorteaza melodii" << endl;
	cout << "4. Afiseaza toate melodiile" << endl;
	cout << "5. Playlist menu" << endl;
	cout << "0. Exit" << endl;
}
void ConsoleUI::printPlaylistMenu() {
	cout << "MENIU PLAYLIST"<< endl;
	cout << "1. Adauga melodie in playlist" << endl;
	cout << "2. Adauga melodii random in playlist" << endl;
	cout << "3. Goleste playlist" << endl;
	cout << "4. Afiseaza playlist curent" << endl;
	cout << "5. Inapoi la meniul principal" << endl;
}

void ConsoleUI::uiAdd() {
	string titlu, artist, gen;
	double durata;
	cout << "Titlul melodiei este:";
	getline(cin >> ws, titlu);

	cout << "Artistul melodiei este:";
	getline(cin >> ws, artist);
	cout << "Genul melodiei este:";
	getline(cin >> ws, gen);

	cout << "Durata melodiei (numar real, intre 0.5 si 15, format MM.SS) este:";
	cin >> durata;
	try {
		srv.addMelodie(titlu, artist,gen, durata);
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidationException& ve) {
		cout << "Melodia nu este valida!" << endl;
		cout << ve.getErrorMessages();
	}

}

void ConsoleUI::uiSort() {
	cout << "Criteriul de sortare este (durata/artist+titlu):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "durata")
		printMelodies(srv.sortByDurata());
	else if (criteriu == "artist+titlu")
		printMelodies(srv.sortByArtistMelodie());
	else
		cout << "Nu se poate sorta dupa criteriul dat." << endl;

}

void ConsoleUI::uiFilter() {
	cout << "Criteriul de filtrare este (gen/durata):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "gen") {
		cout << "Genul pentru care se afiseaza melodiile:" << endl;
		string searchedGenre;
		cin >> searchedGenre;
		printMelodies(srv.filtrareGen(searchedGenre));
	}
	else if (criteriu == "durata") {
		double durataStart, durataEnd;
		cout << "Limita inferioara a duratei:" << endl;
		cin >> durataStart;
		cout << "Limita superioara a duratei:" << endl;
		cin >> durataEnd;

		printMelodies(srv.filtrareDurata(durataStart,durataEnd));
	}

	else
		cout << "Nu se poate sorta dupa criteriul dat." << endl;
}

void ConsoleUI::uiAddToPlaylist() {
	string titlu, artist;
	cout << "Titlul melodiei este:";
	getline(cin >> ws, titlu);

	cout << "Artistul melodiei este:";
	getline(cin >> ws, artist);
	
	try {
		srv.addToPlaylist(titlu, artist);
		cout << "Melodia s-a adaugat cu succes la playlist." << endl;
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidationException& ve) {
		cout << "Melodia nu este valida!" << endl;
		cout << ve.getErrorMessages();
	}
}
void ConsoleUI::uiAddRandomToPlaylist() {
	int howManyToAdd;
	cout << "Cate melodii sa se adauge in playlist?";
	cin >> howManyToAdd;


	try {
		int howManyAdded = srv.addRandomToPlaylist(howManyToAdd);
		cout << "S-au adaugat " << howManyAdded << " melodii in playlist." << endl;
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
}
	

void ConsoleUI::uiEmptyPlaylist() {
	srv.emptyPlayList();
	cout << "S-au sters toate melodiile din playlist-ul curent." << endl;
}
void ConsoleUI::printMelodies(const vector<Melodie>& allMelodies) {

	if (allMelodies.size() == 0)
		cout << "Nu exista melodii." << endl;
	else{
		
		for (const auto& song: allMelodies){
			cout << "Titlu: " << song.getTitlu() << " | Artist: " << song.getArtist() << " | Gen: " << song.getGen() << " | Durata: " << song.getDurata() << endl;
		}
		}
}


void ConsoleUI::uiPlayList() {
	int cmd;
	int runningPlayList = 1;
	while (runningPlayList) {
		printPlaylistMenu();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiAddToPlaylist();
			break;
		case 2:
			uiAddRandomToPlaylist();
			break;
		case 3:
			uiEmptyPlaylist();
			break;

		case 4:
			printMelodies(srv.getPlaylistMelodies());
			break;
		case 5:
			runningPlayList = 0;
			break;
		default:
			break;
		}

	}
}

//void ConsoleUI::addDefaultMelodies() {
//	srv.addMelodie("Pictures of Home", "Deep Purple", "rock", 5.3);
//	srv.addMelodie("Penny Lane", "The Beatles", "indie rock",3.32);
//	srv.addMelodie("Strawberry Fields Forever", "The Beatles", "indie rock",3.48);
//	srv.addMelodie("While my Guitar Gently Weeps", "The Beatles", "indie rock", 4.21);
//	srv.addMelodie("Fata verde", "Phoenix", "rock", 4.31);
//	srv.addMelodie("Vasiliscul si Aspida", "Phoenix", "folk-rock", 7.20);
//	srv.addMelodie("Sat dupa sat", "Robin and the Backstabbers", "alternative rock", 2.51);
//	srv.addMelodie("Linistea", "Om la luna", "acoustic", 5.11);
//	
//}
void ConsoleUI::run() {
	int running = 1;
	int cmd;
	//addDefaultMelodies();
	while (running) {
		printMenu();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiAdd();
			break;
		case 2:
			uiFilter();
			break;
		case 3:
			uiSort();
			break;
	
		case 4:
			printMelodies(srv.getAllMelodies());
			break;
		case 5:
			uiPlayList();
			break;
		case 0:
			running = 0;
			break;
		default:
			break;
		}

	}
}