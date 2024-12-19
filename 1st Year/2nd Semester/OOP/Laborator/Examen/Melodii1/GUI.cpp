#include "GUI.h"
#include <QDebug>
#include <QBrush>
#include <QPainter>
#include <QPaintEvent>
void GUI::conect() {
    QObject::connect(table->selectionModel(),&QItemSelectionModel::selectionChanged,[&](){
       auto sel_item=table->selectionModel()->selectedIndexes();
       if(sel_item.isEmpty())
       {
           txtId->setText("");
           txtTitlu->setText("");
           txtArtist->setText("");
           txtRank->setText("");
       }
       else{
            auto item=sel_item.at(0);
            auto row=item.row();
            auto i=table->model()->index(row,0);
            auto j=table->model()->index(row,1);
            auto id=table->model()->data(i,Qt::DisplayRole).toInt();
            txtId->setText(QString::number(id));
            auto titlu=table->model()->data(j,Qt::DisplayRole).toString();
            txtTitlu->setText(titlu);
       }
    });
    QObject::connect(slider,&QSlider::sliderMoved,[&](){
            txtRank->setText(QString::number(slider->value()));
    });
    QObject::connect(btnDelete,&QPushButton::clicked,[&](){
       if(txtId->text().isEmpty())
           QMessageBox::information(nullptr,"Info","Nu ati selectat nicio melodie!");
       try{
           srv.sterge(txtId->text().toInt());
           load();
           update();
       }
       catch(const char* msg){
           QMessageBox::information(nullptr,"Info",msg);
       }
    });
    QObject::connect(btnUpdate,&QPushButton::clicked,[&](){
       if(!txtRank->text().isEmpty() && !txtTitlu->text().isEmpty()){
           srv.update_titlu(txtId->text().toInt(),txtTitlu->text().toStdString());
           srv.update_rank(txtId->text().toInt(),txtRank->text().toInt());
           load();
           update();
       }
       else
           QMessageBox::information(nullptr,"Text","Nu ati selectat nicio melodie sau\n"
                                                   " nu ati modificat sliderul!");
    });
}

void GUI::init(){
    setLayout(main);

    table->setModel(model);

    lyMain->addWidget(table);

    auto* form=new QFormLayout;
    form->addRow("ID",txtId);
    form->addRow("Titlu",txtTitlu);
    form->addRow("Artist",txtArtist);
    form->addRow("Rank",txtRank);

    slider->setMinimum(1);
    slider->setMaximum(10);

    form->addWidget(btnUpdate);
    form->addWidget(btnDelete);
    form->addWidget(slider);

    lyMain->addLayout(form);
    main->addLayout(lyMain);

    view->setScene(scene);
    main->addWidget(view);
}
void GUI::paintEvent(QPaintEvent *event) {
    scene->clear();
    for(int i = 1; i <= 10; i++) {
        int numSongs = srv.melodii_cu_acelasi_rank(i);
        scene->addRect(i*50, 0, 10, numSongs*20);
    }
}
void GUI::load() {
    model->set_melodii(srv.get_all());
}