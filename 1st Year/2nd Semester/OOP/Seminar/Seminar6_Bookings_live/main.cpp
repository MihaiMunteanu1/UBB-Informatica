#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Here";

    Repository repo;
    Service srv{ repo };
    BookingsGUI w{ srv };
    w.show();
    return a.exec();
}
