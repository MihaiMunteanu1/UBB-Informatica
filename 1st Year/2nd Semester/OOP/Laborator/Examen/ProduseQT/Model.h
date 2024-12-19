#pragma once

#pragma once
#include <QAbstractTableModel>
#include "domain.h"
#include <vector>
#include <QBrush>
using std::vector;

class MyTableModel : public QAbstractTableModel {
    vector<Produs> produse;
    double pret;
public:
    MyTableModel(const vector<Produs> produse,double pret) : produse{produse},pret{pret} {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return produse.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        Produs a = produse[index.row()];
        if(role == Qt::DisplayRole) {
            if(index.column()==0) {
                return QString::number(a.get_id());
            }
            else if(index.column()==1) {
                return QString::fromStdString(a.get_nume());
            }
            else if(index.column()==2) {
                return QString::fromStdString(a.get_tip());
            }
            else if(index.column()==3) {
                return QString::number(a.get_pret());
            }
            else if(index.column()==4) {
                return QString::number(a.get_nr_vocale());
            }
        }
        else if(role==Qt::BackgroundRole){
            double p=a.get_pret();
            if(p<=pret){
                return QBrush(Qt::red);
            }
        }
        return QVariant{};
    }
    void set_produse(const vector<Produs>& produse,double pret) {
        beginResetModel();
        this->produse=produse;
        this->pret=pret;
        endResetModel();

    }
};
