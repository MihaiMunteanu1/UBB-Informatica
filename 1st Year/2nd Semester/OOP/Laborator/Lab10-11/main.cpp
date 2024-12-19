#include "ActivitatiGUI.h"
#include <QtWidgets/QApplication>
#include <vector>
#include "ActivitateService.h"
#include "repository.h"
#include "ListaActivitatiGUI.h"
using std::vector;
using std::string;
void runGUI(int argc, char* argv[]) {

    QApplication a(argc, argv);
    ActivitateRepoFile rep{ "activitati.txt" };
    //ActivitateRepo rep;
    ValidatorActivitate val;
    ActivitateService srv{ rep,val };
    ActivitatiGUI gui{ srv };
    gui.show();
    QApplication::exec();
}
int main(int argc, char* argv[])
{
    testAll();
    runGUI(argc, argv);
    return 0;
}