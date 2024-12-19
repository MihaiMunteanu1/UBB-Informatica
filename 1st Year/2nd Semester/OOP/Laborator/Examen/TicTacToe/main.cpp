#include <QApplication>
#include <QPushButton>
#include "service.h"
#include "GUI.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repo repo{"joc.txt"};
    Service srv{repo};
    GUI gui{srv};
    gui.show();
    return QApplication::exec();
}
