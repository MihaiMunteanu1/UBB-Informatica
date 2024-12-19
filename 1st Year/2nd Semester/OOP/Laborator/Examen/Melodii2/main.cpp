#include <QApplication>
#include <QPushButton>
#include "GUI.h"
#include "service.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repo repo{"melodii.txt"};
    Service srv{repo};
    GUI gui{srv};
    gui.show();
    return QApplication::exec();
}
