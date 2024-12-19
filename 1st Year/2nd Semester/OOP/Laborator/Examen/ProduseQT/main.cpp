#include <QApplication>
#include "GUI.h"
#include "service.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repo repo{"produse.txt"};
    Service srv{repo};
    GUI gui{srv};
    gui.show();
    return QApplication::exec();
}
