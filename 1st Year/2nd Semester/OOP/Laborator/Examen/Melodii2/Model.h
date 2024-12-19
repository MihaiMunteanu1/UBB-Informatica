#pragma once
#include "domain.h"
#include <QAbstractTableModel>
#include "service.h"
class MyTableModel : public QAbstractTableModel {
    vector<Melodie> melodii;
    Service& srv;
public:
    MyTableModel(const vector<Melodie> melodii,Service& srv) : melodii{melodii},srv{srv} {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return melodii.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 6;
    }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if(role == Qt::DisplayRole) {
            Melodie a = melodii[index.row()];
            if(index.column()==0) {
                return QString::number(a.get_id());
            }
            else if(index.column()==1) {
                return QString::fromStdString(a.get_titlu());
            }
            else if(index.column()==2) {
                return QString::fromStdString(a.get_artist());
            }
            else if(index.column()==3) {
                return QString::fromStdString(a.get_gen());
            }
            else if(index.column()==4) {
                return QString::number(srv.nr_melodii_artist(a.get_artist()));
            }
            else if(index.column()==5) {
                return QString::number(srv.nr_melodii_gen(a.get_gen()));
            }
        }
        return QVariant{};
    }
    void set_melodii(const vector<Melodie>& melodiii) {
        beginResetModel();
        this->melodii=melodiii;
        endResetModel();

    }
};
