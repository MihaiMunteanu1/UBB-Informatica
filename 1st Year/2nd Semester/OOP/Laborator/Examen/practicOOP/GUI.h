#pragma once
#include <QApplication>
#include <QWidget>
#include "service.h"
#include "Model.h"
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QBrush>
#include <QPainter>
#include <QPaintEvent>
#include <QGraphicsView>
#include <QGraphicsScene>

class GUI:public QWidget {
private:
    Service& srv;

    QTableView* table=new QTableView;
    MyTableModel* model=new MyTableModel{srv.get_all(),srv};
    QVBoxLayout* lyMain=new QVBoxLayout;
    QPushButton* btnSterge=new QPushButton{"Sterge"};
    QPushButton* btnUpdate=new QPushButton{"Update"};

    QLineEdit* txtId=new QLineEdit;
    QLineEdit* txtDenumire=new QLineEdit;
    QLineEdit* txtTip=new QLineEdit;
    QLineEdit* txtCilindrii=new QLineEdit;

    QRadioButton* btn1=new QRadioButton{"1"};
    QRadioButton* btn2=new QRadioButton{"2"};
    QRadioButton* btn4=new QRadioButton{"4"};
    QRadioButton* btn8=new QRadioButton{"8"};

    void paintEvent(QPaintEvent* event) override;

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


