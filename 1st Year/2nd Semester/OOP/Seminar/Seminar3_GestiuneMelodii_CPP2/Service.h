#pragma once
#include "Repository.h"
#include "validators.h"
#include <functional>
using std::function;
class SongStore {
private:
	SongRepository& repo;
	SongValidator& val;

	/*
	Filtreaza lista de melodii pe baza unui criteriu

	@param fct: functia dupa care se filtreaza lista de melodii
	@return: lista cu melodiile care indeplinesc criteriul dat
	*/
	vector<Melodie> filter(function<bool(const Melodie&)> fct);

	/*
	* Functie de sortare proprie
	*
	* @param maiMicF: functia de comparare folosita pentru sortare
	*
	* @return: lista de melodii sortata dupa criteriul dat (vector cu elemente de
	*			tip Melodie)
	*/
	vector<Melodie> generalSort(bool(*maiMicF)(const Melodie&, const Melodie&));

public:
	SongStore(SongRepository& songRepo, SongValidator& val) :repo{ songRepo }, val{ val }{};

	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Service
	//(in aplicatie avem 1 singur Service)
	SongStore(const SongStore& ot) = delete;

	/*
	Adauga o melodie cu titlul titlu, artistul artist, genul gen si durata durata
	*@param titlu: titlul melodiei care se adauga (string)
	*@param artist: artistul melodiei care se adauga (string)
	*@param gen: genul melodiei care se adauga (string)
	*@durata durata: durata melodiei care se adauga (double, format MM.SS)
	* 
	* @throws: 
	*	RepoException daca mai exista melodie cu titlul si artistul dat
	*	ValidationException daca melodia nu este valida
	*/

	void addSong(string titlu, string artist, string gen, double durata);
	/*
	Returneaza un vector cu toate melodiile disponibile
	
	@return: lista cu toate melodiile disponibile (vector cu obiecte de tip Melodie)
	*/

	const vector<Melodie>& getAllSongs() const noexcept {
		return this->repo.getAllSongs();
	}


	/*
	* Returneaza o lista de melodii cu genul dat
	* 
	* @param gen: genul dupa care se filtreaza
	* @return: lista cu melodiile care au genul dat (vector cu elemente de tip Melodie)
	*/
	vector<Melodie> filtrareGen(string gen);

	/*
	* Returneaza o lista de melodii cu durata cuprinsa intre
	* durataStart si durataEnd
	*
	* @param durataStart: durata minima a melodiilor cautate (double)
	* @param durataEnd: durata maxima a melodiilor cautate (double)
	* 
	* @return: lista cu melodiile care au o durata care indeplineste 
	*			criteriile date (vector cu elemente de tip Melodie)
	*/
	vector<Melodie> filtrareDurata(double durataStart, double durataEnd);


	/*
	* Sorteaza melodiile dupa durata
	* 
	* @return: lista cu melodii sortate dupa durata
	*/
	vector<Melodie> sortByDurata();

	/*
	* Sorteaza melodiile dupa artist si titlul melodiei
	*
	* @return: lista cu melodii sortate dupa artist
	*/
	vector<Melodie> sortByArtistSong();

	vector<Melodie> sortByArtistNameLength();

};
void testeService();