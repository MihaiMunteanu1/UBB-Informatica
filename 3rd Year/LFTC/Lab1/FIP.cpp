#include <vector>
#include <fstream>
#include <iostream>
#include "FIP.h"

class FIP {
public:
    FIP() = default;

    // Add a new entry to the FIP (keeps insertion order)
    void add(int codAtom, int pozTS) {
        entries_.push_back({codAtom, pozTS});
    }

    // Save the FIP to the given output stream in a simple table format.
    // Example output same style as main: header + rows.
    void save(std::ofstream& outFile) const {
        if (!outFile) return;
        outFile << "-----------FIP----------\n";
        outFile << "| Cod atom  |  Poz. TS |\n";
        for (const auto &e : entries_) {
            outFile << "| " << e.codAtom << "        | " << e.pozTS << "\n";
        }
    }

    // Accessors
    const std::vector<FIPEntry>& entries() const { return entries_; }
    void clear() { entries_.clear(); }
    size_t size() const { return entries_.size(); }

private:
    std::vector<FIPEntry> entries_;
};