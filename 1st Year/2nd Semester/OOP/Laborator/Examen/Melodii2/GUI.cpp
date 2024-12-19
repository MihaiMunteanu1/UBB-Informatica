#include "GUI.h"

void GUI::init() {
    setLayout(lyMain);
    table->setModel(model);
    lyMain->addWidget(table);

    auto* form=new QFormLayout;
    form->addRow("ID",txtId);
    form->addRow("Titlu",txtTitlu);
    form->addRow("Artist",txtArtist);
    form->addRow("Gen",txtGen);
    form->addWidget(btnAdd);
    form->addWidget(btnSterge);

    lyMain->addLayout(form);

}

void GUI::conect() {
    QObject::connect(table->selectionModel(),&QItemSelectionModel::selectionChanged,[&](){
        auto sel_item=table->selectionModel()->selectedIndexes();
        if(sel_item.isEmpty())
        {
            txtId->setText("");
            txtTitlu->setText("");
            txtArtist->setText("");
            txtGen->setText("");
        }
        else{
            auto item=sel_item.at(0);
            auto row=item.row();
            auto i=table->model()->index(row,0);
            auto j=table->model()->index(row,1);
            auto k=table->model()->index(row,2);
            auto l=table->model()->index(row,3);
            int id=table->model()->data(i,Qt::DisplayRole).toInt();
            auto titlu=table->model()->data(j,Qt::DisplayRole).toString();
            auto artist=table->model()->data(k,Qt::DisplayRole).toString();
            auto gen=table->model()->data(l,Qt::DisplayRole).toString();
            txtId->setText(QString::number(id));
            txtTitlu->setText(titlu);
            txtArtist->setText(artist);
            txtGen->setText(gen);
        }
    });
    QObject::connect(btnAdd,&QPushButton::clicked,[&](){
       string titlu=txtTitlu->text().toStdString();
       string artist=txtArtist->text().toStdString();
       string gen=txtGen->text().toStdString();
       try{
           srv.adauga(titlu,artist,gen);
           load();
           this->repaint();
       }
       catch(const char* msg){
           QMessageBox::information(nullptr,"Info",msg);
       }
    });
    QObject::connect(btnSterge,&QPushButton::clicked,[&](){
        if(txtId->text().isEmpty())
            QMessageBox::information(nullptr,"Info","Nu ati selectat nimic");
        int id=txtId->text().toInt();
        try{
            srv.sterge(id);
            load();
            this->repaint();
        }
        catch(const char* msg){
            QMessageBox::information(nullptr,"Info",msg);
        }
    });
}

void GUI::load() {
    model->set_melodii(srv.get_all());
}
void GUI::paintEvent(QPaintEvent *event) {
    QPainter p{this};
    p.setPen(Qt::darkMagenta);
    int pop = 0, rock = 0, folk = 0, disco = 0;
    for(auto& m : srv.get_all()) {
        if(m.get_gen() == "pop") {
            pop++;
            p.drawEllipse(QPoint(0, 0), pop * 8, pop * 8);
        }
        if(m.get_gen() == "rock") {
            rock++;
            p.drawEllipse(QPoint(p.device()->width(), 0), rock * 8, rock * 8);
        }
        if(m.get_gen() == "folk") {
            folk++;
            p.drawEllipse(QPoint(0, p.device()->height()), folk * 8, folk * 8);
        }
        if(m.get_gen() == "disco") {
            disco++;
            p.drawEllipse(QPoint(p.device()->width(), p.device()->height()), disco * 8, disco * 8);
        }
    }
}