#include "GUI.h"
#include <iostream>
#include "MODEL.h"
#include <QPainter>
void GUI::connect() {
    QObject::connect(btnAdaugare,&QPushButton::clicked,[&](){
        int id,nrRoi;
        string denumire,tip;
        id=editId->text().toInt();
        nrRoi=editNrRoti->text().toInt();
        denumire=editDenumire->text().toStdString();
        tip=editTip->text().toStdString();
        try{
            srv.adauga(id,denumire,tip,nrRoi);
            load();
        }
        catch(const char* msg){
            QMessageBox::information(nullptr,"Test",msg);
        }
    });
    QObject::connect(comboBox,&QComboBox::currentIndexChanged,[&](int index){
        std::string selectedType = comboBox->itemText(index).toStdString();
        model->setCurrentType(selectedType);
        load();
    });
    QObject::connect(table, &QTableView::clicked, [&](const QModelIndex &index){
        scene->clear();
        int nrRoti = model->data(model->index(index.row(), 3)).toInt();
        for(int i = 0; i < nrRoti; i++) {
            scene->addEllipse(i*50,0,40,40);
        }
    });
}
void GUI::init(){

    setLayout(ly);

    model=new MyTableModel{srv.get_all()};
    table->setModel(model);
    ly->addWidget(table);

    auto lySt=new QFormLayout;
    lySt->addRow("ID",editId);
    lySt->addRow("Denumire",editDenumire);
    lySt->addRow("Tip",editTip);
    lySt->addRow("NrRoti",editNrRoti);
    lySt->addWidget(btnAdaugare);

    ly->addLayout(lySt);

    for(auto &tip:srv.getTipuri(srv.get_all()))
        comboBox->addItem(QString::fromStdString(tip));
    ly->addWidget(comboBox);
    view->setScene(scene);
    ly->addWidget(view);
}
void GUI::load() {
    model->set_tractoaree(srv.get_all());
}