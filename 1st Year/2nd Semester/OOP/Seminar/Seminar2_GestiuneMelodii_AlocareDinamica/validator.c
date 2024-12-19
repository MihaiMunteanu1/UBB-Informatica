#include "validator.h"

int valideazaMelodie(Melodie m)
{
    if (strlen(m.titlu) == 0)
        return 1;
    if (strlen(m.artist) == 0)
        return 2;
    if (m.durata < 0.3 || m.durata>15.1)
        return 3;
    return 0;
}
