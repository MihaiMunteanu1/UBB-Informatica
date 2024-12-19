#include "GUI.h"
#include "QDebug"
void GUI::addWindows() {
    for(auto& t:srv.tipuri())
    {
        auto w1=new Window{srv,t,srv.nr_tipuri(t)};
        w1->run();
    }
}

void GUI::init(){
    setLayout(lyMain);

    model=new MyTableModel{srv.get_all(),0};
    table->setModel(model);

    lyMain->addWidget(table);

    auto* form=new QFormLayout;
    form->addRow("Id",txtId);
    form->addRow("Nume",txtNume);
    form->addRow("Tip",txtTip);
    form->addRow("Pret",txtPret);

    form->addWidget(btnAdd);

    slider->setMinimum(1);
    slider->setMaximum(100);

    form->addWidget(slider);
    lyMain->addLayout(form);

}

void GUI::conect() {
    QObject::connect(btnAdd,&QPushButton::clicked,[&](){
       int id=txtId->text().toInt();
       string nume=txtNume->text().toStdString();
       string tip=txtTip->text().toStdString();
       double pret=txtPret->text().toDouble();
       string erori=srv.adauga(id,nume,tip,pret);
       load(srv.get_all(),0);
       if(!erori.empty()){
           QMessageBox::information(nullptr,"Info",QString::fromStdString(erori));
       }
    });
    QObject::connect(slider,&QSlider::sliderMoved,[&](){
        double pret=slider->value();
        load(srv.get_all(),pret);
        qDebug()<<pret;
    });
}
void GUI::load(const vector<Produs>& p,double pret) {
    model->set_produse(p,pret);
}