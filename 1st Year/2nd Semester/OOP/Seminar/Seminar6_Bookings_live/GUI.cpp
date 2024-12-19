#include "GUI.h"

void BookingsGUI::initializeGUIComponents()
{
	mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

	table = new QTableWidget;
	table->setColumnCount(4);
	table->setRowCount(srv.getAllBookings().size());
	table->setHorizontalHeaderLabels({ "Destinatie", "Perioada", "Pret", "Avans" });
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	mainLayout->addWidget(table);

	comboBoxDestinatie = new QComboBox;
	comboBoxDestinatie->addItem("Spain");
	comboBoxDestinatie->addItem("Norway");
	comboBoxDestinatie->addItem("Greece");
	comboBoxDestinatie->addItem("USA");
	comboBoxDestinatie->addItem("France");



	comboBoxPerioada = new QComboBox;
	comboBoxPerioada->addItems({ "20 - 28 iunie", "13 - 20 iulie", "12 - 19 august" });
	mainLayout->addWidget(comboBoxDestinatie);
	mainLayout->addWidget(comboBoxPerioada);


	editPret = new QLineEdit;
	editPret->setPlaceholderText("Pret");

	editAvans = new QLineEdit;
	editAvans->setPlaceholderText("Avans");

	mainLayout->addWidget(editPret);
	mainLayout->addWidget(editAvans);


	addBookingBtn = new QPushButton{ "Adaugare rezervare" };
	mainLayout->addWidget(addBookingBtn);

	removeBookingBtn = new QPushButton{ "Stergere rezervare" };
	mainLayout->addWidget(removeBookingBtn);

	discountSlider = new QSlider;
	discountSlider->setMinimum(10);
	discountSlider->setMaximum(100);

	mainLayout->addWidget(discountSlider);

	discountLbl = new QLabel{ "Discount: 10%" };
	mainLayout->addWidget(discountLbl);

	applyDiscountBtn = new QPushButton{ "Aplicare discount" };
	mainLayout->addWidget(applyDiscountBtn);

	sortAscendingButton = new QRadioButton("Sortare dupa pret - crescator");
	sortDescendingButton = new QRadioButton("Sortare dupa pret - descrescator");
	mainLayout->addWidget(sortAscendingButton);
	mainLayout->addWidget(sortDescendingButton);

	exampleSpinBox = new QSpinBox;
	exampleSpinBox->setMinimum(0);
	exampleSpinBox->setMaximum(srv.getAllBookings().size()-1);

	mainLayout->addWidget(exampleSpinBox);
}

void BookingsGUI::connectSignalsSlots()
{
	/*QObject::connect(discountSlider, &QSlider::valueChanged, [&]() {
		discountLbl->setText(QString::fromStdString("Discount: "+ std::to_string(discountSlider->value())+"%"));
		});*/
	QObject::connect(discountSlider, &QSlider::valueChanged, this, [&]() {
		int value = discountSlider->value();
		discountLbl->setText(QString::fromStdString("Discount: " + std::to_string(value) + "%"));

		});
	QObject::connect(exampleSpinBox, &QSpinBox::valueChanged,[&](int value) {
		//exemplu conectare semnal de valoare schimbata din QSpinBox, preluare valoare
		QFont serifFont("Times", 10, QFont::Bold);

		//setare atribut font la randul cu index value
		for (int col=0; col<table->columnCount();++col)
			table->item(value, col)->setFont(serifFont);

		});
	QObject::connect(addBookingBtn, &QPushButton::clicked, this, &BookingsGUI::addBooking);
	QObject::connect(addBookingBtn, &QPushButton::clicked, this, &BookingsGUI::addBooking);
	QObject::connect(removeBookingBtn, &QPushButton::clicked, this, &BookingsGUI::deleteBooking);
	
	QObject::connect(applyDiscountBtn, &QPushButton::clicked, this, &BookingsGUI::applyDiscount);
	QObject::connect(sortAscendingButton, &QRadioButton::clicked, this, []() {
		qDebug() << "Clicked RadioButton for sorting in ascending oorder.";
		});
	QObject::connect(sortDescendingButton, &QRadioButton::clicked, this, []() {
		qDebug() << "Clicked RadioButton for sorting in descending oorder.";
		});
}

void BookingsGUI::reloadData(const vector<Booking>& bookings) {
	table->setRowCount(bookings.size());
	for (size_t row = 0; row < bookings.size(); ++row) {
		const Booking& booking = bookings[row];
		table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(booking.getDestinatie())));
		table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(booking.getPerioada())));
		table->setItem(row, 2, new QTableWidgetItem(QString::number(booking.getPret(), 'f', 2)));
		table->setItem(row, 3, new QTableWidgetItem(QString::number(booking.getAvans(), 'f', 2)));
		if (booking.getAvans() > booking.getPret() / 2) {
			colorRow(row);
		}
	}
}

void BookingsGUI::addBooking() {
	try {
		string destinatie = comboBoxDestinatie->currentText().toStdString();
		string perioada = comboBoxPerioada->currentText().toStdString();
		double pret = editPret->text().toDouble();
		double avans = editAvans->text().toDouble();
		srv.addBooking(destinatie, perioada, pret, avans);
		reloadData(srv.getAllBookings());
	}
	catch (std::exception& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
	};
}

void BookingsGUI::deleteBooking() {
	if (table->selectedItems().isEmpty())
		QMessageBox::warning(this, "Warning", "Nothing selected");
	else {
		int selectedRow = table->selectedItems().at(0)->row();
		
			string destinatie = table->item(selectedRow, 0)->text().toStdString();
			string perioada = table->item(selectedRow, 1)->text().toStdString();
			double pret = table->item(selectedRow, 2)->text().toDouble();
			double avans = table->item(selectedRow, 3)->text().toDouble();
			srv.deleteBooking(destinatie, perioada);
			reloadData(srv.getAllBookings());
		
	}
}

void BookingsGUI::applyDiscount()
{
	int discount = this->discountSlider->value();
	srv.applyDiscount(discount);
	reloadData(srv.getAllBookings());

}

void BookingsGUI::colorRow(int row)
{
		for (int col = 0; col < 4; ++col) {
			table->item(row, col)->setBackground(Qt::blue);
		}
	

}

