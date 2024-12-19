#include "ListaActivitatiGUI.h"
#include <QtWidgets/qformlayout.h>
#include <qmessagebox.h>
void ListaActivitatiGUI::initConnect() {
    QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
        try {
            cos.add_to_lista_activitati(txtTitlu->text().toStdString());
            reloadList(cos.getAllListaActivitai());
        }
        catch (RepoException& ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
        }
        catch (ValidatorException& ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_msg()));
        }
    });
    QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {
        cos.clearAllListaActivitati();
        reloadList(cos.getAllListaActivitai());
    });
    QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
        try {
            int howMany=cos.addRandomToListaActivitati(txtRandom->text().toInt());
            reloadList(cos.getAllListaActivitai());
        }
        catch (RepoException& ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
        }
    });
    QObject::connect(btnPrint, &QPushButton::clicked, [&]() {
        auto activitati = cos.getAllListaActivitai();
        for (const auto& a : activitati) {
            qDebug() << QString::fromStdString(a.get_titlu()) << " " << QString::fromStdString(a.get_tip()) << " " << QString::fromStdString(a.get_descriere()) << " " << a.get_durata();
        }
    });
    QObject::connect(btnExport, &QPushButton::clicked, [&]() {
        if (txtFisier->text().isEmpty() && txtMod->text().isEmpty()) {
            QMessageBox::warning(this, "Warning", "Completati numele fisierului si modul");
            return;
        }
        if (txtMod->text().toStdString() == "HTML")
            cos.exporttofileHTML(txtFisier->text().toStdString());
        else if(txtMod->text().toStdString() == "CSV")
            cos.exporttofileCVS(txtFisier->text().toStdString());
        else {
            QMessageBox::warning(this, "Warning", "Mod invalid");
        }
    });
}
void ListaActivitatiGUI::init(){
    cos.addObserver(this);

    setLayout(mainLayout);
    activitatiTable->setColumnCount(4);
    activitatiTable->setRowCount(cos.getAllListaActivitai().size());
    mainLayout->addWidget(activitatiTable);
    auto Ly = new QHBoxLayout{};
    Ly->addWidget(btnAdauga);
    Ly->addWidget(btnGoleste);
    Ly->addWidget(btnGenereaza);
    Ly->addWidget(btnPrint);
    Ly ->addWidget(btnExport);
    auto dreaptaLy = new QFormLayout;
    dreaptaLy->addRow("Titlu", txtTitlu);
    dreaptaLy->addRow("Random", txtRandom);
    dreaptaLy->addRow("Fisier", txtFisier);
    dreaptaLy->addRow("Mod", txtMod);
    mainLayout->addLayout(Ly);
    mainLayout->addLayout(dreaptaLy);
}

void ListaActivitatiGUI::reloadList(const vector<Activitate>& activitati) {
    //activitatiWidget->clear();
    activitatiTable->clear();
    activitatiTable->setRowCount(cos.getAllListaActivitai().size());
    QStringList tableHeader;
    tableHeader << "Titlu" << "Tip" << "Descriere" << "Durata";
    activitatiTable->setHorizontalHeaderLabels(tableHeader);
    int nr=0;
    for (const auto& a : activitati) {
        activitatiTable->setItem(nr,0,new QTableWidgetItem(QString::fromStdString(a.get_titlu())));
        activitatiTable->setItem(nr,1,new QTableWidgetItem(QString::fromStdString(a.get_tip())));
        activitatiTable->setItem(nr,2,new QTableWidgetItem(QString::fromStdString(a.get_descriere())));
        activitatiTable->setItem(nr,3,new QTableWidgetItem(QString::number(a.get_durata())));
        nr++;
    }
}

