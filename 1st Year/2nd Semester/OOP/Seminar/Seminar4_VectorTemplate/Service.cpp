#pragma once
#include "Service.h"
#include <assert.h>
#include <functional>
#include <algorithm>
using std::sort;
void SongStore::addSong(string titlu, string artist, string gen, double durata) {
	Melodie s1{titlu, artist, gen, durata};
	val.valideaza(s1);
	repo.addSong(s1);

}

MyVector<Melodie> SongStore::generalSort(bool(*maiMicF)(const Melodie&, const Melodie&)) {
	MyVector<Melodie> v{ repo.getAllSongs() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {
				//interschimbam
				std::swap(v[i], v[j]);
			}
		}
	}
	return v;
}



MyVector<Melodie> SongStore::sortByDurata() {
	auto sortedCopy = repo.getAllSongs();
	//folosim std::sort pentru sortare
	//https://cplusplus.com/reference/algorithm/sort/
	//folosim functia cmpDurata pentru criteriu
	return generalSort(cmpDurata);
}

MyVector<Melodie> SongStore::sortByArtistSong() {
	//folosim functia scrisa de noi pentru sortare
	//putem folosi si noi functie ca parametru
	//pentru criteriu
	return generalSort(cmpArtistSong);
}

MyVector<Melodie> SongStore::sortByArtistNameLength() {
	//putem folosi si functii lambda cu parametru formal
	//la generalSort function pointer, dar doar atata timp
	//cat nu avem nevoie de nimic in []
	// forma unei functii lambda: [](){}
	//[]: capture clause
	//    i.e. putem specifica care variabile din "exteriorul" (enclosing/surrounding scope)
	//         functiei lambda vrem sa le accesam in corpul acestei functii, si
	//         cum sa fie transmise acestea
	//    e.g. [=]: toate variabilele din "exterior", transmise prin valoare functiei lambda
	//		   [&]: toate variabilele din "exterior", transmise prin referinta functiei (pot fi modificate)
	//         [durata]: (doar) variabila durata va putea fi accesata, este transmisa prin valoare
	//		   [&durata]: (doar) variabila durata va putea fi accesata, este transmisa prin referinta

	//(): lista de parametri
	//{}: corpul functiei
	
	return generalSort([](const Melodie& m1, const Melodie& m2) {
		return m1.getArtist().length() < m2.getArtist().length();
		});

}

MyVector<Melodie> SongStore::filter(function<bool(const Melodie&)> fct) {
	MyVector<Melodie> filteredSongs;
	for (const auto& song : repo.getAllSongs()) {
		if (fct(song)) {
			filteredSongs.push_back(song);
		}
	}
	return filteredSongs;
}

MyVector<Melodie> SongStore::filtrareGen(string gen) {
	return filter([gen](const Melodie& m) {
		return m.getGen() == gen;
		});
}

MyVector<Melodie> SongStore::filtrareDurata(double durataStart, double durataEnd) {
	/*return filter([=](const Melodie& m) {
		return m.getDurata() >= durataStart && m.getDurata() <= durataEnd;
		});*/
	//sau
	return filter([durataStart,durataEnd](Melodie m) {
		return m.getDurata() >= durataStart && m.getDurata() <= durataEnd;
});
}


void testAddService() {
	SongRepository testRepo;
	SongValidator testVal;
	SongStore testService{ testRepo,testVal};

	testService.addSong("Raisa", "Fly Project", "pop", 3.42);
	testService.addSong("Raisa2", "Fly Project", "pop", 3.42);
	testService.addSong("Raisa3", "Fly Project", "pop", 3.42);

	assert(testService.getAllSongs().size() == 3);
	try {
		testService.addSong("Raisa", "Fly Project", "pop", 3.42);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		testService.addSong("Pictures of Home", "Deep Purple", "rock", 1.22);
		assert(true);
	}
	catch (ValidationException&) {
		assert(false);
	}
	
	try {
		testService.addSong("", "Deep Purple", "rock", 2.24);
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages()=="Titlul trebuie sa aiba cel putin 2 caractere.\n");
	}

	
	try {
		testService.addSong("Smoke on the Water", "", "rock", 2.24);
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}

	
	try {
		testService.addSong("High Hopes", "Pink Floyd", "rock", 2.64);
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		testService.addSong("Child in Time", "Deep Purple", "rock", 16);
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}


}

