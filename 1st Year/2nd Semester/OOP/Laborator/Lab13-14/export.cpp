#include "export.h"
#include "Activitate.h"
#include <fstream>
#include <vector>
#include <string>
void exportToCVS(const string& fName, const vector<Activitate>& activitati) {
    std::ofstream fout(fName);
    if (!fout.is_open()) {
        throw ActivitateException("Unable to open file:" + fName);
    }
    for (const auto& activitate : activitati) {
        fout << activitate.get_titlu() << ","
             << activitate.get_descriere() << ","
             << activitate.get_tip() << "," << activitate.get_durata() << "\n";
    }
    fout.close();
}

void exportToHTML(const string& fName, const vector<Activitate>& activitati) {
    std::ofstream fout(fName);
    if (!fout.is_open()) {
        throw ActivitateException("Unable to open file:" + fName);
    }
    fout << "<html><body>\n";
    fout << "<table border=\"1\" style=\"width:100 % \">\n";
    for (const auto& activitate : activitati) {
        fout << "<tr>\n";
        fout << "<td>" << activitate.get_titlu() << "</td>\n";
        fout << "<td>" << activitate.get_descriere() << "</td>\n";
        fout << "<td>" << activitate.get_tip() << "</td>\n";
        fout << "<td>" << activitate.get_durata() << "</td>\n";
        fout << "</tr>\n";
    }
    fout << "</table>\n";
    fout << "</body></html>\n";
    fout.close();
}