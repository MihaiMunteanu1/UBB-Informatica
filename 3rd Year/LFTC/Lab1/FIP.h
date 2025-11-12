#pragma once
#include <vector>
#include <fstream>

struct FIPEntry {
    int codAtom;   // code of the atom (e.g. 0 for id, 1 for const, or keyword code)
    int pozTS;     // position in TS (0 if not in TS)
};