void testFilterService() {
	SongRepository testRepo;
	SongValidator testVal;
	SongStore testService{ testRepo,testVal };

	testService.addSong("Pasarea Calandrinon", "Phoenix", "folk-rock", 3.42);
	testService.addSong("Baba Novak", "Phoenix", "folk-rock", 8.31);
	testService.addSong("Apocalipsa", "Phoenix", "folk-rock", 5.27);
	testService.addSong("Fantanile", "Alternosfera", "alternative rock", 4.52);
	testService.addSong("Ploile Nu Vin", "Alternosfera", "alternative rock", 3.45);
	testService.addSong("Padure Verde", "Via Daca", "maybe folk", 3.2);

	MyVector<Melodie> melodiiFolkRock = testService.filtrareGen("folk-rock");
	assert(melodiiFolkRock.size() == 3);
	MyVector<Melodie> melodiiHeavyMetal = testService.filtrareGen("heavy metal");
	assert(melodiiHeavyMetal.size() == 0);


	MyVector<Melodie> melodii1 = testService.filtrareDurata(2.15, 3.44);
	assert(melodii1.size() == 2);
	MyVector<Melodie> melodii2 = testService.filtrareDurata(9, 10);
	assert(melodii2.size() == 0);

}

void testSortService() {

	SongRepository testRepo;
	SongValidator testVal;
	SongStore testService{ testRepo,testVal };

	testService.addSong("Pasarea Calandrinon", "Phoenix", "folk-rock", 3.42);
	testService.addSong("Baba Novak", "Phoenix", "folk-rock", 8.31);
	testService.addSong("Apocalipsa", "Phoenix", "folk-rock", 5.27);
	testService.addSong("Fantanile", "Alternosfera", "alternative rock", 4.52);
	testService.addSong("Ploile Nu Vin", "Alternosfera", "alternative rock", 3.45);
	testService.addSong("Padure Verde", "Via Daca", "maybe folk", 3.2);

	MyVector<Melodie> sortedByDurata = testService.sortByDurata();
	assert(sortedByDurata[0].getTitlu() == "Padure Verde");
	assert(sortedByDurata[1].getTitlu() == "Pasarea Calandrinon");
	assert(sortedByDurata[2].getTitlu() == "Ploile Nu Vin");
	assert(sortedByDurata[5].getTitlu() == "Baba Novak");

	MyVector<Melodie> sortedByArtistSong = testService.sortByArtistSong();
	assert(sortedByArtistSong[0].getArtist() == "Alternosfera");
	assert(sortedByArtistSong[0].getTitlu() == "Fantanile");

	assert(sortedByArtistSong[2].getArtist() == "Phoenix");
	assert(sortedByArtistSong[2].getTitlu() == "Apocalipsa");

	assert(sortedByArtistSong[5].getArtist() == "Via Daca");
	assert(sortedByArtistSong[5].getTitlu() == "Padure Verde");

	MyVector<Melodie> sortedByArtistNameLength = testService.sortByArtistNameLength();
	assert(sortedByArtistNameLength[0].getArtist() == "Phoenix");
	assert(sortedByArtistNameLength[1].getArtist() == "Phoenix");
	assert(sortedByArtistNameLength[2].getArtist() == "Phoenix");

	assert(sortedByArtistNameLength[3].getArtist() == "Via Daca");
	assert(sortedByArtistNameLength[4].getArtist() == "Alternosfera");
	assert(sortedByArtistNameLength[5].getArtist() == "Alternosfera");





}
void testeService() {
	testAddService();
	testFilterService();
	testSortService();
}