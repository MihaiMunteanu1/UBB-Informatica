#pragma once
#include <QAbstractTableModel>
#include "domain.h"
#include <vector>
#include <QBrush>
using std::vector;

class MyTableModel : public QAbstractTableModel {
    vector<Tractoare> tractoare;
    std::string currentType;

public:
    MyTableModel(const vector<Tractoare> activitati) : tractoare{activitati} {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return tractoare.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }
    void setCurrentType(const std::string& type) {
        currentType = type;
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("ID");
                case 1:
                    return QString("DENUMIRE");
                case 2:
                    return QString("TIP");
                case 3:
                    return QString("NR ROTI");
            }
        }
        return QVariant{};
    }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        Tractoare a = tractoare[index.row()];
        if(role == Qt::DisplayRole) {
            if(index.column()==0) {
                return QString::number(a.get_id());
            }
            else if(index.column()==1) {
                return QString::fromStdString(a.get_denumire());
            }
            else if(index.column()==2) {
                return QString::fromStdString(a.get_tip());
            }
            else if(index.column()==3) {
                return QString::number(a.get_nrRoti());
            }
        }
        else if(role == Qt::BackgroundRole && a.get_tip() == currentType) {
            return QBrush(Qt::red);
        }
        return QVariant{};
    }
    void set_tractoaree(const vector<Tractoare>& tractoaree) {
        beginResetModel();
        //emit layoutAboutToBeChanged();
        this->tractoare=tractoaree;
        //emit layoutChanged();
        endResetModel();
        //auto topLeft = createIndex(0, 0);
        //auto bottomRight = createIndex(rowCount(), columnCount());
        //emit dataChanged(topLeft, bottomRight);
        //emit layoutChanged();
    }
};
