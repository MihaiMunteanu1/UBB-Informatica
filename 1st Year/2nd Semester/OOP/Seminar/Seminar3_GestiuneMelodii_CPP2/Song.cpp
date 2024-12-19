#include "Song.h"
#include <assert.h>
string Melodie::getTitlu() const {
	return this->titlu;
}
string Melodie::getArtist() const {
	return this->artist;
}
string Melodie::getGen() const {
	return this->gen;
}
double Melodie::getDurata() const noexcept{
	return this->durata;
}

void Melodie::setArtist(string artistNou) {
	this->artist = artistNou;
}
void Melodie::setTitlu(string titluNou) {
	this->titlu = titluNou;
}
void Melodie::setGen(string genNou) {
	this->gen = genNou;
}
void Melodie::setDurata(double durataNoua) noexcept {
	this->durata = durataNoua;
}



bool cmpDurata(const Melodie& m1, const Melodie& m2)  {
	return m1.getDurata() < m2.getDurata();
}

bool cmpArtistSong(const Melodie& m1, const Melodie& m2) {
	if (m1.getArtist() == m2.getArtist())
		return m1.getTitlu() < m2.getTitlu();
	else
		return m1.getArtist() < m2.getArtist();
}


void testGetSet() {
	Melodie song1{ "Pictures of Home", "Deep Purple","rock",1.22};
	assert(song1.getTitlu() == "Pictures of Home");
	assert(song1.getArtist() == "Deep Purple");
	assert(song1.getGen() == "rock");
	assert(song1.getDurata() == 1.22);

	Melodie song2{ "Lucky Man", "Emerson, Lake & Palmer","rock",3.44 };
	assert(song2.getTitlu() == "Lucky Man");
	assert(song2.getArtist() == "Emerson, Lake & Palmer");
	assert(song2.getGen() == "rock");
	assert(song2.getDurata() == 3.44);

	song2.setTitlu("Goodbye Blue Sky");
	song2.setArtist("Pink Floyd");
	song2.setGen("psychedelic rock");
	song2.setDurata(5.22);

	assert(song2.getTitlu() == "Goodbye Blue Sky");
	assert(song2.getArtist() == "Pink Floyd");
	assert(song2.getGen() == "psychedelic rock");
	assert(song2.getDurata() == 5.22);



}

void testeDomain() {
	testGetSet();
}