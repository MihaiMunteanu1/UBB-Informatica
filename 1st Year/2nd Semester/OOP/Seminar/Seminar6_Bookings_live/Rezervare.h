#pragma once
#include <string>
using std::string;
class Booking {
private:
	string destinatie;
	string perioada;
	double pret;
	double avans;
public:
	Booking() = default;
	Booking(const string& _dest, const string& _perioada, const double& _pret, const double& _avans = 0) : destinatie{ _dest }, perioada{ _perioada }, pret{ _pret }, avans{ _avans } { };
	
	string getDestinatie() const {
		return destinatie;
	}
	string getPerioada() const {
		return perioada;
	}
	double getPret() const {
		return pret;
	}
	double getAvans() const {
		return avans;
	}

	void setDestinatie(const string& newDest) {
		destinatie = newDest;
	}
	void setPerioada(const string& newP) {
		perioada = newP;
	}

	void setPret(double newPret) {
		pret = newPret;
	}

	void setAvans(double newAvans) {
		avans = newAvans;
	}



};