#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlistwidget.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include "ActivitateService.h"
#include "ListaActivitatiGUI.h"
#include "HistogramaGUI.h"
#include "MODEL.h"
class ActivitatiGUI : public QWidget {
public:
    ActivitatiGUI(ActivitateService& srv) :srv{ srv } {
        initGUI();
        loadData(srv.get_all());
        initConnect();
    }
private:
    ActivitateService& srv;

    MyTableModel* model;
    QTableView* table=new QTableView;

    QVBoxLayout* lyButns = new QVBoxLayout{};
    QHBoxLayout* lyMain = new QHBoxLayout{};
    QListWidget* lst = new QListWidget;
    QPushButton* btnAdauga = new QPushButton{ "&Adauga" };
    QPushButton* btnUpdate = new QPushButton{ "&Update" };
    QPushButton* btnRemove = new QPushButton{ "&Remove" };
    QPushButton* btnUndo = new QPushButton{ "&Undo" };
    QPushButton* btnLista = new QPushButton{ "&Lista" };
    QPushButton* btnListaRead = new QPushButton{ "&Lista Read Only" };
    QPushButton* btnAfiseaza = new QPushButton{ "&Afiseaza" };
    QPushButton* btnSortByTitlu = new QPushButton{ "&SortByTitlu" };
    QPushButton* btnSortByDurata = new QPushButton{ "&SortByDurata" };
    QPushButton* btnFilterByTitlu = new QPushButton{ "&FilterByTitlu" };
    QPushButton* btnFilterByTip = new QPushButton{ "&FilterByTip" };
    QPushButton* btnFilterByDurata = new QPushButton{ "&FilterByDurata" };

    QLineEdit* txtTitlu = new QLineEdit;
    QLineEdit* txtDescriere = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtDurata = new QLineEdit;
    QWidget* widgetBtn =new QWidget;
    vector<QPushButton*> listaBtn;
    void initConnect();
    void loadData(const std::vector<Activitate>& activitati);
    void initGUI();
};