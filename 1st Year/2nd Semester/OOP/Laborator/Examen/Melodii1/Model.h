#pragma once
#include "service.h"
#include <QAbstractTableModel>


class MyTableModel : public QAbstractTableModel {
    vector<Melodie> melodii;
    Service& srv;
public:
    MyTableModel(const vector<Melodie> melodii,Service& srv) : melodii{melodii},srv{srv} {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return melodii.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("ID");
                case 1:
                    return QString("TITLU");
                case 2:
                    return QString("ARTIST");
                case 3:
                    return QString("RANK");
                case 4:
                    return QString("NR MELODII CU ACELASI RANK");
            }
        }
        return QVariant{};
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
                return QString::number(a.get_rank());
            }
            else if(index.column()==4) {
                return QString::number(srv.melodii_cu_acelasi_rank(a.get_rank()));
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
