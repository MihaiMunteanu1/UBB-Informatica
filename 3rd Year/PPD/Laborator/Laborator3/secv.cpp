#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

pair<vector<unsigned char>, int> readData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Nu s-a putut deschide fisierul: " + filename);
    }

    int n;
    file >> n;

    vector<unsigned char> number(n);
    for (int i = 0; i < n; i++) {
        int digit;
        file >> digit;
        number[i] = static_cast<unsigned char>(digit);
    }

    file.close();
    return {number, n};
}

void writeBigNumber(const string& filename, const vector<unsigned char>& number) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Nu s-a putut crea fisierul: " + filename);
    }

    int n = number.size();
    while (n > 1 && number[n-1] == 0) {
        n--;
    }

    for (int i = 0; i <n ; i++) {
        file << static_cast<int>(number[i]);
        file << " ";
    }
    file << endl;

    file.close();
}

vector<unsigned char> suma(const vector<unsigned char>& num1,
                                    const vector<unsigned char>& num2) {
    int maxLen = max(num1.size(), num2.size());
    vector<unsigned char> result(maxLen + 1, 0);

    unsigned char carry = 0;
    for (int i = 0; i < maxLen; i++) {
        unsigned char digit1 = (i < num1.size()) ? num1[i] : 0;
        unsigned char digit2 = (i < num2.size()) ? num2[i] : 0;

        unsigned char sum = digit1 + digit2 + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry > 0) {
        result[maxLen] = carry;
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout<<"Introduceti varianta si testul"<<endl;
        return 1;
    }

    string test = argv[2];
    string varianta = argv[1];
    string file1_path,file2_path,result_path,result_secv_path;

    file1_path = "Vers"+varianta+"/data"+test+"/Numar1.txt";
    file2_path = "Vers"+varianta+"/data"+test+"/Numar2.txt";
    result_path = "Vers"+varianta+"/data"+test+"/Numar3Secv.txt";

    auto start_total = high_resolution_clock::now();

    auto [num1, n1] = readData(file1_path);
    auto [num2, n2] = readData(file2_path);


    vector<unsigned char> result = suma(num1, num2);

    writeBigNumber(result_path, result);

    auto end_total = high_resolution_clock::now();

    auto total_time = duration_cast<milliseconds >(end_total - start_total);

    cout << "Timp total: " << total_time.count() << " ms" << endl;

    return 0;
}