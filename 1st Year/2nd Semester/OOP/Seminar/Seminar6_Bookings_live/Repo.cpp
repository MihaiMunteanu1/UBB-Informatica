#include "Repo.h"

void Repository::loadFromFile()
{
	std::ifstream f(filename);
	if (!f.is_open())
	{
		throw std::exception("File cannot be opened");
	}

	std::string line;
	while (std::getline(f, line))
	{
		std::istringstream iss(line);
		string token = "", destinatie, perioada;
		double pret, avans;
		int count = 0;
		while (std::getline(iss, token, ',')) {
			if (count == 0)
				destinatie = token;
			else if (count == 1)
				perioada = token;
			else if (count == 2)
				pret = stod(token);
			else {
				avans = stod(token);
			}
			count++;
		}
		if (count != 0) {
			Booking b{ destinatie, perioada, pret, avans };
			rezervari.push_back(b);
		}
	}

	f.close();


}

void Repository::store(const Booking& b)
{
	auto it = std::find_if(rezervari.begin(), rezervari.end(), [&](const Booking& bInVector) {
		return bInVector.getDestinatie() == b.getDestinatie() && b.getPerioada() == bInVector.getPerioada();
		});

	if (it != rezervari.end())
		throw std::exception("The booking already exists.");
	rezervari.push_back(b);
}

void Repository::remove(const string& destinatie, const string& perioada)
{
	auto it = std::find_if(rezervari.begin(), rezervari.end(), [&](const Booking& bInVector) {
		return bInVector.getDestinatie() == destinatie && perioada == bInVector.getPerioada();
		});

	if (it == rezervari.end())
		throw std::exception("The booking does not exist.");
	rezervari.erase(it);
}
