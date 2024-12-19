#pragma once
#include <QWidget>
#include <QApplication>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "service.h"
#include "Model.h"
#include "Observer.h"

class Window:public Observer{
private:
    Service& srv;
    string tip;
    QWidget* window = new QWidget;
    int nr;
    QLabel* lbl=new QLabel;
    QHBoxLayout* layout = new QHBoxLayout;
public:
    Window(Service& srv,string tip,int nr):srv{srv},tip{tip},nr{nr}{
        this->srv.addObserver(this);
        auto txt= QString::number(nr);
        lbl->setText(txt);
        window->setWindowTitle(QString::fromStdString(tip));
        window->setLayout(layout);
        layout->addWidget(lbl);
    }
    void update() override{
        nr=this->srv.nr_tipuri(tip);
        auto txt= to_string(nr);
        lbl->setText(QString::fromStdString(txt));
    }
    void run(){
        window->show();
    }
};

class GUI:public QWidget {
private:
    Service& srv;
    QHBoxLayout* lyMain=new QHBoxLayout;
    QTableView* table=new QTableView;
    MyTableModel* model;
    QPushButton* btnAdd=new QPushButton{"Adauga"};
    QLineEdit* txtId=new QLineEdit;
    QLineEdit* txtNume=new QLineEdit;
    QLineEdit* txtTip=new QLineEdit;
    QLineEdit* txtPret=new QLineEdit;
    QSlider* slider=new QSlider;

    void init();
    void conect();
    void load(const vector<Produs>& p,double pret);
    void addWindows();
public:
    GUI(Service& srv):srv{srv}{
        init();
        conect();
        addWindows();
    }
};



