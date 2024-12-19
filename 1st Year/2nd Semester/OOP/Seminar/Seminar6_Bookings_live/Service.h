#pragma once
#include "Repo.h"
class Service {
private:
	Repository& repo;
public:
	Service(Repository& repo) :repo{ repo } {};
	const vector<Booking>& getAllBookings() {
		return repo.getAllBookings();
	}
	/// <summary>
	/// Adauga rezervare
	/// </summary>
	/// <param name="destinatie">Destinatia</param>
	/// <param name="perioada">Perioada</param>
	/// <param name="pret">Pretul</param>
	/// <param name="avans">Avansul</param>
	/// Arunca exceptie (std::exception) daca mai exista rezervare cu aceasta destinatie si in aceasta perioada
	void addBooking(const string& destinatie, const string& perioada, const double& pret, const double& avans) {
		Booking b{ destinatie, perioada, pret, avans };
		repo.store(b);
	}

	/// <summary>
	/// Sterge o rezervare
	/// </summary>
	/// <param name="destinatie">Destinatia rezervarii care se sterge</param>
	/// <param name="perioada">Perioada rezervarii care se sterge</param>
	void deleteBooking(const string& destinatie, const string& perioada) {
		repo.remove(destinatie, perioada);
	}	
	/// <summary>
	/// Aplica discount-ul dat la fiecare rezervare din lista
	/// </summary>
	/// <param name="discountPercent">Procentul de discount</param>
	void applyDiscount(const int& discountPercent);

};


//TO-DO: add tests