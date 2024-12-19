#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Rezervare.h"
using std::vector;
class Repository {
private:
	vector<Booking> rezervari;
	string filename;

	void loadFromFile();
public:
	Repository(const string& _filename = "data.txt") : filename{ _filename } {
		loadFromFile();
	}	
	/// <summary>
	/// Adauga rezervarea data in lista de rezervari
	/// </summary>
	/// <param name="b">Rezervarea care se va adauga</param>
	void store(const Booking& b);
	vector<Booking>& getAllBookings() {
		return rezervari;
	}	
	/// <summary>
	/// Sterge rezervarea cu destinatia si perioada data
	/// </summary>
	/// <param name="destinatie">Destinatia data</param>
	/// <param name="perioada">Perioada data</param>

	void remove(const string& destinatie, const string& perioada);


};