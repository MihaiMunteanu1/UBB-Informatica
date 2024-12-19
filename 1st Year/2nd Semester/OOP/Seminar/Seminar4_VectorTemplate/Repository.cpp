#include "Repository.h"
#include <assert.h>



bool SongRepository::isin(const Melodie& songToSearchFor) {
	for (const auto& songInRepo : this->allSongs)
		//functioneaza doar daca facem overload la ==
		if (songInRepo==songToSearchFor) 
			return true;
	return false;
}
const Melodie& SongRepository::find(string titlu, string artist) {
	for (const Melodie& s : this->allSongs) {
		if (s.getTitlu() == titlu && s.getArtist() == artist) {
			return s;
		}
	}
	throw RepoException("Melodia cu titlul "+titlu+" si artistul "+artist +" nu exista in lista");
}

void SongRepository::addSong(const Melodie& s) {
	if (isin(s)) {
		throw RepoException("Melodia cu titlul " + s.getTitlu() + " si artistul " + s.getArtist() + " exista deja in lista.");
	}
	this->allSongs.push_back(s);
}

const MyVector<Melodie>& SongRepository::getAllSongs() const noexcept{
	return this->allSongs;
}

void testAddRepo() {
	SongRepository testRepo;
	Melodie song1{ "Learning to Fly", "Pink Floyd","rock",8 };
	testRepo.addSong(song1);
	assert(testRepo.getAllSongs().size() == 1);

	Melodie song2{ "Shine on You (Crazy Diamond)", "Pink Floyd", "rock", 3.42 };
	Melodie song3{ "Learning to Fly", "Pink Floyd","rock",8 };
	try {
		testRepo.addSong(song3);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}


}
void testFindRepo() {
	SongRepository testRepo;

	Melodie song1{ "Pictures of Home", "Deep Purple", "rock",3.24 };
	Melodie song2{ "Highway Star","Deep Purple", "rock",2.44 };
	Melodie song3{ "Holy Diver","Dio", "rock", 4.45 };
	testRepo.addSong(song1);
	testRepo.addSong(song2);

	assert(testRepo.isin(song1));
	assert(!testRepo.isin(song3));

	auto& foundSong = testRepo.find("Pictures of Home", "Deep Purple");
	assert(foundSong.getArtist() == "Deep Purple");
	assert(foundSong.getDurata() == 3.24);
	assert(foundSong.getGen() == "rock");


	try {
		testRepo.find("Baba O'riley", "The Who");
		assert(false);
	}
	catch (RepoException& ve) {
		assert(ve.getErrorMessage()== "Melodia cu titlul Baba O'riley si artistul The Who nu exista in lista");
	}
}

ostream& operator<<(ostream& stream, const RepoException& exception)
{
	stream << exception.errorMsg << "\n";
	return stream;
}


void testeRepo() {
	testAddRepo();
	testFindRepo();
}