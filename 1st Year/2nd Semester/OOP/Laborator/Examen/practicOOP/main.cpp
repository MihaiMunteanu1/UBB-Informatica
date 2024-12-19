#include <QApplication>
#include "GUI.h"
#include "service.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repo repo{"utilaje.txt"};
    Service srv{repo};
    test_domain();
    test_repo();
    test_service();
    GUI gui{srv};
    gui.show();
    return QApplication::exec();
}
