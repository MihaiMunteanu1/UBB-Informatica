#pragma once
#include "service.h"
#include <QApplication>
#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSlider>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "Model.h"
class GUI: public QWidget {
private:
    Service& srv;

    QVBoxLayout* main=new QVBoxLayout;
    QGraphicsView* view = new QGraphicsView(this);
    QGraphicsScene* scene = new QGraphicsScene(this);
    QHBoxLayout* lyMain=new QHBoxLayout;

    QTableView* table=new QTableView;
    MyTableModel* model=new MyTableModel{srv.get_all(),srv};

    QSlider* slider=new QSlider;
    QPushButton* btnDelete=new QPushButton{"Delete"};
    QPushButton* btnUpdate=new QPushButton{"Update"};
    QLineEdit* txtId=new QLineEdit;
    QLineEdit* txtTitlu=new QLineEdit;
    QLineEdit* txtArtist=new QLineEdit;
    QLineEdit* txtRank=new QLineEdit;


    void init();
    void load();
    void conect();
public:
    GUI(Service& srv):srv{srv}{
        init();
        conect();
    }

    void paintEvent(QPaintEvent *event);
};



