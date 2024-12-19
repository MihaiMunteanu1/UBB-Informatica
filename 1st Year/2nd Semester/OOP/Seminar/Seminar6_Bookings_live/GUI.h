#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QMessageBox>
#include <qspinbox.h>
#include "Service.h"
class BookingsGUI : public QWidget {
private:
	Service& srv;

	QVBoxLayout* mainLayout;
	QTableWidget* table;

	QComboBox* comboBoxDestinatie;
	QComboBox* comboBoxPerioada;
	QLineEdit* editPret;
	QLineEdit* editAvans;

	QPushButton* addBookingBtn;
	QPushButton* removeBookingBtn;

	QSlider* discountSlider;
	QLabel* discountLbl;
	QPushButton* applyDiscountBtn;

	QRadioButton* sortAscendingButton;
	QRadioButton* sortDescendingButton;
	QSpinBox* exampleSpinBox;

	void initializeGUIComponents();
	void connectSignalsSlots();
	void reloadData(const vector<Booking>& bookings);
	void addBooking();
	void deleteBooking();
	void applyDiscount();
	void colorRow( int row);

public:
	BookingsGUI(Service& _srv) : srv{ _srv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadData(srv.getAllBookings());

	};

};

