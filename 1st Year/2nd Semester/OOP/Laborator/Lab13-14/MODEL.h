#pragma once
#include <QAbstractTableModel>
#include "Activitate.h"
#include <vector>
using std::vector;

class MyTableModel : public QAbstractTableModel {
    vector<Activitate> activitati;
public:
    MyTableModel(const vector<Activitate> activitati) : activitati{activitati} {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return activitati.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if(role == Qt::DisplayRole) {
            Activitate a = activitati[index.row()];
            if(index.column()==0) {
                return QString::fromStdString(a.get_titlu());
            }
            else if(index.column()==1) {
                return QString::fromStdString(a.get_tip());
            }
            else if(index.column()==2) {
                return QString::fromStdString(a.get_descriere());
            }
            else if(index.column()==3) {
                return QString::number(a.get_durata());
            }
        }
        return QVariant{};
    }
    void set_activitati(const vector<Activitate>& activitatii) {
        beginResetModel();
        //emit layoutAboutToBeChanged();
        this->activitati=activitatii;
        //emit layoutChanged();
        endResetModel();
        //auto topLeft = createIndex(0, 0);
        //auto bottomRight = createIndex(rowCount(), columnCount());
        //emit dataChanged(topLeft, bottomRight);
        //emit layoutChanged();
    }
};
