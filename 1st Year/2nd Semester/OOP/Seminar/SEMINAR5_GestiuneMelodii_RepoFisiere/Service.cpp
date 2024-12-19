#pragma once
#include "Service.h"
#include <assert.h>
#include <functional>
#include <algorithm>

void MelodieStore::addMelodie(string titlu, string artist, string gen, double durata) {
	Melodie s1{titlu, artist, gen, durata};
	val.valideaza(s1);
	repo.store(s1);

}


vector<Melodie> MelodieStore::sortByDurata() {
	vector<Melodie> sortedCopy{ repo.getAllMelodies() };
	sort(sortedCopy.begin(), sortedCopy.end(),cmpDurata);
	return sortedCopy;
}

vector<Melodie> MelodieStore::sortByArtistMelodie() {
	vector<Melodie> sortedCopy{ repo.getAllMelodies() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpArtistMelodie);
	return sortedCopy;
}

vector<Melodie> MelodieStore::filtrareGen(string gen) {
	const vector<Melodie>& allMelodies = getAllMelodies();
	vector<Melodie> filteredMelodies;
	std::copy_if(allMelodies.begin(), allMelodies.end(), back_inserter(filteredMelodies),
		[gen](const Melodie& m) {	
			return m.getGen() == gen;
		});

	return filteredMelodies;
	
}

vector<Melodie> MelodieStore::filtrareDurata(double durataStart, double durataEnd) {
	const vector<Melodie>& allMelodies = getAllMelodies();
	vector<Melodie> filteredMelodies;
	std::copy_if(allMelodies.begin(), allMelodies.end(), back_inserter(filteredMelodies),
		[=](const Melodie& m) {
			return m.getDurata()>durataStart && m.getDurata()<durataEnd;
		});

	return filteredMelodies;
}

void MelodieStore::addToPlaylist(string titlu, string artist) {
	
	const auto& song = repo.find(titlu, artist);
	currentPlaylist.addMelodieToPlaylist(song);

}
int MelodieStore::addRandomToPlaylist(int howMany) {
	currentPlaylist.addRandomMelodies(this->getAllMelodies(), howMany);
	return currentPlaylist.getAllPlaylistMelodies().size();
}
void MelodieStore::emptyPlayList() {
	currentPlaylist.emptyPlaylist();
}
const vector<Melodie>& MelodieStore::getPlaylistMelodies() {
	return currentPlaylist.getAllPlaylistMelodies();
}


void testAddService() {
	MelodieRepository testRepo;
	MelodieValidator testVal;
	MelodieStore testService{ testRepo,testVal};

	testService.addMelodie("Raisa", "Fly Project", "pop", 3.42);
	testService.addMelodie("Raisa2", "Fly Project", "pop", 3.42);
	testService.addMelodie("Raisa3", "Fly Project", "pop", 3.42);

	assert(testService.getAllMelodies().size() == 3);
	try {
		testService.addMelodie("Raisa", "Fly Project", "pop", 3.42);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		testService.addMelodie("Pictures of Home", "Deep Purple", "rock", 1.22);
		assert(true);
	}
	catch (ValidationException&) {
		assert(false);
	}
	
	try {
		testService.addMelodie("", "Deep Purple", "rock", 2.24);
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages()=="Titlul trebuie sa aiba cel putin 2 caractere.\n");
	}

	
	try {
		testService.addMelodie("Smoke on the Water", "", "rock", 2.24);
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}

	
	try {
		testService.addMelodie("High Hopes", "Pink Floyd", "rock", 2.64);
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		testService.addMelodie("Child in Time", "Deep Purple", "rock", 16);
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}


}

