#pragma once
#include "service.h"
#include <QApplication>
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include "Model.h"
class Painter : public QWidget {
private:
    map<string, int> genuri;
public:
    explicit Painter(map<string, int> genuri) : genuri(genuri) {
        this->repaint();
    }
    void paintEvent(QPaintEvent* ev) override;
};

class GUI:public QWidget {
private:
    Service& srv;

    QHBoxLayout* lyMain=new QHBoxLayout;

    QTableView* table=new QTableView;
    MyTableModel* model=new MyTableModel{srv.get_all(),srv};

    QPushButton* btnAdd=new QPushButton{"Adauga"};
    QPushButton* btnSterge=new QPushButton{"Sterge"};

    QLineEdit* txtId=new QLineEdit;
    QLineEdit* txtTitlu=new QLineEdit;
    QLineEdit* txtArtist=new QLineEdit;
    QLineEdit* txtGen=new QLineEdit;

    void paintEvent(QPaintEvent* ev) override;

    void init();
    void load();
    void conect();
public:
    GUI(Service& srv):srv{srv}{
        init();
        conect();
        this->repaint();
    }

};


