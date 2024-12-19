#include "GUI.h"

void GUI::conect() {
    QObject::connect(table->selectionModel(),&QItemSelectionModel::selectionChanged,[&](){
        auto sel_item=table->selectionModel()->selectedIndexes();
        if(sel_item.isEmpty())
        {
            txtId->setText("");
            txtDim->setText("");
            txtTabla->setText("");
            txtJucator->setText("");
            txtStare->setText("");
        }
        else{
            auto item=sel_item.at(0);
            auto row=item.row();
            auto i=table->model()->index(row,0);
            auto j=table->model()->index(row,1);
            auto k=table->model()->index(row,2);
            auto l=table->model()->index(row,3);
            auto m=table->model()->index(row,4);
            int id=table->model()->data(i,Qt::DisplayRole).toInt();
            int dim=table->model()->data(j,Qt::DisplayRole).toInt();
            auto tablaa=table->model()->data(k,Qt::DisplayRole).toString();
            auto jucator=table->model()->data(l,Qt::DisplayRole).toString();
            auto stare=table->model()->data(m,Qt::DisplayRole).toString();
            txtId->setText(QString::number(id));
            txtDim->setText(QString::number(dim));
            txtTabla->setText(tablaa);
            txtJucator->setText(jucator);
            txtStare->setText(stare);


        }
    });
    QObject::connect(btnAdd,&QPushButton::clicked,[&](){
        int id=txtId->text().toInt();
        int dimm=txtDim->text().toInt();
        string tablaa=txtTabla->text().toStdString();
        char jucator=txtJucator->text().toStdString()[0];
        try{
            srv.adauga(id,dimm,tablaa,jucator);
            load();
        }
        catch(const char* msg){
            QMessageBox::information(nullptr,"Info",msg);
        }
    });
    QObject::connect(btnModifica,&QPushButton::clicked,[&](){
        int id=txtId->text().toInt();
        int dimm=txtDim->text().toInt();
        string tablaa=txtTabla->text().toStdString();
        char jucator=txtJucator->text().toStdString()[0];
        string stare=txtStare->text().toStdString();
        try{
            srv.modifica(id,dimm,tablaa,jucator,stare);
            load();
        }
        catch(const char* msg){
            QMessageBox::information(nullptr,"Info",msg);
        }
    });
}

void GUI::init(){
    setLayout(lyMain);

    table->setModel(model);
    lyMain->addWidget(table);

    auto* form=new QFormLayout;

    form->addRow("ID",txtId);
    form->addRow("Dim",txtDim);
    form->addRow("Tabla",txtTabla);
    form->addRow("Jucator",txtJucator);
    form->addRow("Stare",txtStare);
    form->addWidget(btnAdd);
    form->addWidget(btnModifica);

    lyMain->addLayout(form);

}

void GUI::load() {
    model->set_jocuri(srv.get_all());
}
