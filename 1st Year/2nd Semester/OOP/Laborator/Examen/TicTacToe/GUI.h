#pragma once
#include "service.h"
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTableView>
#include "Model.h"
class GUI:public QWidget {
private:
    Service& srv;
    QHBoxLayout* lyMain=new QHBoxLayout;

    QTableView* table=new QTableView;

    MyTableModel* model=new MyTableModel{srv.get_all()};

    QPushButton* btnAdd=new QPushButton{"Adauga"};
    QPushButton* btnModifica=new QPushButton{"Modifica"};

    QLineEdit* txtId=new QLineEdit;
    QLineEdit* txtDim=new QLineEdit;
    QLineEdit* txtTabla=new QLineEdit;
    QLineEdit* txtJucator=new QLineEdit;
    QLineEdit* txtStare=new QLineEdit;


    void init();
    void load();
    void conect();
public:
    GUI(Service& srv):srv{srv}{
        init();
        conect();
    }

};



