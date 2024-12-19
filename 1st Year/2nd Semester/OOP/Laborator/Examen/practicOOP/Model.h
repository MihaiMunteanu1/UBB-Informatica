#pragma once
#include <QAbstractTableModel>
#include "domain.h"
#include "service.h"
#include <QBrush>


class MyTableModel : public QAbstractTableModel {
    vector<Utilaj> utilaje;
    Service& srv;
public:
    /**
     * Constructor pt Table Model
     * @param utilaje
     * @param srv
     */
    MyTableModel(const vector<Utilaj> utilaje,Service& srv) : utilaje{utilaje},srv{srv}{}

    /**
     * Functie care returneaza nr de utilaje
     * @param parent
     * @return
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return utilaje.size();
    }

    /**
     * Functie care returneaza nr de coloane
     * @param parent
     * @return
     */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        Utilaj a = utilaje[index.row()];
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
                return QString::number(a.get_cilindrii());
            }
            else if(index.column()==4) {
                return QString::number(srv.nr_utilaje_tip(a.get_tip()));
            }
        }
        return QVariant{};
    }
    void set_utilaje(const vector<Utilaj>& utilajee) {
        beginResetModel();
        this->utilaje=utilajee;
        endResetModel();

    }
};
