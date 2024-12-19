#include <iostream>
#include "GUI.h"
#include <QApplication>
#include "service.h"
int main(int argc,char* argv[]) {
    QApplication a(argc,argv);
    Repo repo{"tractoare.txt"};
    Service srv{repo};
    GUI gui{srv};
    gui.show();
    QApplication::exec();
    return 0;
}
