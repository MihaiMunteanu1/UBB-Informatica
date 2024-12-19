#include "GUI.h"
#include <QMessageBox>
void GUI::conect(){
    QObject::connect(btn1,&QRadioButton::clicked,[&](){
       txtCilindrii->setText("1");
    });
    QObject::connect(btn2,&QRadioButton::clicked,[&](){
        txtCilindrii->setText("2");
    });
    QObject::connect(btn4,&QRadioButton::clicked,[&](){
        txtCilindrii->setText("4");
    });
    QObject::connect(btn8,&QRadioButton::clicked,[&](){
        txtCilindrii->setText("8");
    });

    QObject::connect(table->selectionModel(),&QItemSelectionModel::selectionChanged,[&](){
        auto sel_item=table->selectionModel()->selectedIndexes();
        if(sel_item.isEmpty())
        {
            txtId->setText("");
            txtDenumire->setText("");
            txtTip->setText("");
            txtCilindrii->setText("");
        }
        else{
            auto item=sel_item.at(0);
            auto row=item.row();
            auto i=table->model()->index(row,0);
            auto id=table->model()->data(i,Qt::DisplayRole).toInt();
            txtId->setText(QString::number(id));
            auto j=table->model()->index(row,1);
            auto denumire=table->model()->data(j,Qt::DisplayRole).toString();
            txtDenumire->setText(denumire);
            auto k=table->model()->index(row,2);
            auto tip=table->model()->data(k,Qt::DisplayRole).toString();
            txtTip->setText(tip);
            auto l=table->model()->index(row,3);
            auto cilindrii=table->model()->data(l,Qt::DisplayRole).toInt();
            txtCilindrii->setText(QString::number(cilindrii));
            if(cilindrii==1)
                btn1->setChecked(true);
            else if(cilindrii==2)
                btn2->setChecked(true);
            else if(cilindrii==4)
                btn4->setChecked(true);
            else if(cilindrii==8)
                btn8->setChecked(true);
        }
    });
    QObject::connect(btnSterge,&QPushButton::clicked,[&](){
        if(txtId->text().isEmpty())
            QMessageBox::information(nullptr,"Info","Nu ati selectat nimic");
        else{
            try{
                srv.sterge(txtId->text().toInt());
                load();
                this->repaint();
            }
            catch(const char* msg){
                QMessageBox::information(nullptr,"Info",msg);
            }
        }

    });
    QObject::connect(btnUpdate,&QPushButton::clicked,[&](){
        int id=txtId->text().toInt();
        string denumire=txtDenumire->text().toStdString();
        string tip=txtTip->text().toStdString();
        int cilindrii;
        if(btn1->isChecked())
            cilindrii=1;
        else if(btn2->isChecked())
            cilindrii=2;
        else if(btn4->isChecked())
            cilindrii=4;
        else if(btn8->isChecked())
            cilindrii=8;
        else cilindrii=-1;
        if(cilindrii==-1)
            QMessageBox::information(nullptr,"Info","Nu ati selectat nimic");
        else{
            try{
                srv.modifica(id,denumire,tip,cilindrii);
                load();
                this->repaint();
            }
            catch(const char* msg){
                QMessageBox::information(nullptr,"Info",msg);
            }
        }
    });
}

void GUI::init(){
    setLayout(lyMain);

    auto* ly=new QHBoxLayout;
    table->setModel(model);
    //table->setMaximumHeight(300);
    table->setFixedHeight(300);
    ly->addWidget(table);

    auto* form=new QFormLayout;
    form->addRow("ID",txtId);
    form->addRow("Denumire",txtDenumire);
    form->addRow("Tip",txtTip);
    form->addRow("Cilindrii",txtCilindrii);
    form->addWidget(btnSterge);
    form->addWidget(btnUpdate);
    form->addWidget(btn1);
    form->addWidget(btn2);
    form->addWidget(btn4);
    form->addWidget(btn8);

    ly->addLayout(form);
    lyMain->addLayout(ly);
}

void GUI::load(){
    model->set_utilaje(srv.get_all());
}

void GUI::paintEvent(QPaintEvent *event) {
    QPainter p{this};
    int j=1;
    for(int i=1;i<=4;i++){
        int c=j;
        j=j*2;
        int numar=srv.nr_utilaje_cilindrii(c);
        p.drawEllipse(100*i,600,numar*20,numar*20);
    }

}