void testFilterService() {
	MelodieRepository testRepo;
	MelodieValidator testVal;
	MelodieStore testService{ testRepo,testVal };

	testService.addMelodie("Pasarea Calandrinon", "Phoenix", "folk-rock", 3.42);
	testService.addMelodie("Baba Novak", "Phoenix", "folk-rock", 8.31);
	testService.addMelodie("Apocalipsa", "Phoenix", "folk-rock", 5.27);
	testService.addMelodie("Fantanile", "Alternosfera", "alternative rock", 4.52);
	testService.addMelodie("Ploile Nu Vin", "Alternosfera", "alternative rock", 3.45);
	testService.addMelodie("Padure Verde", "Via Daca", "maybe folk", 3.2);

	vector<Melodie> melodiiFolkRock = testService.filtrareGen("folk-rock");
	assert(melodiiFolkRock.size() == 3);
	vector<Melodie> melodiiHeavyMetal = testService.filtrareGen("heavy metal");
	assert(melodiiHeavyMetal.size() == 0);


	vector<Melodie> melodii1 = testService.filtrareDurata(2.15, 3.44);
	assert(melodii1.size() == 2);
	vector<Melodie> melodii2 = testService.filtrareDurata(9, 10);
	assert(melodii2.size() == 0);

}

void testSortService() {

	MelodieRepository testRepo;
	MelodieValidator testVal;
	MelodieStore testService{ testRepo,testVal };

	testService.addMelodie("Pasarea Calandrinon", "Phoenix", "folk-rock", 3.42);
	testService.addMelodie("Baba Novak", "Phoenix", "folk-rock", 8.31);
	testService.addMelodie("Apocalipsa", "Phoenix", "folk-rock", 5.27);
	testService.addMelodie("Fantanile", "Alternosfera", "alternative rock", 4.52);
	testService.addMelodie("Ploile Nu Vin", "Alternosfera", "alternative rock", 3.45);
	testService.addMelodie("Padure Verde", "Via Daca", "maybe folk", 3.2);

	vector<Melodie> sortedByDurata = testService.sortByDurata();
	
	
	assert(sortedByDurata[0].getTitlu() == "Padure Verde");
	assert(sortedByDurata[1].getTitlu() == "Pasarea Calandrinon");
	assert(sortedByDurata[2].getTitlu() == "Ploile Nu Vin");
	assert(sortedByDurata[5].getTitlu() == "Baba Novak");

	vector<Melodie> sortedByArtistMelodie = testService.sortByArtistMelodie();
	assert(sortedByArtistMelodie[0].getArtist() == "Alternosfera");
	assert(sortedByArtistMelodie[0].getTitlu() == "Fantanile");

	assert(sortedByArtistMelodie[2].getArtist() == "Phoenix");
	assert(sortedByArtistMelodie[2].getTitlu() == "Apocalipsa");

	assert(sortedByArtistMelodie[5].getArtist() == "Via Daca");
	assert(sortedByArtistMelodie[5].getTitlu() == "Padure Verde");






}

void testPlaylist() {
	MelodieRepository testRepo;
	MelodieValidator testVal;
	MelodieStore testService{ testRepo,testVal };

	testService.addMelodie("Pasarea Calandrinon", "Phoenix", "folk-rock", 3.42);
	testService.addMelodie("Baba Novak", "Phoenix", "folk-rock", 8.31);
	testService.addMelodie("Apocalipsa", "Phoenix", "folk-rock", 5.27);
	testService.addMelodie("Fantanile", "Alternosfera", "alternative rock", 4.52);
	testService.addMelodie("Ploile Nu Vin", "Alternosfera", "alternative rock", 3.45);
	testService.addMelodie("Padure Verde", "Via Daca", "maybe folk", 3.2);

	testService.addRandomToPlaylist(4);
	assert(testService.getPlaylistMelodies().size() == 4);
	testService.emptyPlayList();
	assert(testService.getPlaylistMelodies().size() == 0);

	testService.addRandomToPlaylist(20);
	//putem adauga doar 6 melodii (fara sa se repete)
	assert(testService.getPlaylistMelodies().size() == 6);

	testService.emptyPlayList();
	testService.addToPlaylist("Apocalipsa", "Phoenix");
	assert(testService.getPlaylistMelodies().size() == 1);

	try {
		testService.addToPlaylist("Cocosii Negri", "Phoenix");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}


}
void testeService() {
	testAddService();
	testFilterService();
	testSortService();
	testPlaylist();
}