#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
class Melodie {
private:
	string titlu;
	string artist;
	string gen;
	double durata;
public:
	Melodie()=delete;
	Melodie(string titlu, string artist, string gen, double durata) :titlu{ titlu }, artist{ artist }, gen{ gen }, durata{ durata }{};
	Melodie(const Melodie& ot) :titlu{ ot.titlu }, artist{ ot.artist }, gen{ ot.gen }, durata{ ot.durata }{
		//cout << "[SONG] Copy constructor called." << endl;
	}
	

	bool operator==(const Melodie& m) {
		return this->getTitlu() == m.getTitlu() && this->getArtist()==m.getArtist();
	}
	string getTitlu() const;
	string getArtist() const;
	string getGen() const;
	double getDurata() const noexcept;

	void setTitlu(string titluNou);
	void setArtist(string artistNou);
	void setGen(string genNou);
	void setDurata(double durataNoua) noexcept;
};

/*
Compara doua melodii dupa durata

@return: true daca durata melodiei m1 e mai mica decat
		durata melodiei m2, false altfel
*/
bool cmpDurata(const Melodie& m1, const Melodie& m2);

/*
Compara doua melodii dupa artist si titlul melodiei
@return: true daca artistul melodiei m1 e inainte (alfabetic) 
		 artistului melodiei m2, false altfel 
		 daca avem acelasi artist, atunci comparam titlurile melodiilor
		 */
bool cmpArtistSong(const Melodie& m1, const Melodie& m2);

void testeDomain();