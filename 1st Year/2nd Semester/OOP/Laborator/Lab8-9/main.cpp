#include "repository.h"
#include "ActivitateService.h"
#include "ui.h"
#include "validators.h"
int main(){
    testAll();
    string fileName="activitati.txt";
    ActivitateRepoFile repo{fileName};
    //ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService srv{repo,val};
    ui ui(srv);
    ui.run();
    return 0;
}
