#pragma once
#include "service.h"
#include <QAbstractTableModel>
#include "domain.h"

class MyTableModel : public QAbstractTableModel {
    vector<Joc> jocuri;
public:
    MyTableModel(const vector<Joc> jocuri) : jocuri{jocuri}{}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return jocuri.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if(role == Qt::DisplayRole) {
            Joc a = jocuri[index.row()];
            if(index.column()==0) {
                return QString::number(a.get_id());
            }
            else if(index.column()==1) {
                return QString::number(a.get_dim());
            }
            else if(index.column()==2) {
                return QString::fromStdString(a.get_tabla());
            }
            else if(index.column()==3) {
                return QString(QChar(a.get_jucator()));
            }
            else if(index.column()==4) {
                return QString::fromStdString(a.get_stare());
            }
        }
        return QVariant{};
    }
    void set_jocuri(const vector<Joc>& jocurii) {
        beginResetModel();
        this->jocuri=jocurii;
        endResetModel();

    }
};
