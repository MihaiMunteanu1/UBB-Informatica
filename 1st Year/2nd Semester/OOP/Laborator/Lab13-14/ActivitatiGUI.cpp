#include "ActivitatiGUI.h"
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <unordered_map>
void ActivitatiGUI::initConnect() {
    //QMessageBox::information(nullptr, "Info", "Exit button apasat!!!");

    QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
        try {
            srv.add_activitate(txtTitlu->text().toStdString(), txtDescriere->text().toStdString(),
                               txtTip->text().toStdString(), txtDurata->text().toInt());
            loadData(srv.get_all());
        }
        catch (RepoException &ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
        }
        catch (ValidatorException &ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_msg()));
        }
    });
    QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {
        try {
            srv.actualizare_activitate(txtTitlu->text().toStdString(), txtDescriere->text().toStdString(),
                                       txtTip->text().toStdString(), txtDurata->text().toInt());
            loadData(srv.get_all());
        }
        catch (RepoException& ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
        }
    });
    QObject::connect(btnRemove, &QPushButton::clicked, [&]() {
        try {
            srv.stergere_activitate(txtTitlu->text().toStdString());
            loadData(srv.get_all());
        }
        catch (RepoException& ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
        }
    });
    QObject::connect(btnAfiseaza, &QPushButton::clicked, [&]() {
        loadData(srv.get_all());
    });
    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try {
            srv.undo();
            loadData(srv.get_all());
        }
        catch (RepoException& ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
        }
    });
    QObject::connect(btnSortByTitlu, &QPushButton::clicked, [&]() {
        loadData(srv.sortare(sortare_titlu));
    });
    QObject::connect(btnSortByDurata, &QPushButton::clicked, [&]() {
        loadData(srv.sortare(sortare_durata));
    });
    QObject::connect(btnFilterByTitlu, &QPushButton::clicked, [&]() {
        loadData(srv.filtrare_titlu(txtTitlu->text().toStdString()));
    });
    QObject::connect(btnFilterByTip, &QPushButton::clicked, [&]() {
        loadData(srv.filtrare_tip(txtTip->text().toStdString()));
    });
    QObject::connect(btnFilterByDurata, &QPushButton::clicked, [&]() {
        loadData(srv.filtrare_durata(txtDurata->text().toInt()));
    });
    /*QObject::connect(lst,&QListWidget::itemSelectionChanged,[&](){
        auto sel=lst->selectedItems();
        if(sel.empty())
        {
            txtTitlu->setText("");
            txtDurata->setText("");
            txtTip->setText("");
            txtDescriere->setText("");
        }
        else{
            auto selItem=sel.at(0);
            auto titlu=selItem->text();
            auto tip=selItem->data(Qt::UserRole).toString();
            txtTitlu->setText(titlu);
            txtTip->setText(tip);
            auto a=srv.find(titlu.toStdString());
            txtDurata->setText(QString::number(a.get_durata()));
            txtDescriere->setText(QString::fromStdString(a.get_descriere()));
        }
    });*/
    QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
        auto sel = table->selectionModel()->selectedIndexes();
        if (sel.isEmpty())
        {
            txtTitlu->setText("");
            txtDurata->setText("");
            txtTip->setText("");
            txtDescriere->setText("");
        }
        else {
            auto selItem = sel.at(0);
            auto row = selItem.row();
            auto t=table->model()->index(row,0);
            auto titlu = table->model()->data(t, Qt::DisplayRole).toString();
            txtTitlu->setText(titlu);
            auto a = srv.find(titlu.toStdString());
            txtTip->setText(QString::fromStdString(a.get_tip()));
            txtDurata->setText(QString::number(a.get_durata()));
            txtDescriere->setText(QString::fromStdString(a.get_descriere()));
        }
    });
    QObject::connect(btnLista, &QPushButton::clicked, [&]() {
        auto* lista = new ListaActivitatiGUI{srv};
        lista->show();
    });
    QObject::connect(btnListaRead, &QPushButton::clicked, [&]() {
        auto* lista = new HistogramaGUI{srv};
        lista->show();
    });
}

void ActivitatiGUI::loadData(const std::vector<Activitate>& activitati) {
    /*lst->clear();

    for (const auto& a:activitati) {
        auto* item=new QListWidgetItem(QString::fromStdString(a.get_titlu()));
        item->setData(Qt::UserRole,QString::fromStdString(a.get_tip()));
        //item->setBackground(QBrush{Qt::red,Qt::SolidPattern});
        lst->addItem(item);
    }*/

    model->set_activitati(activitati);

    ///Load buttons

    widgetBtn->setLayout(lyButns);

    for(const auto& btn:listaBtn){
        lyButns->removeWidget(btn);
        delete btn;
    }
    listaBtn.clear();

    std::unordered_map<std::string, int> dictionar;
    srv.afisare_dictionar(dictionar);
    for (const auto& [key, value] : dictionar)
    {
        auto* bButon = new QPushButton{ QString::fromStdString(key)};
        lyButns->addWidget(bButon);
        QObject::connect(bButon, &QPushButton::clicked, [value]() {
            QMessageBox::information(nullptr, "Info", QString::number(value));
        });
        listaBtn.push_back(bButon);
    }
    lyMain->addWidget(widgetBtn);

}
void ActivitatiGUI::initGUI() {

    setLayout(lyMain);

    auto* lyPanou = new QVBoxLayout{};
    //lyPanou->addWidget(lst);

    model=new MyTableModel{srv.get_all()};
    table->setModel(model);
    lyPanou->addWidget(table);

    auto lySubPanou = new QHBoxLayout{};
    lySubPanou->addWidget(btnRemove);
    lySubPanou->addWidget(btnSortByTitlu);
    lySubPanou->addWidget(btnSortByDurata);

    lyPanou->addLayout(lySubPanou);

    lyMain->addLayout(lyPanou);

    auto dreaptaLy = new QVBoxLayout;

    auto formLy = new QFormLayout;
    formLy->addRow("Titlu", txtTitlu);
    formLy->addRow("Descriere", txtDescriere);
    formLy->addRow("Tip", txtTip);
    formLy->addRow("Durata", txtDurata);


    auto lyBtn = new QHBoxLayout{};
    lyBtn->addWidget(btnAdauga);
    lyBtn->addWidget(btnUpdate);
    formLy->addRow(lyBtn);


    auto lyBtn2 = new QHBoxLayout{};
    lyBtn2->addWidget(btnFilterByTitlu);
    lyBtn2->addWidget(btnFilterByTip);
    lyBtn2->addWidget(btnFilterByDurata);
    formLy->addRow(lyBtn2);

    auto lyBtn3 = new QHBoxLayout{};
    lyBtn3->addWidget(btnAfiseaza);
    lyBtn3->addWidget(btnUndo);
    formLy->addRow(lyBtn3);

    dreaptaLy->addLayout(formLy);

    auto lyLista=new QVBoxLayout;
    lyLista->addWidget(btnLista);
    lyLista->addWidget(btnListaRead);

    dreaptaLy->addLayout(lyLista);

    lyMain->addLayout(dreaptaLy);

}