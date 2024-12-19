#include "Repository.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::endl;
using std::getline;
using std::stod;
bool MelodieRepository::exists(const Melodie& s) {
	try {
		find(s.getTitlu(), s.getArtist());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}
const Melodie& MelodieRepository::find(string titlu, string artist) {
	/*for (const Melodie& s : this->allMelodies) {
		if (s.getTitlu() == titlu && s.getArtist() == artist) {
			return s;
		}
	}*/
	vector<Melodie>::iterator f = std::find_if(this->allMelodies.begin(), this->allMelodies.end(),
		[=](const Melodie& s) {
		return s.getTitlu() == titlu && s.getArtist() == artist;
		}); 

	if (f != this->allMelodies.end())
		return (*f);
	else
		throw RepoException("Melodia cu titlul "+titlu+" si artistul "+artist +" nu exista in lista.\n");
}
void MelodieRepository::store(const Melodie& s) {
	if (exists(s)) {
		throw RepoException("Melodia cu titlul " + s.getTitlu() + " si artistul " + s.getArtist() + " nu exista in lista");
	}
	this->allMelodies.push_back(s);
}

const vector<Melodie>& MelodieRepository::getAllMelodies() {
	return this->allMelodies;
}

void MelodieRepositoryFile::loadFromFile() {
	ifstream songFile(this->filename);
	if (!songFile.is_open()) {
		throw RepoException("Cannot read from file " + filename);
	}
	string line;
	while (getline(songFile, line))
	{
		string titlu, artist, gen;
		double durata;

		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		//Citire linie de tip "Titlu,Artist,Gen,Durata"
		//separam linia cu separator = ,
		//se pot citi/scrie datele in fisier dupa cum va este usor
		//1 atribut pe o linie, sau pe o linie toate atributele, separate de spatiu etc
		while (getline(linestream, current_item, ','))
		{
			//we should do some checks here, make sure
			//that what we read is correct, throw exception otherwise
			//or 'clean' data we read
			//e.g. remove trailing spaces
			//as of now, if in file we have Venom, Eminem,... and we search
			//find("Venom","Eminem") - no space before artist, it won't work
			if (item_no == 0) titlu = current_item;
			if (item_no == 1) artist = current_item;
			if (item_no == 2) gen = current_item;
			if (item_no == 3) durata = stod(current_item);
			item_no++;
		}
		Melodie s{ titlu, artist, gen, durata };

		MelodieRepository::store(s);
		

	}
	songFile.close();
}

void MelodieRepositoryFile::saveToFile() {
	ofstream songOutput(this->filename);
	if (!songOutput.is_open())
		throw RepoException("Cannot write to file " + filename);
	for (auto& song : getAllMelodies()) {
		songOutput << song.getTitlu() << "," << song.getArtist() << ",";
		songOutput << song.getGen() << "," << song.getDurata() << endl;
	}
	songOutput.close();
}

void MelodieRepositoryFile::store(const Melodie& s){
	
	MelodieRepository::store(s);
	
	saveToFile();

}
void testAddRepo() {
	MelodieRepository testRepo;
	Melodie song1{ "Yamasha", "Alex Velea","pop",3.45 };
	testRepo.store(song1);
	assert(testRepo.getAllMelodies().size() == 1);

	Melodie song2{ "Raisa", "Fly Project", "pop", 3.42 };
	Melodie song3{ "Yamasha", "Alex Velea", "rock", 4.32 };
	try {
		testRepo.store(song3);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}


}
void testFindRepo() {
	MelodieRepository testRepo;

	Melodie song1{ "Pictures of Home", "Deep Purple", "rock",3.24 };
	Melodie song2{ "Highway Star","Deep Purple", "rock",2.44 };
	Melodie song3{ "Holy Diver","Dio", "rock", 4.45 };
	testRepo.store(song1);
	testRepo.store(song2);

	assert(testRepo.exists(song1));
	assert(!testRepo.exists(song3));

	auto foundMelodie = testRepo.find("Pictures of Home", "Deep Purple");
	assert(foundMelodie.getArtist() == "Deep Purple");
	assert(foundMelodie.getDurata() == 3.24);
	assert(foundMelodie.getGen() == "rock");


	try {
		testRepo.find("Baba O'riley", "The Who");
		assert(false);
	}
	catch (RepoException& ve) {
		
		assert(ve.getErrorMessage()== "Melodia cu titlul Baba O'riley si artistul The Who nu exista in lista.\n");
	}
}

void testeRepo() {
	testAddRepo();
	testFindRepo();
}

void testeFileRepo() {
	std::ofstream ofs;
	ofs.open("test_songs.txt", std::ofstream::out | std::ofstream::trunc);
	ofs << "Hey Hey Rise Up,Pink Floyd,rock,3.32\n";
	ofs << "Legendary,Welshly Arms,alternative,3.38\n";
	ofs << "Never Let Me Go,Florence + The Machine,indie,4.33\n";
	ofs << "Venom,Eminem,hip-hop,2.43\n";
	ofs.close();
	try {
		MelodieRepositoryFile testRepoF{ "test_songs2.txt" };
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	MelodieRepositoryFile testRepoF{ "test_songs.txt" };
	assert(testRepoF.getAllMelodies().size() == 4);


	auto foundMelodie = testRepoF.find("Venom", "Eminem");
	assert(foundMelodie.getArtist() == "Eminem");
	assert(foundMelodie.getDurata() == 2.43);
	assert(foundMelodie.getGen() == "hip-hop");

	Melodie song1{ "Pictures of Home", "Deep Purple", "rock",3.24 };

	testRepoF.store(song1);
	assert(testRepoF.getAllMelodies().size() == 5);
	Melodie foundMelodie2 = testRepoF.find("Pictures of Home", "Deep Purple");
	assert(foundMelodie2.getDurata() == 3.24);






	

}