#include "Service.h"

void Service::applyDiscount(const int& discountPercent)
{
	//Alternativ: functie modificare in repo
	for (Booking& b : repo.getAllBookings()) {
		b.setPret(b.getPret() - (b.getPret() * discountPercent) / 100);
	}
}
