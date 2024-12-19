#pragma once
#include <QWidget.h>
#include "ListaActivitati.h"
#include <QListWidget.h>
#include <QLayout.h>
#include <QPushButton.h>
#include <QtWidgets/qlineedit.h>
#include "ActivitateService.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include "Observer.h"
#include "ListaActivitati.h"
class ListaActivitatiGUI : public QWidget, public Observer{
private:
    ActivitateService& cos;
    void init();
    void reloadList(const vector<Activitate>& activitati);
    void initConnect();
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QTableWidget* activitatiTable=new QTableWidget;
    QPushButton* btnAdauga = new QPushButton{ "&Adauga" };
    QPushButton* btnGoleste = new QPushButton{ "&Goleste" };
    QPushButton* btnGenereaza = new QPushButton{ "&Genereaza" };
    QPushButton* btnPrint = new QPushButton{ "&Print" };
    QPushButton* btnExport = new QPushButton{ "&Export" };
    QLineEdit* txtTitlu = new QLineEdit;
    QLineEdit* txtRandom = new QLineEdit;
    QLineEdit* txtFisier = new QLineEdit;
    QLineEdit* txtMod = new QLineEdit;

    void update() override {
        reloadList(cos.getAllListaActivitai());
    }

public:
    ListaActivitatiGUI(ActivitateService& cos) :cos{cos} {
         init();
         reloadList(cos.getAllListaActivitai());
         initConnect();
     }
};