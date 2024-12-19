#pragma once
#include "service.h"
#include "MODEL.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCheckBox>
#include <QComboBox>
#include <QLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

class GUI:public QWidget {
private:
    Service& srv;
    void init();
    void connect();
    void load();

    QHBoxLayout* ly=new QHBoxLayout;
    QComboBox* comboBox=new QComboBox;
    QTableView* table=new QTableView;
    MyTableModel* model;
    QGraphicsView* view = new QGraphicsView;
    QGraphicsScene* scene = new QGraphicsScene;
    QLineEdit* editId = new QLineEdit;
    QLineEdit* editDenumire = new QLineEdit;
    QLineEdit* editTip = new QLineEdit;
    QLineEdit* editNrRoti = new QLineEdit;
    QPushButton* btnAdaugare = new QPushButton("&Adaugare");

public:
    GUI(Service& srv):srv{srv}{
        init();
        connect();
    }
};



