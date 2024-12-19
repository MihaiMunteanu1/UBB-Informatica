#pragma once

#include <vector>
#include <string>
#include "Activitate.h"

using std::vector;
using std::string;

void exportToCVS(const string& fName, const vector<Activitate>& activitati);

void exportToHTML(const string& fName, const vector<Activitate>& activitati);
