#pragma once
#include "Song.h"
#include <vector>
using std::vector;
/*
Clasa de exceptii specifice Repo
*/
class RepoException {
private:
	string errorMsg;
public:
	RepoException(string errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		return this->errorMsg;
	}
};

class MelodieRepository {
private:
	vector<Melodie> allMelodies;
public:
	
	MelodieRepository() = default;
	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Repository
	//(in aplicatie avem 1 singur Repo)
	MelodieRepository(const MelodieRepository& ot) = delete;
	/*
	Adauga o melodie in lista
	@param s: melodia care se adauga (Melodie)
	@return -
	post: melodia va fi adaugata in lista

	@throws: RepoException daca o melodie cu acelasi titlu si acelasi artist
			 exista deja 
	*/
	virtual void store(const Melodie& s);
	/*
	Returneaza o lista cu toate melodiile
	@return: lista cu melodiile (vector of Melodie objects)
	*/
	const vector<Melodie>& getAllMelodies();
	
	/*
	Cauta o melodie cu titlul si artistul dat

	@param titlu: titlul dupa care se cauta
	@param artist: artistul dupa care se cauta 
	@returns: entitatea Melodie cu titlul si artistul dat (daca aceasta exista)
	@throws: RepoException daca nu exista melodie cu titlul si artistul dat*/
	const Melodie& find(string titlu, string artist);

	/*
	Verifica daca o melodie data exista in lista
	
	@param s: melodia care se cauta in lista
	@return: true daca melodia exista, false altfel
	*/
	bool exists(const Melodie& s);

};

class MelodieRepositoryFile : public MelodieRepository {
private:
	string filename;
	/*
	Incarca datele din fisier
	*/
	void loadFromFile();
	/*
	* Salveaza datele din fisier
	* Format: titlu,artist,gen,durata\n
	*/
	void saveToFile();
public:
	MelodieRepositoryFile(string fname) :MelodieRepository(),filename{ fname } {
		loadFromFile();
	};
	void store(const Melodie& s) override;
};

void testeRepo();
void testeFileRepo();